#ifndef     __STC8G_H__
#define     __STC8G_H__

/////////////////////////////////////////////////

//包含本头文件后,不用另外再包含"REG51.H"

__sfr __at(0x80) P0;
__sbit __at(0x80) P00;
__sbit __at(0x81) P01;
__sbit __at(0x82) P02;
__sbit __at(0x83) P03;
__sbit __at(0x84) P04;
__sbit __at(0x85) P05;
__sbit __at(0x86) P06;
__sbit __at(0x87) P07;
__sfr __at(0x81) SP;
__sfr16 __at(0x8382) DP;
__sfr __at(0x82) DPL;
__sfr __at(0x83) DPH;
__sfr __at(0x84) S4CON;
__sfr __at(0x85) S4BUF;
__sfr __at(0x87) PCON;
__sfr __at(0x88) TCON;
__sbit __at(0x8F) TF1;
__sbit __at(0x8E) TR1;
__sbit __at(0x8D) TF0;
__sbit __at(0x8C) TR0;
__sbit __at(0x8B) IE1;
__sbit __at(0x8A) IT1;
__sbit __at(0x89) IE0;
__sbit __at(0x88) IT0;
__sfr __at(0x89) TMOD;
__sfr __at(0x8A) TL0;
__sfr __at(0x8B) TL1;
__sfr16 __at(0x8C8A) T0;
__sfr __at(0x8C) TH0;
__sfr16 __at(0x8D8B) T1;
__sfr __at(0x8D) TH1;
__sfr __at(0x8E) AUXR;
__sfr __at(0x8F) INTCLKO;
__sfr __at(0x90) P1;
__sbit __at(0x90) P10;
__sbit __at(0x91) P11;
__sbit __at(0x92) P12;
__sbit __at(0x93) P13;
__sbit __at(0x94) P14;
__sbit __at(0x95) P15;
__sbit __at(0x96) P16;
__sbit __at(0x97) P17;
__sfr __at(0x91) P1M1;
__sfr __at(0x92) P1M0;
__sfr __at(0x93) P0M1;
__sfr __at(0x94) P0M0;
__sfr __at(0x95) P2M1;
__sfr __at(0x96) P2M0;
__sfr __at(0x98) SCON;
__sbit __at(0x9F) SM0;
__sbit __at(0x9E) SM1;
__sbit __at(0x9D) SM2;
__sbit __at(0x9C) REN;
__sbit __at(0x9B) TB8;
__sbit __at(0x9A) RB8;
__sbit __at(0x99) TI;
__sbit __at(0x98) RI;
__sfr __at(0x99) SBUF;
__sfr __at(0x9A) S2CON;
__sfr __at(0x9B) S2BUF;
__sfr __at(0x9D) IRCBAND;
__sfr __at(0x9E) LIRTRIM;
__sfr __at(0x9F) IRTRIM;
__sfr __at(0xA0) P2;
__sbit __at(0xA0) P20;
__sbit __at(0xA1) P21;
__sbit __at(0xA2) P22;
__sbit __at(0xA3) P23;
__sbit __at(0xA4) P24;
__sbit __at(0xA5) P25;
__sbit __at(0xA6) P26;
__sbit __at(0xA7) P27;
__sfr __at(0xA2) P_SW1;
__sfr __at(0xA8) IE;
__sbit __at(0xAF) EA;
__sbit __at(0xAE) ELVD;
__sbit __at(0xAD) EADC;
__sbit __at(0xAC) ES;
__sbit __at(0xAB) ET1;
__sbit __at(0xAA) EX1;
__sbit __at(0xA9) ET0;
__sbit __at(0xA8) EX0;
__sfr __at(0xA9) SADDR;
__sfr __at(0xAA) WKTCL;
__sfr __at(0xAB) WKTCH;
__sfr16 __at(0xABAA) WKTC;
__sfr __at(0xAC) S3CON;
__sfr __at(0xAD) S3BUF;
__sfr __at(0xAE) TA;
__sfr __at(0xAF) IE2;
__sfr __at(0xB0) P3;
__sbit __at(0xB0) P30;
__sbit __at(0xB1) P31;
__sbit __at(0xB2) P32;
__sbit __at(0xB3) P33;
__sbit __at(0xB4) P34;
__sbit __at(0xB5) P35;
__sbit __at(0xB6) P36;
__sbit __at(0xB7) P37;
__sfr __at(0xB1) P3M1;
__sfr __at(0xB2) P3M0;
__sfr __at(0xB3) P4M1;
__sfr __at(0xB4) P4M0;
__sfr __at(0xB5) IP2;
__sfr __at(0xB6) IP2H;
__sfr __at(0xB7) IPH;
__sfr __at(0xB8) IP;
__sbit __at(0xB8+7) PPCA;
__sbit __at(0xB8+6) PLVD;
__sbit __at(0xB8+5) PADC;
__sbit __at(0xB8+4) PS;
__sbit __at(0xB8+3) PT1;
__sbit __at(0xB8+2) PX1;
__sbit __at(0xB8+1) PT0;
__sbit __at(0xB8+0) PX0;
__sfr __at(0xB9) SADEN;
__sfr __at(0xBA) P_SW2;
__sfr __at(0xBC) ADC_CONTR;
__sfr __at(0xBD) ADC_RES;
__sfr __at(0xBE) ADC_RESL;
__sfr16 __at(0xBDBE) ADC_RES16;
__sfr __at(0xC0) P4;
__sbit __at(0XC0+0) P40;
__sbit __at(0xC0+1) P41;
__sbit __at(0xC0+2) P42;
__sbit __at(0xC0+3) P43;
__sbit __at(0xC0+4) P44;
__sbit __at(0xC0+5) P45;
__sbit __at(0xC0+6) P46;
__sbit __at(0xC0+7) P47;
__sfr __at(0xC1) WDT_CONTR;
__sfr __at(0xC2) IAP_DATA;
__sfr __at(0xC3) IAP_ADDRH;
__sfr __at(0xC4) IAP_ADDRL;
__sfr16 __at(0xC3C4) IAP_ADDR;
__sfr __at(0xC5) IAP_CMD;
__sfr __at(0xC6) IAP_TRIG;
__sfr __at(0xC7) IAP_CONTR;
__sfr __at(0xC8) P5;
__sbit __at(0xC8+0) P50;
__sbit __at(0xC8+1) P51;
__sbit __at(0xC8+2) P52;
__sbit __at(0xC8+3) P53;
__sbit __at(0xC8+4) P54;
__sbit __at(0xC8+5) P55;
__sbit __at(0xC8+6) P56;
__sbit __at(0xC8+7) P57;
__sfr __at(0xC9) P5M1;
__sfr __at(0xCA) P5M0;
__sfr __at(0xcb) P6M1;
__sfr __at(0xcc) P6M0;
__sfr __at(0xCD) SPSTAT;
__sfr __at(0xCE) SPCTL;
__sfr __at(0xCF) SPDAT;
__sfr __at(0xD0) PSW;
__sbit __at(0xD0+7) CY;
__sbit __at(0xD0+6) AC;
__sbit __at(0xD0+5) F0;
__sbit __at(0xD0+4) RS1;
__sbit __at(0xD0+3) RS0;
__sbit __at(0xD0+2) OV;
__sbit __at(0xD0+1) F1;
__sbit __at(0xD0+0) P;
__sfr __at(0xD1) T4T3M;
__sfr __at(0xD2) T4H;
__sfr __at(0xD3) T4L;
__sfr16 __at(0xD2D3) T4;
__sfr __at(0xD4) T3H;
__sfr __at(0xD5) T3L;
__sfr16 __at(0xD4D5) T3;
__sfr __at(0xD6) T2H;
__sfr __at(0xD7) T2L;
__sfr16 __at(0xD6D7) T2;
__sfr __at(0xD8) CCON;
__sbit __at(0xD8+7) CF;
__sbit __at(0xD8+6) CR;
__sbit __at(0xD8+2) CCF2;
__sbit __at(0xD8+1) CCF1;
__sbit __at(0xD8+0) CCF0;
__sfr __at(0xD9) CMOD;
__sfr __at(0xDA) CCAPM0;
__sfr __at(0xDB) CCAPM1;
__sfr __at(0xDC) CCAPM2;
__sfr __at(0xDE) ADCCFG;
__sfr __at(0xDF) IP3;
__sfr __at(0xE0) ACC;
__sfr __at(0xe1) P7M1;
__sfr __at(0xe2) P7M0;
__sfr __at(0xE3) DPS;
__sfr __at(0xE4) DPL1;
__sfr __at(0xE5) DPH1;
__sfr16 __at(0xE5E4) DP1;
__sfr __at(0xE6) CMPCR1;
__sfr __at(0xE7) CMPCR2;
__sfr __at(0xE8) P6;
__sbit __at(0xE8+0) P60;
__sbit __at(0xE8+1) P61;
__sbit __at(0xE8+2) P62;
__sbit __at(0xE8+3) P63;
__sbit __at(0xE8+4) P64;
__sbit __at(0xE8+5) P65;
__sbit __at(0xE8+6) P66;
__sbit __at(0xE8+7) P67;
__sfr __at(0xE9) CL;
__sfr __at(0xEA) CCAP0L;
__sfr __at(0xEB) CCAP1L;
__sfr __at(0xEC) CCAP2L;
__sfr __at(0xEE) IP3H;
__sfr __at(0xEF) AUXINTIF;
__sfr __at(0xF0) B;
__sfr __at(0xF1) PWMSET;
__sfr __at(0xF2) PCA_PWM0;
__sfr __at(0xF3) PCA_PWM1;
__sfr __at(0xF4) PCA_PWM2;
__sfr __at(0xF5) IAP_TPS;
__sfr __at(0xF6) PWMCFG01;
__sfr __at(0xF7) PWMCFG23;
__sfr __at(0xf8) P7;
__sbit __at(0xF8+0) P70;
__sbit __at(0xF8+1) P71;
__sbit __at(0xF8+2) P72;
__sbit __at(0xF8+3) P73;
__sbit __at(0xF8+4) P74;
__sbit __at(0xF8+5) P75;
__sbit __at(0xF8+6) P76;
__sbit __at(0xF8+7) P77;
__sfr __at(0xF9) CH;
__sfr16 __at(0xF9E9) C;
__sfr __at(0xFA) CCAP0H;
__sfr __at(0xFB) CCAP1H;
__sfr __at(0xFC) CCAP2H;
__sfr16 __at(0xFAEA) CCAP0;
__sfr16 __at(0xFBEB) CCAP1;
__sfr16 __at(0xFCEC) CCAP2;
__sfr __at(0xFE) PWMCFG45;
__sfr __at(0xFF) RSTCFG;

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////

