/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _CUST_BATTERY_METER_TABLE_H
#define _CUST_BATTERY_METER_TABLE_H

#define BAT_NTC_10 1
#define BAT_NTC_47 0

#if (BAT_NTC_10 == 1)
#define RBAT_PULL_UP_R             16900
#endif

#if (BAT_NTC_47 == 1)
#define RBAT_PULL_UP_R             61900
#endif

#define RBAT_PULL_UP_VOLT          1800

typedef struct _BATTERY_PROFILE_STRUCT {
	signed int percentage;
	signed int voltage;
} BATTERY_PROFILE_STRUCT, *BATTERY_PROFILE_STRUCT_P;

typedef struct _R_PROFILE_STRUCT {
	signed int resistance;
	signed int voltage;
} R_PROFILE_STRUCT, *R_PROFILE_STRUCT_P;

typedef enum {
	T1_0C,
	T2_25C,
	T3_50C
} PROFILE_TEMPERATURE;

#if (BAT_NTC_10 == 1)
BATT_TEMPERATURE Batt_Temperature_Table[] = {
	{-20, 68237},
	{-15, 53650},
	{-10, 42506},
	{ -5, 33892},
	{  0, 27219},
	{  5, 22021},
	{ 10, 17926},
	{ 15, 14674},
	{ 20, 12081},
	{ 25, 10000},
	{ 30, 8315},
	{ 35, 6948},
	{ 40, 5834},
	{ 45, 4917},
	{ 50, 4161},
	{ 55, 3535},
	{ 60, 3014}
};
#endif

#if (BAT_NTC_47 == 1)
	BATT_TEMPERATURE Batt_Temperature_Table[] = {
	{-20, 483954},
	{-15, 360850},
	{-10, 271697},
	{ -5, 206463},
	{  0, 158214},
	{  5, 122259},
	{ 10, 95227},
	{ 15, 74730},
	{ 20, 59065},
	{ 25, 47000},
	{ 30, 37643},
	{ 35, 30334},
	{ 40, 24591},
	{ 45, 20048},
	{ 50, 16433},
	{ 55, 13539},
	{ 60, 11210}
	};
#endif

/* T0 -10C */
BATTERY_PROFILE_STRUCT battery_profile_t0[] = {
{0,4380},
{1,4362},
{2,4346},
{3,4332},
{4,4318},
{5,4304},
{6,4291},
{7,4279},
{8,4266},
{9,4254},
{10,4242},
{11,4230},
{12,4219},
{13,4207},
{14,4196},
{15,4185},
{16,4174},
{17,4163},
{18,4153},
{19,4141},
{20,4131},
{21,4120},
{22,4109},
{23,4099},
{24,4090},
{25,4081},
{26,4071},
{27,4060},
{28,4047},
{29,4033},
{30,4018},
{31,4003},
{32,3989},
{33,3977},
{34,3966},
{35,3956},
{36,3948},
{37,3940},
{38,3932},
{39,3924},
{40,3917},
{41,3909},
{42,3902},
{43,3894},
{44,3887},
{45,3880},
{46,3874},
{47,3868},
{48,3861},
{49,3856},
{50,3850},
{51,3845},
{52,3840},
{53,3835},
{54,3830},
{55,3826},
{56,3822},
{57,3817},
{58,3813},
{59,3810},
{59,3806},
{60,3803},
{61,3800},
{62,3797},
{63,3794},
{64,3792},
{65,3790},
{66,3788},
{67,3787},
{68,3785},
{69,3783},
{70,3781},
{71,3779},
{72,3777},
{73,3775},
{74,3773},
{75,3770},
{76,3767},
{77,3764},
{78,3760},
{79,3757},
{80,3752},
{81,3748},
{82,3743},
{83,3737},
{84,3732},
{85,3726},
{86,3720},
{87,3715},
{88,3709},
{89,3704},
{90,3699},
{91,3695},
{92,3690},
{93,3685},
{94,3678},
{95,3667},
{96,3649},
{97,3617},
{98,3567},
{99,3494},
{100,3400},
{100,3400},
{100,3400},
{100,3400},
{100,3400},
{100,3400}
};

