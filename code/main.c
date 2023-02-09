// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include	"def.h"
#include	"iic.h"
#include	"ssd1306.h"
#include      "ser.h"
#include	"fonts.h"
#include	"K.h"
#include	"key.h"
#include	"iap.h"
#include	"eeprom.h"
#include	"tools.h"

/*
	This program is for STC8G1K17-16pin
	MCU must be burned at following scheme:
		Internal IRC Freq. : 22.1184MHz (as same as specified in def.h)
		User EEPROM size : 2k (as same as specified in def.h)
		Low-voltage reset : Enable
		Reset pin used as I/O port : Yes
		Hardware enable WDT : Disable (I will use software enable it)
		Add a reset code in front of ID : Yes (it will adds Band-Gap voltage reference)
		Erase all EEPROM data : Yes
		Fill data to space area : 0XFF
	Calibration Data:
		They will be set at last flash page which is start from 0x4200 (or 0x600 at EEPROM address)
*/

#define DEBUG 1
#define TRACE  1

#define FREQ_IIC        200000   /* IIC frequency */
#define BAUDRATE     115200 /* serial baudrate */

#define TEMP_MIN  100  /* lowest temperature setting */
#define TEMP_MAX  500 /* highest temperature setting */
#define TEMP_COLD 25 /* init or default room temperature */
#define TEMP_TIMEOUT  10 /* in seconds,  if in temperature controlling mode, when timeout, it will be automatically back to blow controlling mode */
#define BLOW_LEVELS 16   /* levels of wind blowing control */
#define BLOW_PWM_MIN 50   /* 0-255 PWM setting when blowing setting level 0, this should be tested for another fan, don't make fan stop spinning  */
#define BLOW_STOP_TEMP 80 /* when temperature is cool-down to this, blowing can stop */
#define BLOW_START_TEMP 200 /* when temperature is higher than this, blowing must start to protect heating gun */

#define PID_KP	0.08  /* nearly 20 centigrades make full control */
#define PID_TI	200
#define PID_TD	8
#define PID_TF	2
#define PID_FALL	5   /* Enhance the control effect for temperature falling, which is always slower than rising */
#define PID_EDGE_TOP    4     /* use directly control instead of PID when temperature error is out of a range */
#define PID_EDGE_BTM   100     /* use directly control instead of PID when temperature error is out of a range */

#define ANA_GAIN 0.009901 /* gain of input to output of AMP 5.1k/(5.1k+510k), in design */
#define ANA_OFF   0.0              /* offset of AMP and residuals, in uV, 0 in design */
#define ANA_PK      0.002176  /* correction coefficient of power voltage, 14/(6420+14), in design */
#define ANA_PG     3.5641  /* gain of power voltage  to ADC input, (39+100)/39, in design */

// ADC Band-Gap reference
#define BG_REF_DEF	1190    /* default, will be used if loading from BG_REFL/BG_REFH fails */
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*EEPROM_PAGES-8) u8 BG_REFL;  // get Band-Gap Ref. mV, need to enable "Add a reset code in front of ID" option before downloading using STC-ISP
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*EEPROM_PAGES-9) u8 BG_REFH; // get Band-Gap Ref. mV, need to enable "Add a reset code in front of ID" option before downloading using STC-ISP

// my calibration data
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)) 		u8 CALI_TAG;          // when CALI_XXX exists, it will be 0x55
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+2) 	u8 CALI_OFFSETH;  // add offset, in uV, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+3)	u8 CALI_OFFSETL;   // add offset, in uV, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+4) 	u8 CALI_GAINH;  // add AMP gain, in 1/32768, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+5)	u8 CALI_GAINL;  // add AMP gain, in 1/32768, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+6) 	u8 CALI_PKH;  // add correction coefficient of power voltage, in 1/32768, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+7)	u8 CALI_PKL;   // add correction coefficient of power voltage, in 1/32768, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+8) 	u8 CALI_PGH;  // add gain of power voltage  to ADC input, in 1/32768, signed
__code __at(EEPROM_OFFSET+EEPROM_PAGE_SIZE*(EEPROM_PAGES-1)+9)	u8 CALI_PGL;    // add gain of power voltage  to ADC input, in 1/32768, signed

// global parametes and states
__pdata u16  	g_tick=0; // timer tick value