volatile __xdata __at(0xff00) unsigned char PWM0CH;
volatile __xdata __at(0xff01) unsigned char PWM0CL;
volatile __xdata __at(0xff02) unsigned char PWM0CKS;

volatile __xdata __at(0xff03) unsigned char PWM0TADCH;
volatile __xdata __at(0xff04) unsigned char PWM0TADCL;
volatile __xdata __at(0xff05) unsigned char PWM0IF;
volatile __xdata __at(0xff06) unsigned char PWM0FDCR;

volatile __xdata __at(0xff11) unsigned char PWM00T1L;

volatile __xdata __at(0xff12) unsigned char PWM00T2H;
volatile __xdata __at(0xff13) unsigned char PWM00T2L;
volatile __xdata __at(0xff14) unsigned char PWM00CR;
volatile __xdata __at(0xff15) unsigned char PWM00HLD;

volatile __xdata __at(0xff18) unsigned char PWM01T1H;
volatile __xdata __at(0xff19) unsigned char PWM01T1L;

volatile __xdata __at(0xff1a) unsigned char PWM01T2H;
volatile __xdata __at(0xff1b) unsigned char PWM01T2L;
volatile __xdata __at(0xff1c) unsigned char PWM01CR;
volatile __xdata __at(0xff1d) unsigned char PWM01HLD;

volatile __xdata __at(0xff20) unsigned char PWM02T1H;
volatile __xdata __at(0xff21) unsigned char PWM02T1L;

volatile __xdata __at(0xff22) unsigned char PWM02T2H;
volatile __xdata __at(0xff23) unsigned char PWM02T2L;
volatile __xdata __at(0xff24) unsigned char PWM02CR;
volatile __xdata __at(0xff25) unsigned char PWM02HLD;