/* T1 0C */
BATTERY_PROFILE_STRUCT battery_profile_t1[] = {
{0,4384},
{1,4371},
{2,4358},
{3,4347},
{4,4335},
{5,4323},
{6,4312},
{7,4300},
{8,4288},
{9,4277},
{10,4265},
{11,4254},
{12,4243},
{13,4231},
{14,4220},
{15,4209},
{16,4198},
{17,4187},
{18,4176},
{19,4166},
{20,4155},
{21,4144},
{22,4134},
{23,4123},
{24,4112},
{25,4102},
{26,4092},
{27,4083},
{28,4074},
{29,4066},
{30,4057},
{31,4044},
{32,4029},
{33,4014},
{34,4000},
{35,3987},
{36,3976},
{37,3967},
{38,3958},
{38,3950},
{39,3941},
{40,3932},
{41,3923},
{42,3914},
{43,3905},
{44,3897},
{45,3890},
{46,3882},
{47,3876},
{48,3869},
{49,3863},
{50,3857},
{51,3852},
{52,3847},
{53,3842},
{54,3837},
{55,3832},
{56,3828},
{57,3823},
{58,3819},
{59,3815},
{60,3812},
{61,3808},
{62,3804},
{63,3801},
{64,3798},
{65,3795},
{66,3792},
{67,3789},
{68,3786},
{69,3784},
{70,3782},
{71,3780},
{72,3778},
{73,3775},
{74,3773},
{75,3771},
{76,3769},
{77,3766},
{78,3763},
{79,3759},
{80,3756},
{81,3752},
{82,3747},
{83,3742},
{84,3736},
{85,3730},
{86,3724},
{87,3717},
{88,3709},
{89,3703},
{90,3699},
{91,3697},
{92,3694},
{93,3692},
{94,3688},
{95,3681},
{96,3668},
{97,3640},
{98,3594},
{99,3533},
{100,3447},
{100,3400},
{100,3400},
{100,3400},
{100,3400},
{100,3400}
};

/* T2 25C */
BATTERY_PROFILE_STRUCT battery_profile_t2[] = {
{0,4385},
{1,4373},
{2,4362},
{3,4351},
{4,4340},
{5,4328},
{6,4317},
{7,4306},
{8,4294},
{9,4283},
{10,4271},
{11,4260},
{12,4249},
{13,4237},
{14,4226},
{15,4214},
{16,4203},
{17,4192},
{18,4182},
{19,4170},
{20,4159},
{21,4149},
{22,4138},
{23,4127},
{24,4116},
{25,4107},
{26,4096},
{26,4085},
{27,4076},
{28,4067},
{29,4058},
{30,4048},
{31,4036},
{32,4025},
{33,4015},
{34,4005},
{35,3999},
{36,3991},
{37,3983},
{38,3974},
{39,3966},
{40,3957},
{41,3947},
{42,3937},
{43,3925},
{44,3914},
{45,3904},
{46,3894},
{47,3886},
{48,3880},
{49,3873},
{50,3867},
{51,3862},
{52,3856},
{53,3851},
{54,3847},
{55,3842},
{56,3837},
{57,3833},
{58,3829},
{59,3824},
{60,3821},
{61,3818},
{62,3814},
{63,3810},
{64,3807},
{65,3804},
{66,3801},
{67,3798},
{68,3796},
{69,3792},
{70,3790},
{71,3787},
{72,3783},
{73,3780},
{74,3776},
{75,3772},
{76,3768},
{77,3764},
{78,3760},
{78,3757},
{79,3753},
{80,3750},
{81,3746},
{82,3743},
{83,3738},
{84,3731},
{85,3725},
{86,3720},
{87,3713},
{88,3705},
{89,3700},
{90,3698},
{91,3697},
{92,3696},
{93,3695},
{94,3692},
{95,3687},
{96,3668},
{97,3627},
{98,3573},
{99,3501},
{100,3400},
{100,3400},
{100,3400},
{100,3400},
{100,3400}
};

/* T3 50C */
BATTERY_PROFILE_STRUCT battery_profile_t3[] = {
{0,4359},
{1,4347},
{2,4335},
{3,4323},
{4,4312},
{5,4301},
{6,4289},
{7,4278},
{8,4266},
{9,4255},
{10,4243},
{11,4232},
{12,4221},
{13,4210},
{14,4198},
{15,4187},
{16,4176},
{17,4165},
{18,4155},
{19,4144},
{20,4133},
{21,4123},
{22,4112},
{23,4102},
{24,4092},
{25,4081},
{26,4072},
{27,4062},
{28,4052},
{29,4043},
{30,4034},
{31,4024},
{32,4015},
{33,4007},
{34,3998},
{35,3989},
{36,3981},
{37,3973},
{38,3964},
{39,3956},
{40,3948},
{41,3940},
{42,3931},
{43,3921},
{44,3909},
{45,3896},
{46,3887},
{47,3878},
{48,3872},
{49,3865},
{50,3859},
{51,3854},
{52,3848},
{53,3843},
{54,3838},
{55,3834},
{56,3829},
{57,3825},
{58,3821},
{59,3816},
{60,3813},
{61,3809},
{62,3805},
{63,3802},
{64,3799},
{65,3795},
{66,3792},
{67,3789},
{68,3786},
{69,3783},
{70,3780},
{71,3777},
{72,3771},
{73,3764},
{74,3757},
{74,3752},
{75,3747},
{76,3743},
{77,3739},
{78,3735},
{79,3731},
{80,3728},
{81,3724},
{82,3720},
{83,3715},
{84,3709},
{85,3703},
{86,3698},
{87,3691},
{88,3682},
{89,3678},
{90,3677},
{91,3676},
{92,3675},
{93,3674},
{94,3671},
{95,3664},
{96,3639},
{97,3597},
{98,3543},
{99,3471},
{100,3400},
{100,3400},
{100,3400},
{100,3400},
{100,3400},
{100,3400}
};