//__pdata float 	g_ana_gain       =ANA_GAIN;    
__pdata float 	g_ana_gain       =0.009980;    // gain of input to output of AMP 5.02k/(5.02k+498k), measured, 0.009901 is designed value
//__pdata float 	g_ana_off          =ANA_OFF;   
__pdata float 	g_ana_off          =2750;            // offset of AMP and residuals, in uV, measured
//__pdata float	g_ana_pk          = ANA_PK;   
__pdata float	g_ana_pk          = 0.00231;      // correction coefficient of power voltage,  measured , 0.002176  is designed value
__pdata float	g_ana_pg          = ANA_PG; 

__pdata u16	g_eeprom_addr=0;  // address for read/write config in eeprom
__pdata u16	g_temp_set_load=0;  // temperature setting, loaded from eeprom
__pdata u8		g_blow_load=0;  // temperature setting, loaded from eeprom

__pdata u16  	g_vref_bg=BG_REF_DEF;      // ADC Band-Gap Vref., in mV
__pdata u16  	g_adc_vref=0;    // ADC raw value of Band-Gap Vref
__pdata u16  	g_adc_pwr=0;    // ADC raw value of power (not Vcc of STC8G), and it's divided by 39k/(100k+39k) resistor net
__pdata u16	g_adc_temp=0; // ADC raw value of temperature

__pdata u16	g_temp_set=(TEMP_MAX+TEMP_MIN)/2;  // temperature setting, TEMP_MIN - TEMP_MAX
__pdata u8         g_blow=BLOW_LEVELS/2;     // blowing rate  0-(BLOW_LEVELS-1)  (0 means PWM output BLOW_PWM_MIN )

__bit			g_cali_mode=0;  // 1: in calibration mode
__pdata u8		g_cali_temp=TEMP_COLD;   // calibration room temperature
__bit			g_work=0;      // 1: system working 0: not work, whatever if g_run is 0 or 1
__bit 			g_run=0;            // 1: blowgun is working (switch is off)
__pdata u16	g_temp_cur=TEMP_COLD<<5;  // current measured temperature, 5-bit fixed point
__pdata u16	g_vcc=VCC;  // power Vcc voltage, in mV
__bit			g_blowing=0;  //1: currently blowing
__bit			g_heating=0; //1: currently heating

__bit 			g_rot_temp=0;  // 1: rotary encoder control temperature 0: rotary encoder control blowing
__pdata u8		g_rot_temp_timeout=0;  // 0:timeout
__bit			g_flicker=0;   // for display flicker, toggled by timer

// events
__bit e_key_button=0;     // need to check rotary encoder button
__bit e_key_rot=0;     // need to check rotary encoder step pulses
__bit e_key_run=0;     // need to check gun's switch
__bit e_disp_flush=0;     // need to flush display
__bit e_adc_vref=0;  // need to sample ADC channels
__bit e_adc_pwr=0;  // need to sample ADC channels
__bit e_adc_temp=0;  // need to sample ADC channels
__bit e_fan_control=0;  // need to control fan PWM
__bit e_heat_control=0; // need to control heating
__bit e_calc=0; // need to calculate temperature and do heating control


// save back calibrated data
void factory_save()
{
	__xdata u8 p[EEPROM_PAGE_SIZE];
	i16 t;
	iap_load (p, EEPROM_PAGES-1);
	p[0]=0x55;
	t=(i16)(g_ana_off-ANA_OFF);
	p[2]=t>>8;
	p[3]=(u8)t;
	t=(i16)((g_ana_gain/ANA_GAIN-1.0)*32768+0.5);
	p[4]=t>>8;
	p[5]=(u8)t;
	t=(i16)((g_ana_pk/ANA_PK-1.0)*32768+0.5);
	p[6]=t>>8;
	p[7]=(u8)t;
	t=(i16)((g_ana_pg/ANA_PG-1.0)*32768+0.5);
	p[8]=t>>8;
	p[9]=(u8)t;
	iap_save (p, EEPROM_PAGES-1);	
#if DEBUG
	ser_str("Cali data saved\r\n");
#endif
}

// read ADC ch , ch==0x0f means internal Gap-Band voltage, output 0~65535
#pragma callee_saves adc_read
u16 adc_read(u8 ch)
{
	ADC_CONTR =ch | 0b11000000; // power on, start, select internal Gap-Band channel
	_nop();
	_nop();
	while (!(ADC_CONTR & 0b00100000));   // wait completing
	ADC_CONTR &= 0b11011111; // clear ADC_FLAG
	return ADC_RES16;  // optimized by using __sfr16
}