volatile __xdata __at(0xff28) unsigned char PWM03T1H;
volatile __xdata __at(0xff29) unsigned char PWM03T1L;

volatile __xdata __at(0xff2a) unsigned char PWM03T2H;
volatile __xdata __at(0xff2b) unsigned char PWM03T2L;
volatile __xdata __at(0xff2c) unsigned char PWM03CR;
volatile __xdata __at(0xff2d) unsigned char PWM03HLD;

volatile __xdata __at(0xff30) unsigned char PWM04T1H;
volatile __xdata __at(0xff31) unsigned char PWM04T1L;

volatile __xdata __at(0xff32) unsigned char PWM04T2H;
volatile __xdata __at(0xff33) unsigned char PWM04T2L;
volatile __xdata __at(0xff34) unsigned char PWM04CR;
volatile __xdata __at(0xff35) unsigned char PWM04HLD;

volatile __xdata __at(0xff38) unsigned char PWM05T1H;
volatile __xdata __at(0xff39) unsigned char PWM05T1L;

volatile __xdata __at(0xff3a) unsigned char PWM05T2H;
volatile __xdata __at(0xff3b) unsigned char PWM05T2L;
volatile __xdata __at(0xff3c) unsigned char PWM05CR;
volatile __xdata __at(0xff3d) unsigned char PWM05HLD;

volatile __xdata __at(0xff40) unsigned char PWM06T1H;
volatile __xdata __at(0xff41) unsigned char PWM06T1L;

volatile __xdata __at(0xff42) unsigned char PWM06T2H;
volatile __xdata __at(0xff43) unsigned char PWM06T2L;
volatile __xdata __at(0xff44) unsigned char PWM06CR;
volatile __xdata __at(0xff45) unsigned char PWM06HLD;

volatile __xdata __at(0xff48) unsigned char PWM07T1H;
volatile __xdata __at(0xff49) unsigned char PWM07T1L;

volatile __xdata __at(0xff4a) unsigned char PWM07T2H;
volatile __xdata __at(0xff4b) unsigned char PWM07T2L;
volatile __xdata __at(0xff4c) unsigned char PWM07CR;
volatile __xdata __at(0xff4d) unsigned char PWM07HLD;

volatile __xdata __at(0xff50) unsigned char PWM1CH;
volatile __xdata __at(0xff51) unsigned char PWM1CL;
volatile __xdata __at(0xff52) unsigned char PWM1CKS;
volatile __xdata __at(0xff55) unsigned char PWM1IF;
volatile __xdata __at(0xff56) unsigned char PWM1FDCR;

volatile __xdata __at(0xff60) unsigned char PWM10T1H;
volatile __xdata __at(0xff61) unsigned char PWM10T1L;

volatile __xdata __at(0xff62) unsigned char PWM10T2H;
volatile __xdata __at(0xff63) unsigned char PWM10T2L;
volatile __xdata __at(0xff64) unsigned char PWM10CR;
volatile __xdata __at(0xff65) unsigned char PWM10HLD;

volatile __xdata __at(0xff68) unsigned char PWM11T1H;
volatile __xdata __at(0xff69) unsigned char PWM11T1L;

volatile __xdata __at(0xff6a) unsigned char PWM11T2H;
volatile __xdata __at(0xff6b) unsigned char PWM11T2L;
volatile __xdata __at(0xff6c) unsigned char PWM11CR;
volatile __xdata __at(0xff6d) unsigned char PWM11HLD;

volatile __xdata __at(0xff70) unsigned char PWM12T1H;
volatile __xdata __at(0xff71) unsigned char PWM12T1L;

volatile __xdata __at(0xff72) unsigned char PWM12T2H;
volatile __xdata __at(0xff73) unsigned char PWM12T2L;
volatile __xdata __at(0xff74) unsigned char PWM12CR;
volatile __xdata __at(0xff75) unsigned char PWM12HLD;

volatile __xdata __at(0xff78) unsigned char PWM13T1H;
volatile __xdata __at(0xff79) unsigned char PWM13T1L;

volatile __xdata __at(0xff7a) unsigned char PWM13T2H;
volatile __xdata __at(0xff7b) unsigned char PWM13T2L;
volatile __xdata __at(0xff7c) unsigned char PWM13CR;
volatile __xdata __at(0xff7d) unsigned char PWM13HLD;

volatile __xdata __at(0xff80) unsigned char PWM14T1H;
volatile __xdata __at(0xff81) unsigned char PWM14T1L;

volatile __xdata __at(0xff82) unsigned char PWM14T2H;
volatile __xdata __at(0xff83) unsigned char PWM14T2L;
volatile __xdata __at(0xff84) unsigned char PWM14CR;
volatile __xdata __at(0xff85) unsigned char PWM14HLD;

volatile __xdata __at(0xff88) unsigned char PWM15T1H;
volatile __xdata __at(0xff89) unsigned char PWM15T1L;

volatile __xdata __at(0xff8a) unsigned char PWM15T2H;
volatile __xdata __at(0xff8b) unsigned char PWM15T2L;
volatile __xdata __at(0xff8c) unsigned char PWM15CR;
volatile __xdata __at(0xff8d) unsigned char PWM15HLD;

volatile __xdata __at(0xff90) unsigned char PWM16T1H;
volatile __xdata __at(0xff91) unsigned char PWM16T1L;

volatile __xdata __at(0xff92) unsigned char PWM16T2H;
volatile __xdata __at(0xff93) unsigned char PWM16T2L;
volatile __xdata __at(0xff94) unsigned char PWM16CR;
volatile __xdata __at(0xff95) unsigned char PWM16HLD;

volatile __xdata __at(0xff98) unsigned char PWM17T1H;
volatile __xdata __at(0xff99) unsigned char PWM17T1L;

volatile __xdata __at(0xff9a) unsigned char PWM17T2H;
volatile __xdata __at(0xff9b) unsigned char PWM17T2L;
volatile __xdata __at(0xff9c) unsigned char PWM17CR;
volatile __xdata __at(0xff9d) unsigned char PWM17HLD;

volatile __xdata __at(0xffa0) unsigned char PWM2CH;
volatile __xdata __at(0xffa1) unsigned char PWM2CL;
volatile __xdata __at(0xffa2) unsigned char PWM2CKS;