/* battery profile for actual temperature. The size should be the same as T1, T2 and T3 */
BATTERY_PROFILE_STRUCT battery_profile_temperature[] = {
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0},                   
	{0, 0}, 
	{0, 0},                   
	{0, 0},                   
	{0, 0},       	
	{0, 0} 
};

/* T0 -10C */
R_PROFILE_STRUCT r_profile_t0[] = {
{968,4380},
{968,4362},
{970,4346},
{968,4332},
{958,4318},
{945,4304},
{935,4291},
{928,4279},
{915,4266},
{908,4254},
{900,4242},
{885,4230},
{878,4219},
{870,4207},
{858,4196},
{850,4185},
{845,4174},
{835,4163},
{833,4153},
{825,4141},
{823,4131},
{813,4120},
{808,4109},
{803,4099},
{800,4090},
{798,4081},
{798,4071},
{790,4060},
{778,4047},
{768,4033},
{755,4018},
{745,4003},
{730,3989},
{728,3977},
{723,3966},
{718,3956},
{718,3948},
{718,3940},
{713,3932},
{713,3924},
{715,3917},
{708,3909},
{705,3902},
{703,3894},
{700,3887},
{700,3880},
{703,3874},
{700,3868},
{700,3861},
{703,3856},
{705,3850},
{708,3845},
{708,3840},
{713,3835},
{713,3830},
{718,3826},
{725,3822},
{735,3817},
{740,3813},
{750,3810},
{750,3806},
{755,3803},
{763,3800},
{765,3797},
{770,3794},
{778,3792},
{783,3790},
{790,3788},
{800,3787},
{808,3785},
{820,3783},
{830,3781},
{840,3779},
{850,3777},
{870,3775},
{888,3773},
{903,3770},
{923,3767},
{940,3764},
{960,3760},
{990,3757},
{1008,3752},
{1040,3748},
{1065,3743},
{1098,3737},
{1133,3732},
{1168,3726},
{1203,3720},
{1243,3715},
{1283,3709},
{1323,3704},
{1360,3699},
{1400,3695},
{1443,3690},
{1490,3685},
{1520,3678},
{1553,3667},
{1583,3649},
{1615,3617},
{1670,3567},
{1748,3494},
{1918,3400},
{1918,3400},
{1918,3400},
{1918,3400},
{1918,3400},
{1918,3400} 
};

/* T1 0C */
R_PROFILE_STRUCT r_profile_t1[] = {
{433,4384},
{433,4371},
{433,4358},
{430,4347},
{425,4335},
{425,4323},
{428,4312},
{423,4300},
{418,4288},
{418,4277},
{413,4265},
{413,4254},
{410,4243},
{403,4231},
{400,4220},
{395,4209},
{400,4198},
{398,4187},
{395,4176},
{398,4166},
{395,4155},
{393,4144},
{395,4134},
{388,4123},
{385,4112},
{385,4102},
{390,4092},
{393,4083},
{395,4074},
{400,4066},
{403,4057},
{398,4044},
{390,4029},
{385,4014},
{375,4000},
{360,3987},
{365,3976},
{368,3967},
{363,3958},
{360,3950},
{355,3941},
{353,3932},
{348,3923},
{343,3914},
{335,3905},
{333,3897},
{330,3890},
{333,3882},
{335,3876},
{333,3869},
{333,3863},
{333,3857},
{335,3852},
{338,3847},
{338,3842},
{335,3837},
{335,3832},
{340,3828},
{343,3823},
{343,3819},
{345,3815},
{348,3812},
{350,3808},
{353,3804},
{355,3801},
{353,3798},
{355,3795},
{358,3792},
{363,3789},
{363,3786},
{365,3784},
{368,3782},
{373,3780},
{375,3778},
{378,3775},
{375,3773},
{380,3771},
{383,3769},
{393,3766},
{400,3763},
{405,3759},
{413,3756},
{420,3752},
{428,3747},
{438,3742},
{445,3736},
{455,3730},
{465,3724},
{483,3717},
{498,3709},
{513,3703},
{530,3699},
{553,3697},
{575,3694},
{608,3692},
{645,3688},
{678,3681},
{715,3668},
{748,3640},
{800,3594},
{878,3533},
{990,3447},
{1453,3400},
{1453,3400},
{1453,3400},
{1453,3400},
{1453,3400}
};