// change FAN PWM output, 0-0xFF, 0 means off, 0xFF means full power
#pragma callee_saves fan_ctrl
void fan_ctrl (u8 pwm)
{
	if (pwm)
		PCA_PWM1 &= 0b11001101;
	else
		PCA_PWM1 |= 0b00110010;

	CCAP1H = (u8)0xFF - pwm;
}

// if P3.0 is low, reboot for downloading
void on_P30_down()  __interrupt (16)
{
	IAP_CONTR = 0x60;
}

// when power is down
void on_cmp()   __interrupt (21)
{
	CMPCR1 &= 0b10111111; // clear flag 
	
	EA=0;
	CR=0; // stop PCA/PWM for saving power (maybe blow is stop/full power for a short time)
	if (g_temp_set_load!=g_temp_set || g_blow_load!=g_blow) { // need to save config
		iap_write(g_eeprom_addr, g_temp_set>>8);
		iap_write(g_eeprom_addr+1, g_temp_set);
		iap_write(g_eeprom_addr+2, g_blow);
		g_eeprom_addr=eeprom_save(g_eeprom_addr,3,0,EEPROM_PAGES-1);
		g_temp_set_load=g_temp_set;
		g_blow_load=g_blow;
#if DEBUG
		ser_str("config saved\r\n");
#endif
	} 
	CR=1;
	EA=1;

#if DEBUG
	ser_str("power lost\r\n");
#endif
}

// make digital array of a number for display
void digitalize (u16 u, __idata u8* p)
{
	p[2]=u%10;
	u-=p[2];
	u/=10;
	p[1]=u%10;
	u-=p[1];
	u/=10;
	p[0]=u%10;
}

// show string in display
/*
void disp_str(char * str, u8 col, u8 page)
{
	while (*str) {
		ssd1306_bitmap(col,page,8,16,FONTS_ASCII_8X16[*str-' ']);
		col+=8;
		str++;
	}
}
*/