volatile __xdata __at(0xffa3) unsigned char PWM2TADCH;
volatile __xdata __at(0xffa4) unsigned char PWM2TADCL;
volatile __xdata __at(0xffa5) unsigned char PWM2IF;
volatile __xdata __at(0xffa6) unsigned char PWM2FDCR;

volatile __xdata __at(0xffb0) unsigned char PWM20T1H;
volatile __xdata __at(0xffb1) unsigned char PWM20T1L;

volatile __xdata __at(0xffb2) unsigned char PWM20T2H;
volatile __xdata __at(0xffb3) unsigned char PWM20T2L;
volatile __xdata __at(0xffb4) unsigned char PWM20CR;
volatile __xdata __at(0xffb5) unsigned char PWM20HLD;

volatile __xdata __at(0xffb8) unsigned char PWM21T1H;
volatile __xdata __at(0xffb9) unsigned char PWM21T1L;

volatile __xdata __at(0xffba) unsigned char PWM21T2H;
volatile __xdata __at(0xffbb) unsigned char PWM21T2L;
volatile __xdata __at(0xffbc) unsigned char PWM21CR;
volatile __xdata __at(0xffbd) unsigned char PWM21HLD;

volatile __xdata __at(0xffc0) unsigned char PWM22T1H;
volatile __xdata __at(0xffc1) unsigned char PWM22T1L;

volatile __xdata __at(0xffc2) unsigned char PWM22T2H;
volatile __xdata __at(0xffc3) unsigned char PWM22T2L;
volatile __xdata __at(0xffc4) unsigned char PWM22CR;
volatile __xdata __at(0xffc5) unsigned char PWM22HLD;

volatile __xdata __at(0xffc8) unsigned char PWM23T1H;
volatile __xdata __at(0xffc9) unsigned char PWM23T1L;

volatile __xdata __at(0xffca) unsigned char PWM23T2H;
volatile __xdata __at(0xffcb) unsigned char PWM23T2L;
volatile __xdata __at(0xffcc) unsigned char PWM23CR;
volatile __xdata __at(0xffcd) unsigned char PWM23HLD;

volatile __xdata __at(0xffd0) unsigned char PWM24T1H;
volatile __xdata __at(0xffd1) unsigned char PWM24T1L;

volatile __xdata __at(0xffd2) unsigned char PWM24T2H;
volatile __xdata __at(0xffd3) unsigned char PWM24T2L;
volatile __xdata __at(0xffd4) unsigned char PWM24CR;
volatile __xdata __at(0xffd5) unsigned char PWM24HLD;

volatile __xdata __at(0xffd8) unsigned char PWM25T1H;
volatile __xdata __at(0xffd9) unsigned char PWM25T1L;

volatile __xdata __at(0xffda) unsigned char PWM25T2H;
volatile __xdata __at(0xffdb) unsigned char PWM25T2L;
volatile __xdata __at(0xffdc) unsigned char PWM25CR;
volatile __xdata __at(0xffdd) unsigned char PWM25HLD;

volatile __xdata __at(0xffe0) unsigned char PWM26T1H;
volatile __xdata __at(0xffe1) unsigned char PWM26T1L;

volatile __xdata __at(0xffe2) unsigned char PWM26T2H;
volatile __xdata __at(0xffe3) unsigned char PWM26T2L;
volatile __xdata __at(0xffe4) unsigned char PWM26CR;
volatile __xdata __at(0xffe5) unsigned char PWM26HLD;

volatile __xdata __at(0xffe8) unsigned char PWM27T1H;
volatile __xdata __at(0xffe9) unsigned char PWM27T1L;

volatile __xdata __at(0xffea) unsigned char PWM27T2H;
volatile __xdata __at(0xffeb) unsigned char PWM27T2L;
volatile __xdata __at(0xffec) unsigned char PWM27CR;
volatile __xdata __at(0xffed) unsigned char PWM27HLD;

/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

volatile __xdata __at(0xfe00) unsigned char CLKSEL;
volatile __xdata __at(0xfe01) unsigned char CLKDIV;
volatile __xdata __at(0xfe02) unsigned char HIRCCR;
volatile __xdata __at(0xfe03) unsigned char XOSCCR;
volatile __xdata __at(0xfe04) unsigned char IRC32KCR;
volatile __xdata __at(0xfe05) unsigned char MCLKOCR;
volatile __xdata __at(0xfe06) unsigned char IRCDB;
volatile __xdata __at(0xfe08) unsigned char X32KCR;

volatile __xdata __at(0xfe10) unsigned char P0PU;
volatile __xdata __at(0xfe11) unsigned char P1PU;
volatile __xdata __at(0xfe12) unsigned char P2PU;
volatile __xdata __at(0xfe13) unsigned char P3PU;
volatile __xdata __at(0xfe14) unsigned char P4PU;
volatile __xdata __at(0xfe15) unsigned char P5PU;
volatile __xdata __at(0xfe16) unsigned char P6PU;
volatile __xdata __at(0xfe17) unsigned char P7PU;
volatile __xdata __at(0xfe18) unsigned char P0NCS;
volatile __xdata __at(0xfe19) unsigned char P1NCS;
volatile __xdata __at(0xfe1a) unsigned char P2NCS;
volatile __xdata __at(0xfe1b) unsigned char P3NCS;
volatile __xdata __at(0xfe1c) unsigned char P4NCS;
volatile __xdata __at(0xfe1d) unsigned char P5NCS;
volatile __xdata __at(0xfe1e) unsigned char P6NCS;
volatile __xdata __at(0xfe1f) unsigned char P7NCS;
volatile __xdata __at(0xfe20) unsigned char P0SR;
volatile __xdata __at(0xfe21) unsigned char P1SR;
volatile __xdata __at(0xfe22) unsigned char P2SR;
volatile __xdata __at(0xfe23) unsigned char P3SR;
volatile __xdata __at(0xfe24) unsigned char P4SR;
volatile __xdata __at(0xfe25) unsigned char P5SR;
volatile __xdata __at(0xfe26) unsigned char P6SR;
volatile __xdata __at(0xfe27) unsigned char P7SR;
volatile __xdata __at(0xfe28) unsigned char P0DR;
volatile __xdata __at(0xfe29) unsigned char P1DR;
volatile __xdata __at(0xfe2a) unsigned char P2DR;
volatile __xdata __at(0xfe2b) unsigned char P3DR;
volatile __xdata __at(0xfe2c) unsigned char P4DR;
volatile __xdata __at(0xfe2d) unsigned char P5DR;
volatile __xdata __at(0xfe2e) unsigned char P6DR;
volatile __xdata __at(0xfe2f) unsigned char P7DR;
volatile __xdata __at(0xfe30) unsigned char P0IE;
volatile __xdata __at(0xfe31) unsigned char P1IE;
volatile __xdata __at(0xfe32) unsigned char P2IE;
volatile __xdata __at(0xfe33) unsigned char P3IE;
volatile __xdata __at(0xfe34) unsigned char P4IE;
volatile __xdata __at(0xfe35) unsigned char P5IE;
volatile __xdata __at(0xfe36) unsigned char P6IE;
volatile __xdata __at(0xfe37) unsigned char P7IE;