/* T2 25C */
R_PROFILE_STRUCT r_profile_t2[] = {
{135,4385},
{135,4373},
{138,4362},
{138,4351},
{140,4340},
{135,4328},
{138,4317},
{138,4306},
{138,4294},
{138,4283},
{138,4271},
{140,4260},
{140,4249},
{138,4237},
{140,4226},
{138,4214},
{140,4203},
{138,4192},
{143,4182},
{140,4170},
{140,4159},
{143,4149},
{143,4138},
{145,4127},
{143,4116},
{148,4107},
{145,4096},
{145,4085},
{148,4076},
{155,4067},
{153,4058},
{153,4048},
{150,4036},
{155,4025},
{155,4015},
{155,4005},
{160,3999},
{160,3991},
{165,3983},
{160,3974},
{165,3966},
{163,3957},
{160,3947},
{155,3937},
{150,3925},
{143,3914},
{138,3904},
{130,3894},
{130,3886},
{130,3880},
{130,3873},
{128,3867},
{130,3862},
{128,3856},
{128,3851},
{133,3847},
{133,3842},
{130,3837},
{130,3833},
{133,3829},
{130,3824},
{133,3821},
{135,3818},
{135,3814},
{135,3810},
{135,3807},
{133,3804},
{138,3801},
{138,3798},
{143,3796},
{138,3792},
{140,3790},
{140,3787},
{135,3783},
{135,3780},
{133,3776},
{135,3772},
{133,3768},
{130,3764},
{130,3760},
{130,3757},
{130,3753},
{133,3750},
{130,3746},
{133,3743},
{135,3738},
{130,3731},
{130,3725},
{135,3720},
{135,3713},
{135,3705},
{130,3700},
{130,3698},
{133,3697},
{138,3696},
{143,3695},
{145,3692},
{153,3687},
{150,3668},
{148,3627},
{155,3573},
{163,3501},
{205,3400},
{948,3400},
{948,3400},
{948,3400},
{948,3400}
};

/* T3 50C */
R_PROFILE_STRUCT r_profile_t3[] = {
{103,4359},
{103,4347},
{103,4335},
{100,4323},
{103,4312},
{103,4301},
{103,4289},
{103,4278},
{103,4266},
{103,4255},
{103,4243},
{103,4232},
{105,4221},
{105,4210},
{103,4198},
{103,4187},
{105,4176},
{105,4165},
{108,4155},
{108,4144},
{108,4133},
{108,4123},
{108,4112},
{108,4102},
{110,4092},
{108,4081},
{110,4072},
{110,4062},
{110,4052},
{113,4043},
{113,4034},
{113,4024},
{113,4015},
{115,4007},
{115,3998},
{115,3989},
{118,3981},
{120,3973},
{120,3964},
{120,3956},
{123,3948},
{125,3940},
{125,3931},
{123,3921},
{118,3909},
{108,3896},
{108,3887},
{105,3878},
{105,3872},
{103,3865},
{103,3859},
{105,3854},
{103,3848},
{103,3843},
{105,3838},
{105,3834},
{105,3829},
{108,3825},
{108,3821},
{105,3816},
{110,3813},
{110,3809},
{110,3805},
{110,3802},
{113,3799},
{113,3795},
{113,3792},
{113,3789},
{115,3786},
{115,3783},
{115,3780},
{115,3777},
{110,3771},
{108,3764},
{105,3757},
{108,3752},
{105,3747},
{108,3743},
{108,3739},
{108,3735},
{108,3731},
{108,3728},
{108,3724},
{108,3720},
{108,3715},
{108,3709},
{108,3703},
{110,3698},
{110,3691},
{105,3682},
{103,3678},
{105,3677},
{108,3676},
{110,3675},
{115,3674},
{118,3671},
{120,3664},
{113,3639},
{113,3597},
{118,3543},
{128,3471},
{233,3400},
{883,3400},
{883,3400},
{883,3400},
{883,3400},
{883,3400}
};

/* r-table profile for actual temperature. The size should be the same as T1, T2 and T3 */
R_PROFILE_STRUCT r_profile_temperature[] = {
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},    
	{0, 0},
	{0, 0},    
	{0, 0},    
	{0, 0}	
};

/* ============================================================
// function prototype
// ============================================================*/
int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUCT_P fgauge_get_profile(unsigned int temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUCT_P fgauge_get_profile_r_table(unsigned int temperature);

#endif	/*#ifndef _CUST_BATTERY_METER_TABLE_H*/