// flush display
void disp_flush()
{
	static __bit cali_mode=0;	
	static __bit show_fixed=0;
	static __bit temp_flicker=0;
	static __bit heating=0;
	static __bit blowing=0;
	static __bit work=0;
	static __bit run=0;
	static __pdata u16 temp_set=0xffff;
	static __pdata u16 temp_cur=0xffff;
	static __pdata u8   blow=0xff;
	static __pdata u8   cali_temp=0xff;
	
	__idata u8 p[3];
	
	if (!(CMPCR1&0x01))  // maybe no power, just testing/downloading
		return;
		
	if (cali_mode!=g_cali_mode) {
		cali_mode=g_cali_mode;
		show_fixed=0;
		ssd1306_rect(0,0,128,8,0); // clear screen
	}
	
	if (cali_mode) {
		if (!show_fixed || cali_temp!=g_cali_temp) {
			cali_temp=g_cali_temp;
			digitalize(cali_temp, p);
			if (!p[0])
				ssd1306_rect(60,5,16,3,0);
			else 
				ssd1306_bitmap(60,5,16,3,FONTS_DIGI_SET_16X24[p[0]]);
			if (!p[0]  && !p[1])
				ssd1306_rect(76,5,16,3,0);
			else 
				ssd1306_bitmap(76,5,16,3,FONTS_DIGI_SET_16X24[p[1]]);
			ssd1306_bitmap(92,5,16,3,FONTS_DIGI_SET_16X24[p[2]]);
		}
	} else {
		// temperature "set" string flicker
		if (g_rot_temp) {
			if (!show_fixed || temp_flicker!=g_flicker) {
				temp_flicker=g_flicker;
				if (temp_flicker) {
					ssd1306_bitmap(0,0,16,3,FONTS_DIGI_SET_16X24[10]);  //S
					ssd1306_bitmap(16,0,16,3,FONTS_DIGI_SET_16X24[11]);  //E
					ssd1306_bitmap(32,0,16,3,FONTS_DIGI_SET_16X24[12]);  //T
					ssd1306_bitmap(48,0,11,3,FONTS_COLON_11X24);  //:
				} else {
					ssd1306_rect(0,0,59,3,0);
				}
			}
		} else {
			if (!show_fixed || !temp_flicker) {
				ssd1306_bitmap(0,0,16,3,FONTS_DIGI_SET_16X24[10]);  //S
				ssd1306_bitmap(16,0,16,3,FONTS_DIGI_SET_16X24[11]);  //E
				ssd1306_bitmap(32,0,16,3,FONTS_DIGI_SET_16X24[12]);  //T
				ssd1306_bitmap(48,0,11,3,FONTS_COLON_11X24);  //:
				temp_flicker=1;
			} 
		} 

		// show temperature setting number
		if (!show_fixed || temp_set!=g_temp_set) {
			temp_set=g_temp_set;
			digitalize(temp_set, p);
			if (!p[0])
				ssd1306_rect(60,0,16,3,0);
			else 
				ssd1306_bitmap(60,0,16,3,FONTS_DIGI_SET_16X24[p[0]]);
			if (!p[0]  && !p[1])
				ssd1306_rect(76,0,16,3,0);
			else 
				ssd1306_bitmap(76,0,16,3,FONTS_DIGI_SET_16X24[p[1]]);
			ssd1306_bitmap(92,0,16,3,FONTS_DIGI_SET_16X24[p[2]]);
		}

		if (!show_fixed || temp_cur!=((g_temp_cur+3)>>5)) {
			temp_cur=(g_temp_cur+3)>>5;
			digitalize(temp_cur, p);
			if (!p[0])
				ssd1306_rect(44,3,20,4,0);
			else 
				ssd1306_bitmap(44,3,20,4,FONTS_DIGI_20X32[p[0]]);
			if (!p[0]  && !p[1])
				ssd1306_rect(64,3,20,4,0);
			else 
				ssd1306_bitmap(64,3,20,4,FONTS_DIGI_20X32[p[1]]);
			ssd1306_bitmap(84,3,20,4,FONTS_DIGI_20X32[p[2]]);
		}

		if (!show_fixed || blow!=g_blow) {
			blow=g_blow;
			u8 t=1+(u8)((u16)blow*126/(BLOW_LEVELS-1));
			ssd1306_rect(0,7,t,1,0b01111111);
			if (t<127)
				ssd1306_rect(t,7,127-t,1,0b01000001);
			ssd1306_rect(127,7,1,1,0b01111111);
		}
		
		if (!show_fixed || heating!=g_heating || blowing!=g_blowing || work!=g_work || run!=g_run) {
			heating=g_heating;
			blowing=g_blowing;
			work=g_work;
			run=g_run;
			if (heating)
				ssd1306_bitmap(0,3,32,4,FONTS_HEAT_32X32);
			else if (work) {
				if (run)
					ssd1306_bitmap(0,3,32,4,FONTS_RUN_32X32);
				else
					ssd1306_bitmap(0,3,32,4,FONTS_WORK_32X32);
			} else if (blowing)
				ssd1306_bitmap(0,3,32,4,FONTS_BLOW_32X32);	
			else
				ssd1306_rect(0,3,32,4,0);
		}
	}
	
	if (!show_fixed) {
		show_fixed=1;
		if (cali_mode)
			ssd1306_bitmap(0,0,128,4,FONTS_CALI_128X32);  // calibration notice text
		else {
			ssd1306_bitmap(108,0,20,3,FONTS_CDG_20X24);  // centigrade
			ssd1306_bitmap(104,3,24,4,FONTS_CDG_24X32);  // centigrade
		}
	}	
}