volatile __xdata __at(0xfe60) unsigned char RTCCR;
volatile __xdata __at(0xfe61) unsigned char RTCCFG;
volatile __xdata __at(0xfe62) unsigned char RTCIEN;
volatile __xdata __at(0xfe63) unsigned char RTCIF;
volatile __xdata __at(0xfe64) unsigned char ALAHOUR;
volatile __xdata __at(0xfe65) unsigned char ALAMIN;
volatile __xdata __at(0xfe66) unsigned char ALASEC;
volatile __xdata __at(0xfe67) unsigned char ALASSEC;
volatile __xdata __at(0xfe68) unsigned char INIYEAR;
volatile __xdata __at(0xfe69) unsigned char INIMONTH;
volatile __xdata __at(0xfe6a) unsigned char INIDAY;
volatile __xdata __at(0xfe6b) unsigned char INIHOUR;
volatile __xdata __at(0xfe6c) unsigned char INIMIN;
volatile __xdata __at(0xfe6d) unsigned char INISEC;
volatile __xdata __at(0xfe6e) unsigned char INISSEC;
volatile __xdata __at(0xfe70) unsigned char YEAR;
volatile __xdata __at(0xfe71) unsigned char MONTH;
volatile __xdata __at(0xfe72) unsigned char DAY;
volatile __xdata __at(0xfe73) unsigned char HOUR;
volatile __xdata __at(0xfe74) unsigned char MIN;
volatile __xdata __at(0xfe75) unsigned char SEC;
volatile __xdata __at(0xfe76) unsigned char SSEC;

volatile __xdata __at(0xfe80) unsigned char I2CCFG;
volatile __xdata __at(0xfe81) unsigned char I2CMSCR;
volatile __xdata __at(0xfe82) unsigned char I2CMSST;
volatile __xdata __at(0xfe83) unsigned char I2CSLCR;
volatile __xdata __at(0xfe84) unsigned char I2CSLST;
volatile __xdata __at(0xfe85) unsigned char I2CSLADR;
volatile __xdata __at(0xfe86) unsigned char I2CTXD;
volatile __xdata __at(0xfe87) unsigned char I2CRXD;
volatile __xdata __at(0xfe88) unsigned char I2CMSAUX;

volatile __xdata __at(0xfea2) unsigned char TM2PS;
volatile __xdata __at(0xfea3) unsigned char TM3PS;
volatile __xdata __at(0xfea4) unsigned char TM4PS;
volatile __xdata __at(0xfea8) unsigned char ADCTIM;
volatile __xdata __at(0xfeac) unsigned char T3T4PS;

/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

volatile __xdata __at(0xfd00) unsigned char P0INTE;
volatile __xdata __at(0xfd01) unsigned char P1INTE;
volatile __xdata __at(0xfd02) unsigned char P2INTE;
volatile __xdata __at(0xfd03) unsigned char P3INTE;
volatile __xdata __at(0xfd04) unsigned char P4INTE;
volatile __xdata __at(0xfd05) unsigned char P5INTE;
volatile __xdata __at(0xfd06) unsigned char P6INTE;
volatile __xdata __at(0xfd07) unsigned char P7INTE;
volatile __xdata __at(0xfd10) unsigned char P0INTF;
volatile __xdata __at(0xfd11) unsigned char P1INTF;
volatile __xdata __at(0xfd12) unsigned char P2INTF;
volatile __xdata __at(0xfd13) unsigned char P3INTF;
volatile __xdata __at(0xfd14) unsigned char P4INTF;
volatile __xdata __at(0xfd15) unsigned char P5INTF;
volatile __xdata __at(0xfd16) unsigned char P6INTF;
volatile __xdata __at(0xfd17) unsigned char P7INTF;
volatile __xdata __at(0xfd20) unsigned char P0IM0;
volatile __xdata __at(0xfd21) unsigned char P1IM0;
volatile __xdata __at(0xfd22) unsigned char P2IM0;
volatile __xdata __at(0xfd23) unsigned char P3IM0;
volatile __xdata __at(0xfd24) unsigned char P4IM0;
volatile __xdata __at(0xfd25) unsigned char P5IM0;
volatile __xdata __at(0xfd26) unsigned char P6IM0;
volatile __xdata __at(0xfd27) unsigned char P7IM0;
volatile __xdata __at(0xfd30) unsigned char P0IM1;
volatile __xdata __at(0xfd31) unsigned char P1IM1;
volatile __xdata __at(0xfd32) unsigned char P2IM1;
volatile __xdata __at(0xfd33) unsigned char P3IM1;
volatile __xdata __at(0xfd34) unsigned char P4IM1;
volatile __xdata __at(0xfd35) unsigned char P5IM1;
volatile __xdata __at(0xfd36) unsigned char P6IM1;
volatile __xdata __at(0xfd37) unsigned char P7IM1;
volatile __xdata __at(0xfd40) unsigned char P0WKUE;
volatile __xdata __at(0xfd41) unsigned char P1WKUE;
volatile __xdata __at(0xfd42) unsigned char P2WKUE;
volatile __xdata __at(0xfd43) unsigned char P3WKUE;
volatile __xdata __at(0xfd44) unsigned char P4WKUE;
volatile __xdata __at(0xfd45) unsigned char P5WKUE;
volatile __xdata __at(0xfd46) unsigned char P6WKUE;
volatile __xdata __at(0xfd47) unsigned char P7WKUE;
volatile __xdata __at(0xfd60) unsigned char PIN_IP;
volatile __xdata __at(0xfd61) unsigned char PIN_IPH;

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////


