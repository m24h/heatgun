// Copyright 2003 m24h, see http://www.apache.org/licenses/LICENSE-2.0

#include "K.h"

// a table of uV/256 => Temp*32 ,  in Celsius degree
__code u16 K_TEMP_FP5[]={
0,
207,
412,
616,
819,
1021,
1221,
1421,
1620,
1818,
2016,
2214,
2411,
2608,
2806,
3003,
3201,
3399,
3598,
3797,
3997,
4198,
4400,
4602,
4805,
5009,
5214,
5418,
5623,
5829,
6034,
6239,
6444,
6650,
6853,
7058,
7261,
7464,
7666,
7869,
8070,
8270,
8471,
8670,
8869,
9068,
9266,
9464,
9662,
9860,
10057,
10253,
10450,
10646,
10842,
11038,
11234,
11429,
11624,
11819,
12014,
12209,
12403,
12597,
12791,
12985,
13179,
13373,
13566,
13760,
13953,
14146,
14339,
14532,
14724,
14917,
15110,
15303,
15495,
15687,
15880,
16072,
16264,
16456,
16649,
16840,
17033,
17225,
17417,
17609,
17801,
17993,
18186,
18378,
18570,
18763,
18955,
19148,
19340,
19533,
19726,
19919,
20112,
20305,
20499,
20692,
20886,
21080,
21274,
21468,
21662,
21858,
22052,
22247,
22443,
22638,
22834,
23030,
23226,
23422,
23619,
23816,
24014,
24211,
24409,
24607,
24806,
25004,
25203,
25403,
25602,
25802,
26003,
26204,
26404,
26605,
26807,
27009,
27211,
27413,
27617,
27820,
28023,
28227,
28432,
28636,
28841,
29047,
29252,
29458,
29664,
29871,
30078,
30285,
30493,
30701,
30909,
31118,
31327,
31536,
31746,
31957,
32167,
32378,
32589,
32801,
33013,
33226,
33439,
33652,
33865,
34079,
34294,
34508,
34724,
34940,
35155,
35372,
35590,
35807,
36025,
36244,
36463,
36682,
36903,
37123,
37344,
37567,
37789,
38012,
38235,
38459,
38684,
38910,
39137,
39364,
39591,
39820,
40049,
40279,
40510,
40741,
40973,
41207,
41440,
41675,
41910,
42146,
42383,
42621,
42859,
43098,
43337,
43578,
43818,
44059 };

// get temperature in 1/32 Celsius degree (5bit fixed-point) of K-thermocouple with input in uV
// return 0xFFFF when out of range
u16 K_temp(u16 uv) 
{
	u8 u=uv>>8;
	u8 v=(u8)uv;
		
	if (u>(u8)(sizeof(K_TEMP_FP5)/2-2))
		return 0xffff;

	u16 a=K_TEMP_FP5[u];
	u8 k=(u8)K_TEMP_FP5[++u] - (u8)a;   // intervals of neighbor elements in K_TEMP32 are less then 256
	return (u8)((k*v+128)>>8)+a; // SDCC follows ANSI C rule : 8bit * 8bit => int * int, then for optimization, op. MUL, not _mulint(), will be used here by SDCC
}

// get uV from temperature, input temperature is in 1/32 Celsius degree (5bit fixed-point)
// return 0xFFFF when out of range
u16 K_uv(u16 temp)
{
	if (K_TEMP_FP5[sizeof(K_TEMP_FP5)/2-1]<temp)
		return 0xFFFF;
	
	u8 u=1;
	u16 a=0;
	u16 b;
	do {
		b=K_TEMP_FP5[u];
		if (b>=temp)
			break;
		a=b;
		u++;
	} while (1);	
	u8 k=(u8)(b-a);
	return ((u16)(u-1)<<8)+((((u16)(temp-a)<<8)+(k>>1))/k);
}