// prog entry
void main()
{
	// disable intr. 
	EA=0;  
	
	// P0,P2,P4 is not used, all High-Z
	P0M0 = 0x00;
	P0M1 = 0xff;
	P2M0 = 0x00;
	P2M1 = 0xff;
	P4M0 = 0x00;
	P4M1 = 0xff;
	// P1.1 P1.6 P1.7:Rotary encoder input (0-Active, Weak-Pull-Up), P1.0:Fan output (1-Active, Push-Pull), others:High-Z
	P1 = 0b11000010;
	P1M0 = 0b00000001;
	P1M1 = 0b00111100;
	P1DR = 0b11111110; // enhance P1.0 output current
	P1SR = 0b11111110; // enhance P1.0 output rate
	// P3.5: Analog input, but want to enhance LM321 output range (weak pull-up),  P3.6 P3.7:Analog input (High-Z),
	// P3.4:Gun Swith input (1-Active), OC, pull-up only when scanning
	// P3.2 P3.3:IIC (Bi-Dir, 0-Active), P3.1 P3.0:Serial Port (Bi-Dir, 0-Start)
	P3 = 0b00001111;
	P3M0 = 0b00010000;
	P3M1 = 0b11110000;
	P3IE = 0b00011111; // disable digital mode for analog input
#if VCC<3800
	P3PU = 0b00001100; // will be used if power voltage is below 3.8V for more pull-up 
#endif
	//P5.5:Heating Control ouput (0-Active, OC), others:High-Z
	P5 = 0b00100000;
	P5M0 = 0b00100000;
	P5M1=0b11111111;
	P5DR = 0b11011111;  // enhance P5.5 output current
	
	// TxD=>P3.1 RxD=>P3.0 CCP1=>P1.0 
	P_SW1 &= 0b00001111;
	// enable XFR always (in fact, not so many RAM), SCL=>P3.2, SDA=>P3.3
	P_SW2 |= 0b10110000; 
	
	// init send-only serial 1 (using timer 2) for debug
	ser_init(65536 - FOSC/BAUDRATE/4);
#if DEBUG
	ser_str("start\r\n");
#endif
		
	// init I2C as master
	iic_init(((FOSC/2/FREQ_IIC)-4)/2);
#if DEBUG
	ser_str("init IIC done\r\n");
#endif
	
	// init ADC
	ADCCFG &= 0b11010000;  // result is left-alignment (a fake 16bit result), ADCclk=SYSclk/2/1
	ADCTIM = 0b10111111;  // 2(setup)+32(duty)+2(hold)+10(convert)=46 ADCclk 
	ADC_CONTR = 0b10001111;  // power on, stop, select internal Gap-Band channel 
	EADC = 0; // not use intro.
#if DEBUG
	ser_str("init ADC done\r\n");
#endif
	
	// init PCA1:8 bit PWM
	CCON &= 0b00111000; // not start now
	CMOD = CMOD & 0b01110000 | 0b00001010; // PCA use FOSC/4=5529.6kHz as clock, no overflow intr.
	CL = 0;  // counter start from 0
	CH = 0;
	CCAP1L = 0xFF; 
	CCAP1H = 0xFF;
	PCA_PWM1 = 0b00111111; // 8 bits PWM mode (FOSC/4/256=21.6kHz), start at 0-Level
	CCAPM1 = CCAPM1 & 0b10000000 | 0b01000010; // PWM mode
	CR = 1;  // start PCA
#if DEBUG
	ser_str("init PWM done\r\n");
#endif

	// init comparator 
	CMPCR1 = 0b10000001; // enable, no intr. , no output, P3.7 vs BandGap voltage
	CMPCR2 = 0b00111111; // enable analog filter and maxium digital filter
	tools_delay_ms(10); // wait for stable result
	IP2 |= 0b00100000;
	IP2H |= 0b00100000; // highest intr. priority
	CMPCR1 |= 0b00010000; // enable intr. when P3.7<BandGap
#if DEBUG
	ser_str("init CMP done\r\n");
#endif

	// init OLED
	if (CMPCR1&0x01) { // maybe no power, factory testing, oled will block IIC communication
		ssd1306_dev(SSD1306_ADDR1);
		ssd1306_init(0, 0, 0);
#if DEBUG
		ser_str("init OLED done\r\n");
#endif
	}

	// init global parameters
	_mk_u16(&g_vref_bg, BG_REFH, BG_REFL); //load band-gap vref
	if (g_vref_bg<(BG_REF_DEF-300) || g_vref_bg>(BG_REF_DEF+300)) // probably incorrect
		g_vref_bg=BG_REF_DEF;
#if DEBUG
	ser_str("Band-Gap Vref = ");
	ser_u32(g_vref_bg);
	ser_str(" mV\r\n");
#endif

	g_adc_vref=adc_read(15);
	g_adc_pwr=adc_read(14);
	g_adc_temp=adc_read(13);
	
	// calibration
	if (CALI_TAG==0x55) {
		i16 t;
		_mk_u16(&t, CALI_OFFSETH, CALI_OFFSETL);
#if DEBUG
		ser_str("Cali offset += ");
		ser_i32(t);
		ser_str(" uV\r\n");
#endif
		g_ana_off=(float)(ANA_OFF)+t;

		_mk_u16(&t, CALI_GAINH, CALI_GAINL);
#if DEBUG
		ser_str("Cali gain += ");
		ser_i32(t);
		ser_str(" /32768\r\n");
#endif
		g_ana_gain=(float)(ANA_GAIN)*(1.0+(float)t/32768);

		_mk_u16(&t, CALI_PKH, CALI_PKL);
#if DEBUG
		ser_str("Cali Pwr Coef += ");
		ser_i32(t);
		ser_str(" /32768\r\n");
#endif
		g_ana_pk=(float)(ANA_PK)*(1.0+(float)t/32768);

		_mk_u16(&t, CALI_PGH, CALI_PGL);
#if DEBUG
		ser_str("Cali Pwr gain += ");
		ser_i32(t);
		ser_str(" /32768\r\n");
#endif
		g_ana_pg=(float)(ANA_PG)*(1.0+(float)t/32768);
	} else {   // save first data
		factory_save();	
	}

	// load config from eeprom	
	g_eeprom_addr=eeprom_load(3, 0, EEPROM_PAGES-1); // the last page cannot be used, it contains some MCU setting
	if (g_eeprom_addr==0xFFFF) { // not found
#if DEBUG
		ser_str("Cfg not found\r\n");
#endif				
		g_temp_set=(TEMP_MIN+TEMP_MAX)/2;  
		g_blow=BLOW_LEVELS/2;  	
	} else {
#if DEBUG
		ser_str("Cfg found at 0x");
		ser_h16(g_eeprom_addr);
		ser_str("\r\n");
#endif		
		g_temp_set=g_temp_set_load=((u16)iap_read(g_eeprom_addr)<<8)+iap_read(g_eeprom_addr+1);
		g_blow=g_blow_load=iap_read(g_eeprom_addr+2);
		if (g_temp_set<TEMP_MIN)
			g_temp_set=TEMP_MIN;
		else if (g_temp_set>TEMP_MAX)
			g_temp_set=TEMP_MAX;
		if (g_blow>=BLOW_LEVELS)
			g_blow=BLOW_LEVELS-1;
	}
	
	// prepare for saving eeprom
	g_eeprom_addr=eeprom_save(g_eeprom_addr,3,0,3);
#if DEBUG
		ser_str("next Cfg at 0x");
		ser_h16(g_eeprom_addr);
		ser_str("\r\n");
#endif		
	
	// init timer 1, frequency is 1000Hz
	ET1=0; // no intr.
	TCON &= 0b00111111;  // stop T1
	INTCLKO &= 0b11111101; // T1 no clock port output	
	TMOD &= 0b00001111;  // 16bit auto-reload mode for T1
	TL1 = (u8)(65536UL-FOSC/12/1000); 
	TH1 = (u8)((65536UL-FOSC/12/1000)>>8); 
	AUXR &= 0b10111111;  // T1 use FOSC/12
#if DEBUG
	ser_str("init Timer1 done\r\n");
#endif

	// enable P3.0 fall-down intr. to reboot
	INTCLKO |= 0b01000000;
	
	// check if enter calibration mode
	if (!P11) {
		g_cali_mode=1;
#if DEBUG
		ser_str("enter calibration mode\r\n");
#endif
	}

	// enable watch dog
	WDT_CONTR = 0b00110101; // nearly 1.2s
	
	// start timer
 	TR1 = 1;

	// enable all intr.
	EA = 1;

	// main loop, try to do only one thing one time
	while(1) {
		// clear watch dog
		WDT_CONTR |=0b00010000;
			
		// heating control
		if (e_heat_control) {
			e_heat_control=0;
			// pid control, anti-integral-windup
			// G(s)=kp(e+e/(ti*S)+td*S*e/(1+Tf*S))
			static float ei=0;
			static float ed=0;
			static u16 last_temp_cur=TEMP_COLD<<5;
			static u16 last_temp_set=0;
			ed=(ed*PID_TF+(float)(i16)(last_temp_cur-g_temp_cur)/32.0)/(1+PID_TF);
			if (g_run && g_work) {
				float e=(float)g_temp_set-(float)g_temp_cur/32.0;
				if (last_temp_set!=g_temp_set)
					ei=0.0;
				if (e>PID_EDGE_BTM) {
					g_heating=1;
					ei=0;					
				} else if (e<-PID_EDGE_TOP) {
					g_heating=0;
					ei=0;
				} else {
					float y=e<0.0?e*(PID_FALL):e;
					y+=(ei+e)/(PID_TI);
					y+=(ed<0.0?ed*(PID_FALL):ed)*(PID_TD);
					y*=(PID_KP);
					if (e>0 && y<1.0 || e<0 && y>-1.0)
						ei+=e;
					g_heating=(y>1.0);
				}
			} else {
				ei=0;
				ed=0;
				g_heating=0;
			}
			last_temp_cur=g_temp_cur;
			last_temp_set=g_temp_set;
			P55=g_heating?0:1;
			continue;
		}
		
		// fan control	
		if (e_fan_control) {
			e_fan_control=0;
			if ((g_run && g_work)
			    || g_temp_cur>=(BLOW_START_TEMP<<5)
			    || (g_temp_cur>=(BLOW_STOP_TEMP<<5)  && g_blowing) // hysteretic control
			) {  
				g_blowing=1;
				fan_ctrl(BLOW_PWM_MIN+(u8)(((255-BLOW_PWM_MIN)*g_blow+(BLOW_LEVELS-2))/(BLOW_LEVELS-1))); 
			} else {
				g_blowing=0;
				fan_ctrl(0);
			}
			continue;
		}

		// ADC control
		if (!(ADC_CONTR & 0b01100000)) { // ADC not working
			if (e_adc_vref) {
				e_adc_vref=0;
				ADC_CONTR =15 | 0b11000000;
				continue;
			} else if (e_adc_pwr) {
				e_adc_pwr=0;
				ADC_CONTR =14 | 0b11000000;
				continue;
			} else if (e_adc_temp) {
				e_adc_temp=0;
				ADC_CONTR =13 | 0b11000000;
				continue;
			}
		} else if (ADC_CONTR & 0b00100000) { // done
			ADC_CONTR &= 0b10001111; // clear ADC_FLAG
			u8 ch=ADC_CONTR & 0b00001111;
			if (ch==15)
				g_adc_vref+= ((i16)(ADC_RES16-g_adc_vref)>>3);  // simple filter, for ADC_RES16 is in fact 10 bits significant
			else if (ch==14)
				g_adc_pwr+= ((i16)(ADC_RES16-g_adc_pwr)>>3);  // simple filter, for ADC_RES16 is in fact 10 bits significant
			else if (ch==13)
				g_adc_temp+= ((i16)(ADC_RES16-g_adc_temp)>>3);  // simple filter, for ADC_RES16 is in fact 10 bits significant
			continue;
		}
		
		// calculate temperature
		if (e_calc) {
			e_calc=0;
			
			float k_ref=1000.0*g_vref_bg/g_adc_vref;  
			float v_pwr=k_ref*g_adc_pwr*g_ana_pg;      // in uV
			g_vcc=(u16)(v_pwr/1000+0.5);
			float v_temp=k_ref*g_adc_temp*g_ana_gain-v_pwr*g_ana_pk+g_ana_off; // in uV
			
			if (v_temp<0.0) 
				v_temp=0.0;
			else if (v_temp>60000.0) 
				v_temp=60000.0;
			
			u16 temp=K_temp((u16)(v_temp+0.5));
			if (temp!=0xFFFF) 
				g_temp_cur+=(i16)(temp-g_temp_cur)>>2; // a simple filter, round-off error is acceptable (1/8 centidegree)

			continue;
		}
			
		// rotary pulses
		if (e_key_rot) { // 500Hz
			e_key_rot=0;
			__bit left=0, right=0, left_q=0, right_q=0;
			KEY_ROT1(k_ra, k_rb,  !P17, !P16,  500*4/1000, left, right) // 4ms	
			KEY_QUICK(n_rot_left_q, left, left_q, 500UL*100/1000) // 100ms
			KEY_QUICK(n_rot_right_q, right, right_q, 500UL*100/1000) //100ms
			
#if DEBUG
			if (left) ser_str("rot <\r\n");
			if (right) ser_str("rot >\r\n");
			if (left_q) ser_str("rot <<\r\n");
			if (right_q) ser_str("rot >>\r\n");
#endif
			if (g_cali_mode) {
				if ((left_q || left) && g_cali_temp>0)
					g_cali_temp--;
				else if ((right_q || right) && g_cali_temp<50)
					g_cali_temp++;
			} else if (g_rot_temp) { // controlling temperature
				if (left_q) {
					g_temp_set=5*((g_temp_set-5)/5);
					g_rot_temp_timeout=0;
				} else if (right_q) {
					g_temp_set=5*((g_temp_set+9)/5);
					g_rot_temp_timeout=0;
				} else if (left) {
					g_temp_set-=1;
					g_rot_temp_timeout=0;
				} else if (right) {
					g_temp_set+=1;
					g_rot_temp_timeout=0;
				}
				if (g_temp_set<TEMP_MIN)
					g_temp_set=TEMP_MIN;
				else if (g_temp_set>TEMP_MAX)
					g_temp_set=TEMP_MAX;
			} else { // controlling blowing
				if ((left_q || left) && g_blow>0)
					g_blow--;
				else if ((right_q || right) && g_blow<(u8)(BLOW_LEVELS-1))
					g_blow++;
			}		
			continue;
		}
		
		// rotary button
		if (e_key_button) { // 62Hz
			e_key_button=0;
			__bit down=0, click=0, longpress=0;
			KEY_BUTTON(k_rk, !P11, 50*62/1000, down, click, longpress, 1500UL*62/1000) // 50ms, 1.5s
			
#if DEBUG
			if (down) ser_str("button -\r\n");
			if (click) ser_str("button *\r\n");
			if (longpress) ser_str("button ---\r\n");
#endif		
			if (g_cali_mode) {
				static __bit can_click=0;
				if (can_click) {
					if(click) {
						can_click=0;
						float k_ref=1000.0*g_vref_bg/g_adc_vref;  
						g_ana_off=(float)K_uv(((u16)g_cali_temp<<5)+8)-k_ref*((float)g_adc_temp*g_ana_gain-(float)g_adc_pwr*g_ana_pg*g_ana_pk);
						factory_save();
						g_cali_mode=0;
		#if DEBUG
						ser_str("exit calibration mode\r\n");
		#endif		
					} 
				} else if (click || longpress)
					can_click=1;  // check this for button is pressed when entering calibration mode
			} else if (click) {
				g_work=!g_work;
			} else if (longpress) {
				g_rot_temp=!g_rot_temp;
				g_rot_temp_timeout=0;
			}
			continue;
		}
			
		// run switch
		if (e_key_run) { //31Hz
			e_key_run=0;
			if (g_cali_mode)
				g_run=0;
			else {
				u8 i;
				P34=1;
				P3PU|=0b00010000; // turned P3.4 to pull-up
				i=255;
				while(--i); // delay a while for P3.4 charge
				KEY_LEVEL(g_run, P34, 200*31/1000) //200ms
				P3PU&=0b11101111; // turned back to high-Z avoid affecting the thermocouple voltage by the pull-up current
				P34=0;
				i=255;
				while(--i); // delay a while for P3.4 discharge
			}
			continue;
		}

		// display flush
		if (e_disp_flush) { // 8Hz
			e_disp_flush=0;
			disp_flush();
			continue;
		}
			
		// main timer tick 
		if (TF1) {
			TF1=0;
			g_tick++; 

#if TRACE
		if (!(g_tick&0x3FF)) { // nearly 1s
				ser_ch('=S:');
				ser_ch(g_work?'W':'w');
				ser_ch(g_run?'R':'r');
				ser_ch(g_heating?'H':'h');
				ser_ch(g_blowing?'B':'b');
				ser_str(" V:");
				ser_u32(g_vcc);
				ser_str(" Tc:");
				ser_u32((g_temp_cur+2)>>5);
				ser_str(" Ts:");
				ser_u32(g_temp_set);
				ser_str(" Bs:");
				ser_u32(g_blow);
				ser_str(" Ar:");
				ser_u32(g_adc_vref);
				ser_str(" Ap:");
				ser_u32(g_adc_pwr);
				ser_str(" At:");
				ser_u32(g_adc_temp);
				ser_str("\r\n");
			}
#endif

			if (((u8)g_tick & 0x01) ==0) // rotary pulses checking at 500Hz
				e_key_rot=1; 
				
			if (((u8)g_tick & 0x0f) ==3) // rotary button checking at 62 Hz
				e_key_button=1; 

			if (((u8)g_tick & 0x1f) ==5) // gun's switch checking at 31 Hz
				e_key_run=1; 
			
			if (((u8)g_tick & 0x7f) ==11) // display flushing at 8 Hz
				e_disp_flush=1; 
			
			if (((u8)g_tick & 0x07) ==1) // adc sampling at 125 Hz
				e_adc_vref=1; 

			if (((u8)g_tick & 0x07) ==3) // adc sampling at 125 Hz
				e_adc_pwr=1; 

			if (((u8)g_tick & 0x07) ==5) // adc sampling at 125 Hz
				e_adc_temp=1; 

			if (((u8)g_tick & 0x1f) ==15) // calculate at 32 Hz
				e_calc=1; 

			if (((u8)g_tick & 0x3f) ==29) // fan control at 16Hz
				e_fan_control=1; 

			if (((u8)g_tick & 0x7f) ==63) // heating control at 8Hz
				e_heat_control=1; 
				
			if ((g_tick & 0x1ff) == 77)
				g_flicker=!g_flicker;

			if ((g_tick & 0x03ff) == 376) { // nearly 1 second
				// check if rotary encoder should take control of blowing again
				if (g_rot_temp) {
					if (++g_rot_temp_timeout==TEMP_TIMEOUT) {
						g_rot_temp=0;
						g_rot_temp_timeout=0;
					}
				}  				
			}
		}
	}
}