volatile __xdata __at(0xfc00) unsigned char PWM3CH;
volatile __xdata __at(0xfc01) unsigned char PWM3CL;
volatile __xdata __at(0xfc02) unsigned char PWM3CKS;
volatile __xdata __at(0xfc05) unsigned char PWM3IF;
volatile __xdata __at(0xfc06) unsigned char PWM3FDCR;

volatile __xdata __at(0xfc10) unsigned char PWM30T1H;
volatile __xdata __at(0xfc11) unsigned char PWM30T1L;

volatile __xdata __at(0xfc12) unsigned char PWM30T2H;
volatile __xdata __at(0xfc13) unsigned char PWM30T2L;
volatile __xdata __at(0xfc14) unsigned char PWM30CR;
volatile __xdata __at(0xfc15) unsigned char PWM30HLD;

volatile __xdata __at(0xfc18) unsigned char PWM31T1H;
volatile __xdata __at(0xfc19) unsigned char PWM31T1L;

volatile __xdata __at(0xfc1a) unsigned char PWM31T2H;
volatile __xdata __at(0xfc1b) unsigned char PWM31T2L;
volatile __xdata __at(0xfc1c) unsigned char PWM31CR;
volatile __xdata __at(0xfc1d) unsigned char PWM31HLD;

volatile __xdata __at(0xfc20) unsigned char PWM32T1H;
volatile __xdata __at(0xfc21) unsigned char PWM32T1L;

volatile __xdata __at(0xfc22) unsigned char PWM32T2H;
volatile __xdata __at(0xfc23) unsigned char PWM32T2L;
volatile __xdata __at(0xfc24) unsigned char PWM32CR;
volatile __xdata __at(0xfc25) unsigned char PWM32HLD;

volatile __xdata __at(0xfc28) unsigned char PWM33T1H;
volatile __xdata __at(0xfc29) unsigned char PWM33T1L;

volatile __xdata __at(0xfc2a) unsigned char PWM33T2H;
volatile __xdata __at(0xfc2b) unsigned char PWM33T2L;
volatile __xdata __at(0xfc2c) unsigned char PWM33CR;
volatile __xdata __at(0xfc2d) unsigned char PWM33HLD;

volatile __xdata __at(0xfc30) unsigned char PWM34T1H;
volatile __xdata __at(0xfc31) unsigned char PWM34T1L;

volatile __xdata __at(0xfc32) unsigned char PWM34T2H;
volatile __xdata __at(0xfc33) unsigned char PWM34T2L;
volatile __xdata __at(0xfc34) unsigned char PWM34CR;
volatile __xdata __at(0xfc35) unsigned char PWM34HLD;

volatile __xdata __at(0xfc38) unsigned char PWM35T1H;
volatile __xdata __at(0xfc39) unsigned char PWM35T1L;

volatile __xdata __at(0xfc3a) unsigned char PWM35T2H;
volatile __xdata __at(0xfc3b) unsigned char PWM35T2L;
volatile __xdata __at(0xfc3c) unsigned char PWM35CR;
volatile __xdata __at(0xfc3d) unsigned char PWM35HLD;

volatile __xdata __at(0xfc40) unsigned char PWM36T1H;
volatile __xdata __at(0xfc41) unsigned char PWM36T1L;

volatile __xdata __at(0xfc42) unsigned char PWM36T2H;
volatile __xdata __at(0xfc43) unsigned char PWM36T2L;
volatile __xdata __at(0xfc44) unsigned char PWM36CR;
volatile __xdata __at(0xfc45) unsigned char PWM36HLD;

volatile __xdata __at(0xfc48) unsigned char PWM37T1H;
volatile __xdata __at(0xfc49) unsigned char PWM37T1L;

volatile __xdata __at(0xfc4a) unsigned char PWM37T2H;
volatile __xdata __at(0xfc4b) unsigned char PWM37T2L;
volatile __xdata __at(0xfc4c) unsigned char PWM37CR;
volatile __xdata __at(0xfc4d) unsigned char PWM37HLD;

volatile __xdata __at(0xfc50) unsigned char PWM4CH;
volatile __xdata __at(0xfc51) unsigned char PWM4CL;
volatile __xdata __at(0xfc52) unsigned char PWM4CKS;

volatile __xdata __at(0xfc53) unsigned char PWM4TADCH;
volatile __xdata __at(0xfc54) unsigned char PWM4TADCL;
volatile __xdata __at(0xfc55) unsigned char PWM4IF;
volatile __xdata __at(0xfc56) unsigned char PWM4FDCR;

volatile __xdata __at(0xfc60) unsigned char PWM40T1H;
volatile __xdata __at(0xfc61) unsigned char PWM40T1L;

volatile __xdata __at(0xfc62) unsigned char PWM40T2H;
volatile __xdata __at(0xfc63) unsigned char PWM40T2L;
volatile __xdata __at(0xfc64) unsigned char PWM40CR;
volatile __xdata __at(0xfc65) unsigned char PWM40HLD;

volatile __xdata __at(0xfc68) unsigned char PWM41T1H;
volatile __xdata __at(0xfc69) unsigned char PWM41T1L;

volatile __xdata __at(0xfc6a) unsigned char PWM41T2H;
volatile __xdata __at(0xfc6b) unsigned char PWM41T2L;
volatile __xdata __at(0xfc6c) unsigned char PWM41CR;
volatile __xdata __at(0xfc6d) unsigned char PWM41HLD;

volatile __xdata __at(0xfc70) unsigned char PWM42T1H;
volatile __xdata __at(0xfc71) unsigned char PWM42T1L;

volatile __xdata __at(0xfc72) unsigned char PWM42T2H;
volatile __xdata __at(0xfc73) unsigned char PWM42T2L;
volatile __xdata __at(0xfc74) unsigned char PWM42CR;
volatile __xdata __at(0xfc75) unsigned char PWM42HLD;

volatile __xdata __at(0xfc78) unsigned char PWM43T1H;
volatile __xdata __at(0xfc79) unsigned char PWM43T1L;

volatile __xdata __at(0xfc7a) unsigned char PWM43T2H;
volatile __xdata __at(0xfc7b) unsigned char PWM43T2L;
volatile __xdata __at(0xfc7c) unsigned char PWM43CR;
volatile __xdata __at(0xfc7d) unsigned char PWM43HLD;

volatile __xdata __at(0xfc80) unsigned char PWM44T1H;
volatile __xdata __at(0xfc81) unsigned char PWM44T1L;

volatile __xdata __at(0xfc82) unsigned char PWM44T2H;
volatile __xdata __at(0xfc83) unsigned char PWM44T2L;
volatile __xdata __at(0xfc84) unsigned char PWM44CR;
volatile __xdata __at(0xfc85) unsigned char PWM44HLD;

volatile __xdata __at(0xfc88) unsigned char PWM45T1H;
volatile __xdata __at(0xfc89) unsigned char PWM45T1L;

volatile __xdata __at(0xfc8a) unsigned char PWM45T2H;
volatile __xdata __at(0xfc8b) unsigned char PWM45T2L;
volatile __xdata __at(0xfc8c) unsigned char PWM45CR;
volatile __xdata __at(0xfc8d) unsigned char PWM45HLD;

volatile __xdata __at(0xfc90) unsigned char PWM46T1H;
volatile __xdata __at(0xfc91) unsigned char PWM46T1L;

volatile __xdata __at(0xfc92) unsigned char PWM46T2H;
volatile __xdata __at(0xfc93) unsigned char PWM46T2L;
volatile __xdata __at(0xfc94) unsigned char PWM46CR;
volatile __xdata __at(0xfc95) unsigned char PWM46HLD;

volatile __xdata __at(0xfc98) unsigned char PWM47T1H;
volatile __xdata __at(0xfc99) unsigned char PWM47T1L;

volatile __xdata __at(0xfc9a) unsigned char PWM47T2H;
volatile __xdata __at(0xfc9b) unsigned char PWM47T2L;
volatile __xdata __at(0xfc9c) unsigned char PWM47CR;
volatile __xdata __at(0xfc9d) unsigned char PWM47HLD;

volatile __xdata __at(0xfca0) unsigned char PWM5CH;
volatile __xdata __at(0xfca1) unsigned char PWM5CL;
volatile __xdata __at(0xfca2) unsigned char PWM5CKS;
volatile __xdata __at(0xfca5) unsigned char PWM5IF;
volatile __xdata __at(0xfca6) unsigned char PWM5FDCR;

volatile __xdata __at(0xfcb0) unsigned char PWM50T1H;
volatile __xdata __at(0xfcb1) unsigned char PWM50T1L;

volatile __xdata __at(0xfcb2) unsigned char PWM50T2H;
volatile __xdata __at(0xfcb3) unsigned char PWM50T2L;
volatile __xdata __at(0xfcb4) unsigned char PWM50CR;
volatile __xdata __at(0xfcb5) unsigned char PWM50HLD;

volatile __xdata __at(0xfcb8) unsigned char PWM51T1H;
volatile __xdata __at(0xfcb9) unsigned char PWM51T1L;

volatile __xdata __at(0xfcba) unsigned char PWM51T2H;
volatile __xdata __at(0xfcbb) unsigned char PWM51T2L;
volatile __xdata __at(0xfcbc) unsigned char PWM51CR;
volatile __xdata __at(0xfcbd) unsigned char PWM51HLD;

volatile __xdata __at(0xfcc0) unsigned char PWM52T1H;
volatile __xdata __at(0xfcc1) unsigned char PWM52T1L;

volatile __xdata __at(0xfcc2) unsigned char PWM52T2H;
volatile __xdata __at(0xfcc3) unsigned char PWM52T2L;
volatile __xdata __at(0xfcc4) unsigned char PWM52CR;
volatile __xdata __at(0xfcc5) unsigned char PWM52HLD;

volatile __xdata __at(0xfcc8) unsigned char PWM53T1H;
volatile __xdata __at(0xfcc9) unsigned char PWM53T1L;

volatile __xdata __at(0xfcca) unsigned char PWM53T2H;
volatile __xdata __at(0xfccb) unsigned char PWM53T2L;
volatile __xdata __at(0xfccc) unsigned char PWM53CR;
volatile __xdata __at(0xfccd) unsigned char PWM53HLD;

volatile __xdata __at(0xfcd0) unsigned char PWM54T1H;
volatile __xdata __at(0xfcd1) unsigned char PWM54T1L;

volatile __xdata __at(0xfcd2) unsigned char PWM54T2H;
volatile __xdata __at(0xfcd3) unsigned char PWM54T2L;
volatile __xdata __at(0xfcd4) unsigned char PWM54CR;
volatile __xdata __at(0xfcd5) unsigned char PWM54HLD;

volatile __xdata __at(0xfcd8) unsigned char PWM55T1H;
volatile __xdata __at(0xfcd9) unsigned char PWM55T1L;

volatile __xdata __at(0xfcda) unsigned char PWM55T2H;
volatile __xdata __at(0xfcdb) unsigned char PWM55T2L;
volatile __xdata __at(0xfcdc) unsigned char PWM55CR;
volatile __xdata __at(0xfcdd) unsigned char PWM55HLD;

volatile __xdata __at(0xfce0) unsigned char PWM56T1H;
volatile __xdata __at(0xfce1) unsigned char PWM56T1L;

volatile __xdata __at(0xfce2) unsigned char PWM56T2H;
volatile __xdata __at(0xfce3) unsigned char PWM56T2L;
volatile __xdata __at(0xfce4) unsigned char PWM56CR;
volatile __xdata __at(0xfce5) unsigned char PWM56HLD;

volatile __xdata __at(0xfce8) unsigned char PWM57T1H;
volatile __xdata __at(0xfce9) unsigned char PWM57T1L;

volatile __xdata __at(0xfcea) unsigned char PWM57T2H;
volatile __xdata __at(0xfceb) unsigned char PWM57T2L;
volatile __xdata __at(0xfcec) unsigned char PWM57CR;
volatile __xdata __at(0xfced) unsigned char PWM57HLD;

volatile __xdata __at(0xfcf0) unsigned char MD3;
volatile __xdata __at(0xfcf1) unsigned char MD2;
volatile __xdata __at(0xfcf2) unsigned char MD1;
volatile __xdata __at(0xfcf3) unsigned char MD0;
volatile __xdata __at(0xfcf4) unsigned char MD5;
volatile __xdata __at(0xfcf5) unsigned char MD4;
volatile __xdata __at(0xfcf6) unsigned char ARCON;
volatile __xdata __at(0xfcf7) unsigned char OPCON;

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////

volatile __xdata __at(0xfb00) unsigned char COMEN;
volatile __xdata __at(0xfb01) unsigned char SEGENL;
volatile __xdata __at(0xfb02) unsigned char SEGENH;
volatile __xdata __at(0xfb03) unsigned char LEDCTRL;
volatile __xdata __at(0xfb04) unsigned char LEDCKS;
volatile __xdata __at(0xfb10) unsigned char COM0_DA_L;
volatile __xdata __at(0xfb11) unsigned char COM1_DA_L;
volatile __xdata __at(0xfb12) unsigned char COM2_DA_L;
volatile __xdata __at(0xfb13) unsigned char COM3_DA_L;
volatile __xdata __at(0xfb14) unsigned char COM4_DA_L;
volatile __xdata __at(0xfb15) unsigned char COM5_DA_L;
volatile __xdata __at(0xfb16) unsigned char COM6_DA_L;
volatile __xdata __at(0xfb17) unsigned char COM7_DA_L;
volatile __xdata __at(0xfb18) unsigned char COM0_DA_H;
volatile __xdata __at(0xfb19) unsigned char COM1_DA_H;
volatile __xdata __at(0xfb1a) unsigned char COM2_DA_H;
volatile __xdata __at(0xfb1b) unsigned char COM3_DA_H;
volatile __xdata __at(0xfb1c) unsigned char COM4_DA_H;
volatile __xdata __at(0xfb1d) unsigned char COM5_DA_H;
volatile __xdata __at(0xfb1e) unsigned char COM6_DA_H;
volatile __xdata __at(0xfb1f) unsigned char COM7_DA_H;
volatile __xdata __at(0xfb20) unsigned char COM0_DC_L;
volatile __xdata __at(0xfb21) unsigned char COM1_DC_L;
volatile __xdata __at(0xfb22) unsigned char COM2_DC_L;
volatile __xdata __at(0xfb23) unsigned char COM3_DC_L;
volatile __xdata __at(0xfb24) unsigned char COM4_DC_L;
volatile __xdata __at(0xfb25) unsigned char COM5_DC_L;
volatile __xdata __at(0xfb26) unsigned char COM6_DC_L;
volatile __xdata __at(0xfb27) unsigned char COM7_DC_L;
volatile __xdata __at(0xfb28) unsigned char COM0_DC_H;
volatile __xdata __at(0xfb29) unsigned char COM1_DC_H;
volatile __xdata __at(0xfb2a) unsigned char COM2_DC_H;
volatile __xdata __at(0xfb2b) unsigned char COM3_DC_H;
volatile __xdata __at(0xfb2c) unsigned char COM4_DC_H;
volatile __xdata __at(0xfb2d) unsigned char COM5_DC_H;
volatile __xdata __at(0xfb2e) unsigned char COM6_DC_H;
volatile __xdata __at(0xfb2f) unsigned char COM7_DC_H;

volatile __xdata __at(0xfb40) unsigned char TSCHEN1;
volatile __xdata __at(0xfb41) unsigned char TSCHEN2;
volatile __xdata __at(0xfb42) unsigned char TSCFG1;
volatile __xdata __at(0xfb43) unsigned char TSCFG2;
volatile __xdata __at(0xfb44) unsigned char TSWUTC;
volatile __xdata __at(0xfb45) unsigned char TSCTRL;
volatile __xdata __at(0xfb46) unsigned char TSSTA1;
volatile __xdata __at(0xfb47) unsigned char TSSTA2;
volatile __xdata __at(0xfb48) unsigned char TSRT;

volatile __xdata __at(0xfb49) unsigned char TSDATH;
volatile __xdata __at(0xfb4a) unsigned char TSDATL;

volatile __xdata __at(0xfb50) unsigned char TSTH00H;
volatile __xdata __at(0xfb51) unsigned char TSTH00L;

volatile __xdata __at(0xfb52) unsigned char TSTH01H;
volatile __xdata __at(0xfb53) unsigned char TSTH01L;

volatile __xdata __at(0xfb54) unsigned char TSTH02H;
volatile __xdata __at(0xfb55) unsigned char TSTH02L;

volatile __xdata __at(0xfb56) unsigned char TSTH03H;
volatile __xdata __at(0xfb57) unsigned char TSTH03L;

volatile __xdata __at(0xfb58) unsigned char TSTH04H;
volatile __xdata __at(0xfb59) unsigned char TSTH04L;

volatile __xdata __at(0xfb5a) unsigned char TSTH05H;
volatile __xdata __at(0xfb5b) unsigned char TSTH05L;

volatile __xdata __at(0xfb5c) unsigned char TSTH06H;
volatile __xdata __at(0xfb5d) unsigned char TSTH06L;

volatile __xdata __at(0xfb5e) unsigned char TSTH07H;
volatile __xdata __at(0xfb5f) unsigned char TSTH07L;

volatile __xdata __at(0xfb60) unsigned char TSTH08H;
volatile __xdata __at(0xfb61) unsigned char TSTH08L;

volatile __xdata __at(0xfb62) unsigned char TSTH09H;
volatile __xdata __at(0xfb63) unsigned char TSTH09L;

volatile __xdata __at(0xfb64) unsigned char TSTH10H;
volatile __xdata __at(0xfb65) unsigned char TSTH10L;

volatile __xdata __at(0xfb66) unsigned char TSTH11H;
volatile __xdata __at(0xfb67) unsigned char TSTH11L;

volatile __xdata __at(0xfb68) unsigned char TSTH12H;
volatile __xdata __at(0xfb69) unsigned char TSTH12L;

volatile __xdata __at(0xfb6a) unsigned char TSTH13H;
volatile __xdata __at(0xfb6b) unsigned char TSTH13L;

volatile __xdata __at(0xfb6c) unsigned char TSTH14H;
volatile __xdata __at(0xfb6d) unsigned char TSTH14L;

volatile __xdata __at(0xfb6e) unsigned char TSTH15H;
volatile __xdata __at(0xfb6f) unsigned char TSTH15L;

/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////


/////////////////////////////////////////////////

#endif

