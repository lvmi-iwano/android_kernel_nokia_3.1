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


/* ============================================================
// define
// ============================================================*/
#define BAT_NTC_10 1
#define BAT_NTC_47 0

#if (BAT_NTC_10 == 1)
#define RBAT_PULL_UP_R             16900
#endif

#if (BAT_NTC_47 == 1)
#define RBAT_PULL_UP_R             61900
#endif

#define RBAT_PULL_UP_VOLT          1800

#define BIF_NTC_R 16000

/* multiple battery profile compile options */
#define MTK_GET_BATTERY_ID_BY_AUXADC
#define BATTERY_ID_CHANNEL_NUM 12
#define TOTAL_BATTERY_NUMBER 2
#define BAT_ID_POS_NEG_VOLTAGE_ERR_RANGE 150000
/*#define MTK_GET_BATTERY_ID_BY_GPIO*/

/* ============================================================
// ENUM
// ============================================================*/

/* ============================================================
// structure
// ============================================================*/

/* ============================================================
// typedef
// ============================================================*/
typedef struct _BATTERY_PROFILE_STRUCT {
	signed int percentage;
	signed int voltage;
	} BATTERY_PROFILE_STRUCT, *BATTERY_PROFILE_STRUCT_P;

typedef struct _R_PROFILE_STRUCT {
	signed int resistance; /* Ohm*/
	signed int voltage;
} R_PROFILE_STRUCT, *R_PROFILE_STRUCT_P;

typedef enum {
	T1_0C,
	T2_25C,
	T3_50C
} PROFILE_TEMPERATURE;

/* ============================================================
// External Variables
// ============================================================*/

/* ============================================================
// External function
// ============================================================*/

/* ============================================================
// <DOD, Battery_Voltage> Table
// ============================================================*/

/* Qmax for battery  */
signed int g_Q_MAX_POS_50[TOTAL_BATTERY_NUMBER] = {2910,2834};
signed int g_Q_MAX_POS_25[TOTAL_BATTERY_NUMBER] = {2910,2870};
signed int g_Q_MAX_POS_0[TOTAL_BATTERY_NUMBER] =  {2293,1899};
signed int g_Q_MAX_NEG_10[TOTAL_BATTERY_NUMBER] = {1052,1085};

signed int g_Q_MAX_POS_50_H_CURRENT[TOTAL_BATTERY_NUMBER] = {2900,2777};
signed int g_Q_MAX_POS_25_H_CURRENT[TOTAL_BATTERY_NUMBER] = {2900,2813};
signed int g_Q_MAX_POS_0_H_CURRENT[TOTAL_BATTERY_NUMBER] =  {2247,1861};
signed int g_Q_MAX_NEG_10_H_CURRENT[TOTAL_BATTERY_NUMBER] = {1031,1063};

signed int g_Q_MAX_SYS_VOLTAGE[TOTAL_BATTERY_NUMBER] = {3400, 3400};
signed int g_BATTERYPSEUDO1[TOTAL_BATTERY_NUMBER] = {0, 0};

/* 1.2V for battery 0;1.35V for battery 1  */
signed int g_battery_id_voltage[TOTAL_BATTERY_NUMBER] = {1200000, 900000};


#if (BAT_NTC_10 == 1)
BATT_TEMPERATURE Batt_Temperature_Table[TOTAL_BATTERY_NUMBER][132] = {
	{
		{-400, 188500},
		{-390, 178600},
		{-380, 169200},
		{-370, 160400},
		{-360, 152100},
		{-350, 144300},
		{-340, 136900},
		{-330, 130000},
		{-320, 123400},
		{-310, 117200},
		{-300, 111300},
		{-290, 105800},
		{-280, 100600},
		{-270, 95640},
		{-260, 90970},
		{-250, 86560},
		{-240, 82380},
		{-230, 78430},
		{-220, 74690},
		{-210, 71140},
		{-200, 67790},
		{-190, 64610},
		{-180, 61600},
		{-170, 58740},
		{-160, 56030},
		{-150, 53460},
		{-140, 51030},
		{-130, 48710},
		{-120, 46520},
		{-110, 44430},
		{-100, 42450},
		{-90, 40570},
		{-80, 38780},
		{-70, 37080},
		{-60, 35460},
		{-50, 33930},
		{-40, 32460},
		{-30, 31070},
		{-20, 29750},
		{-10, 28490},
		{0, 27280},
		{10, 26140},
		{20, 25050},
		{30, 24010},
		{40, 23020},
		{50, 22070},
		{60, 21170},
		{70, 20310},
		{80, 19490},
		{90, 18710},
		{100, 17960},
		{110, 17250},
		{120, 16570},
		{130, 15910},
		{140, 15290},
		{150, 14700},
		{160, 14130},
		{170, 13590},
		{180, 13070},
		{190, 12570},
		{200, 12090},
		{210, 11640},
		{220, 11200},
		{230, 10780},
		{240, 10380},
		{250, 10000},
		{260, 9633},
		{270, 9282},
		{280, 8945},
		{290, 8622},
		{300, 8312},
		{310, 8015},
		{320, 7730},
		{330, 7456},
		{340, 7194},
		{350, 6942},
		{360, 6700},
		{370, 6468},
		{380, 6245},
		{390, 6031},
		{400, 5826},
		{410, 5628},
		{420, 5438},
		{430, 5255},
		{440, 5080},
		{450, 4911},
		{460, 4749},
		{470, 4592},
		{480, 4442},
		{490, 4297},
		{500, 4158},
		{510, 4024},
		{520, 3895},
		{530, 3771},
		{540, 3651},
		{550, 3536},
		{560, 3425},
		{570, 3318},
		{580, 3215},
		{590, 3115},
		{600, 3019},
		{610, 2927},
		{620, 2837},
		{630, 2751},
		{640, 2668},
		{650, 2588},
		{660, 2511},
		{670, 2436},
		{680, 2364},
		{690, 2295},
		{700, 2227},
		{710, 2163},
		{720, 2100},
		{730, 2039},
		{740, 1981},
		{750, 1924},
		{760, 1869},
		{770, 1817},
		{780, 1765},
		{790, 1716},
		{800, 1668},
		{810, 1622},
		{820, 1577},
		{830, 1534},
		{840, 1492},
		{850, 1451},
		{860, 1412},
		{870, 1374},
		{880, 1337},
		{890, 1302},
		{900, 1267},
		{910,1234}
	},
	{
		{-400, 188500},
		{-390, 178600},
		{-380, 169200},
		{-370, 160400},
		{-360, 152100},
		{-350, 144300},
		{-340, 136900},
		{-330, 130000},
		{-320, 123400},
		{-310, 117200},
		{-300, 111300},
		{-290, 105800},
		{-280, 100600},
		{-270, 95640},
		{-260, 90970},
		{-250, 86560},
		{-240, 82380},
		{-230, 78430},
		{-220, 74690},
		{-210, 71140},
		{-200, 67790},
		{-190, 64610},
		{-180, 61600},
		{-170, 58740},
		{-160, 56030},
		{-150, 53460},
		{-140, 51030},
		{-130, 48710},
		{-120, 46520},
		{-110, 44430},
		{-100, 42450},
		{-90, 40570},
		{-80, 38780},
		{-70, 37080},
		{-60, 35460},
		{-50, 33930},
		{-40, 32460},
		{-30, 31070},
		{-20, 29750},
		{-10, 28490},
		{0, 27280},
		{10, 26140},
		{20, 25050},
		{30, 24010},
		{40, 23020},
		{50, 22070},
		{60, 21170},
		{70, 20310},
		{80, 19490},
		{90, 18710},
		{100, 17960},
		{110, 17250},
		{120, 16570},
		{130, 15910},
		{140, 15290},
		{150, 14700},
		{160, 14130},
		{170, 13590},
		{180, 13070},
		{190, 12570},
		{200, 12090},
		{210, 11640},
		{220, 11200},
		{230, 10780},
		{240, 10380},
		{250, 10000},
		{260, 9633},
		{270, 9282},
		{280, 8945},
		{290, 8622},
		{300, 8312},
		{310, 8015},
		{320, 7730},
		{330, 7456},
		{340, 7194},
		{350, 6942},
		{360, 6700},
		{370, 6468},
		{380, 6245},
		{390, 6031},
		{400, 5826},
		{410, 5628},
		{420, 5438},
		{430, 5255},
		{440, 5080},
		{450, 4911},
		{460, 4749},
		{470, 4592},
		{480, 4442},
		{490, 4297},
		{500, 4158},
		{510, 4024},
		{520, 3895},
		{530, 3771},
		{540, 3651},
		{550, 3536},
		{560, 3425},
		{570, 3318},
		{580, 3215},
		{590, 3115},
		{600, 3019},
		{610, 2927},
		{620, 2837},
		{630, 2751},
		{640, 2668},
		{650, 2588},
		{660, 2511},
		{670, 2436},
		{680, 2364},
		{690, 2295},
		{700, 2227},
		{710, 2163},
		{720, 2100},
		{730, 2039},
		{740, 1981},
		{750, 1924},
		{760, 1869},
		{770, 1817},
		{780, 1765},
		{790, 1716},
		{800, 1668},
		{810, 1622},
		{820, 1577},
		{830, 1534},
		{840, 1492},
		{850, 1451},
		{860, 1412},
		{870, 1374},
		{880, 1337},
		{890, 1302},
		{900, 1267},
		{910,1234}
	}
};
#endif

#if (BAT_NTC_47 == 1)
BATT_TEMPERATURE Batt_Temperature_Table[TOTAL_BATTERY_NUMBER][17] = {
	{
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
	},
	{
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
	}
};
#endif

/* T0 -10C */
BATTERY_PROFILE_STRUCT battery_profile_t0[TOTAL_BATTERY_NUMBER][59] = {
	{
		{0,4385},
		{6,4350},
		{8,4325},
		{14,4303},
		{19,4281},
		{25,4261},
		{27,4240},
		{33,4219},
		{39,4199},
		{44,4180},
		{48,4160},
		{53,4141},
		{58,4121},
		{61,4102},
		{67,4084},
		{73,4069},
		{78,4050},
		{81,4021},
		{86,3991},
		{92,3968},
		{94,3952},
		{100,3939},
		{106,3928},
		{111,3917},
		{114,3904},
		{119,3892},
		{125,3880},
		{131,3869},
		{134,3858},
		{139,3847},
		{144,3838},
		{148,3830},
		{153,3821},
		{159,3814},
		{164,3806},
		{167,3800},
		{173,3793},
		{178,3788},
		{184,3783},
		{186,3779},
		{192,3775},
		{197,3771},
		{200,3767},
		{206,3764},
		{211,3759},
		{217,3754},
		{219,3749},
		{225,3743},
		{231,3736},
		{234,3729},
		{239,3722},
		{245,3715},
		{250,3708},
		{253,3700},
		{259,3689},
		{264,3669},
		{270,3633},
		{272,3566},
		{278,3400}
	},
	{
		{0,4378},
		{5,4339},
		{9,4313},
		{14,4282},
		{20,4256},
		{25,4231},
		{27,4210},
		{32,4188},
		{38,4169},
		{41,4150},
		{46,4129},
		{52,4112},
		{54,4098},
		{59,4083},
		{64,4061},
		{70,4029},
		{73,3997},
		{79,3976},
		{86,3943},
		{93,3931},
		{98,3920},
		{100,3908},
		{105,3895},
		{111,3884},
		{116,3872},
		{120,3860},
		{125,3849},
		{130,3840},
		{132,3831},
		{138,3822},
		{143,3815},
		{146,3808},
		{152,3801},
		{157,3797},
		{163,3793},
		{164,3789},
		{170,3787},
		{177,3784},
		{179,3780},
		{184,3776},
		{189,3773},
		{193,3769},
		{198,3765},
		{204,3760},
		{209,3756},
		{211,3750},
		{216,3743},
		{221,3736},
		{225,3727},
		{230,3721},
		{236,3713},
		{238,3707},
		{243,3701},
		{248,3695},
		{254,3684},
		{257,3662},
		{263,3612},
		{266,3582},
		{271,3400}
	}
};

/* T1 0C */
BATTERY_PROFILE_STRUCT battery_profile_t1[TOTAL_BATTERY_NUMBER][59] = {
	{
		{0,4381},
		{3,4348},
		{4,4325},
		{6,4302},
		{9,4282},
		{12,4262},
		{13,4242},
		{15,4221},
		{18,4202},
		{21,4183},
		{22,4164},
		{24,4145},
		{27,4126},
		{28,4108},
		{31,4090},
		{33,4078},
		{36,4061},
		{37,4033},
		{40,4005},
		{42,3985},
		{44,3969},
		{46,3956},
		{49,3942},
		{50,3929},
		{52,3914},
		{54,3901},
		{57,3887},
		{59,3875},
		{61,3865},
		{63,3855},
		{66,3845},
		{67,3837},
		{70,3829},
		{72,3822},
		{75,3815},
		{76,3809},
		{78,3803},
		{81,3798},
		{84,3793},
		{85,3788},
		{87,3784},
		{90,3780},
		{91,3777},
		{94,3774},
		{96,3770},
		{99,3766},
		{100,3761},
		{103,3755},
		{105,3748},
		{107,3739},
		{109,3731},
		{112,3719},
		{114,3708},
		{116,3703},
		{118,3699},
		{121,3692},
		{123,3663},
		{125,3579},
		{127,3400}
	},
	{
		{0,4359},
		{3,4331},
		{5,4306},
		{8,4283},
		{11,4263},
		{14,4241},
		{15,4220},
		{19,4203},
		{22,4183},
		{23,4167},
		{27,4149},
		{29,4130},
		{33,4111},
		{34,4094},
		{37,4084},
		{41,4070},
		{42,4047},
		{44,4015},
		{48,3987},
		{49,3966},
		{52,3950},
		{56,3940},
		{58,3927},
		{63,3899},
		{66,3886},
		{68,3872},
		{71,3861},
		{75,3851},
		{77,3841},
		{78,3831},
		{82,3823},
		{85,3815},
		{86,3809},
		{90,3803},
		{92,3795},
		{96,3789},
		{97,3786},
		{100,3783},
		{104,3779},
		{105,3777},
		{108,3775},
		{111,3772},
		{113,3768},
		{115,3766},
		{119,3761},
		{122,3756},
		{124,3749},
		{127,3741},
		{129,3732},
		{132,3723},
		{134,3710},
		{138,3699},
		{141,3694},
		{142,3689},
		{146,3684},
		{148,3670},
		{149,3607},
		{153,3492},
		{154,3400}
	}
};

/* T2 25C*/
BATTERY_PROFILE_STRUCT battery_profile_t2[TOTAL_BATTERY_NUMBER][59] = {
	{
		{0,4385},
		{2,4355},
		{3,4332},
		{5,4311},
		{7,4288},
		{9,4268},
		{10,4247},
		{12,4227},
		{14,4206},
		{16,4187},
		{18,4167},
		{20,4148},
		{22,4129},
		{23,4110},
		{25,4092},
		{27,4075},
		{29,4060},
		{30,4041},
		{32,4020},
		{34,4004},
		{35,3989},
		{37,3977},
		{39,3963},
		{41,3948},
		{42,3933},
		{44,3915},
		{46,3895},
		{48,3878},
		{49,3866},
		{52,3855},
		{54,3845},
		{55,3837},
		{57,3829},
		{59,3822},
		{61,3814},
		{62,3808},
		{64,3803},
		{66,3798},
		{68,3793},
		{69,3788},
		{71,3783},
		{73,3779},
		{74,3773},
		{76,3766},
		{78,3759},
		{80,3752},
		{81,3747},
		{84,3741},
		{86,3734},
		{87,3725},
		{89,3716},
		{91,3703},
		{93,3690},
		{94,3681},
		{96,3634},
		{98,3539},
		{100,3400},
		{101,3400},
		{103,3400}
	},
	{
		{0,4367},
		{2,4341},
		{3,4320},
		{5,4300},
		{7,4279},
		{9,4259},
		{10,4239},
		{12,4219},
		{14,4200},
		{15,4180},
		{17,4162},
		{19,4143},
		{21,4125},
		{22,4107},
		{24,4088},
		{27,4073},
		{28,4063},
		{30,4043},
		{32,4017},
		{34,3996},
		{35,3986},
		{37,3976},
		{39,3964},
		{40,3949},
		{42,3935},
		{44,3915},
		{46,3896},
		{47,3878},
		{49,3868},
		{51,3857},
		{52,3848},
		{54,3839},
		{56,3831},
		{57,3824},
		{59,3817},
		{61,3811},
		{63,3804},
		{64,3798},
		{66,3793},
		{68,3788},
		{69,3785},
		{71,3781},
		{73,3775},
		{76,3767},
		{77,3761},
		{79,3755},
		{81,3748},
		{82,3736},
		{84,3727},
		{86,3717},
		{88,3708},
		{89,3695},
		{91,3686},
		{94,3672},
		{96,3605},
		{98,3494},
		{100,3400},
		{101,3400},
		{102,3400}
	}
};

/* T3 50C*/
BATTERY_PROFILE_STRUCT battery_profile_t3[TOTAL_BATTERY_NUMBER][59] = {
	{
		{0,4387},
		{2,4343},
		{3,4320},
		{5,4298},
		{7,4278},
		{9,4257},
		{10,4237},
		{12,4217},
		{14,4198},
		{16,4178},
		{18,4159},
		{20,4139},
		{22,4121},
		{23,4102},
		{25,4084},
		{27,4066},
		{29,4049},
		{30,4033},
		{32,4017},
		{34,4001},
		{35,3986},
		{37,3971},
		{39,3958},
		{41,3943},
		{42,3930},
		{44,3914},
		{46,3893},
		{48,3875},
		{49,3862},
		{52,3851},
		{54,3842},
		{55,3833},
		{57,3824},
		{59,3817},
		{61,3810},
		{62,3804},
		{64,3798},
		{66,3792},
		{68,3787},
		{69,3782},
		{71,3778},
		{73,3774},
		{74,3765},
		{76,3752},
		{78,3743},
		{80,3736},
		{81,3730},
		{83,3724},
		{86,3718},
		{87,3710},
		{89,3700},
		{91,3690},
		{93,3677},
		{94,3672},
		{96,3645},
		{98,3571},
		{100,3400},
		{101,3400},
		{103,3400}
	},
	{
		{0,4352},
		{2,4329},
		{3,4308},
		{5,4288},
		{7,4267},
		{9,4247},
		{10,4227},
		{12,4207},
		{14,4188},
		{16,4170},
		{17,4150},
		{19,4131},
		{21,4113},
		{22,4096},
		{24,4078},
		{27,4062},
		{29,4046},
		{30,4028},
		{32,4013},
		{34,3997},
		{36,3984},
		{37,3970},
		{39,3956},
		{41,3942},
		{42,3926},
		{44,3905},
		{46,3886},
		{48,3873},
		{49,3861},
		{51,3851},
		{53,3844},
		{55,3834},
		{56,3827},
		{58,3819},
		{60,3813},
		{61,3806},
		{63,3800},
		{65,3795},
		{67,3791},
		{68,3785},
		{70,3781},
		{72,3774},
		{74,3760},
		{76,3750},
		{78,3744},
		{80,3738},
		{81,3731},
		{83,3726},
		{85,3720},
		{87,3709},
		{88,3699},
		{90,3687},
		{92,3680},
		{94,3677},
		{95,3669},
		{97,3623},
		{99,3535},
		{100,3400},
		{102,3400}
	}
};

/* battery profile for actual temperature. The size should be the same as T1, T2 and T3*/
BATTERY_PROFILE_STRUCT battery_profile_temperature[TOTAL_BATTERY_NUMBER][59] = {
	{
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
	},
	{
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
	}
	
};

/* ============================================================
// <Rbat, Battery_Voltage> Table
// ============================================================*/
/* T0 -10C*/
R_PROFILE_STRUCT r_profile_t0[TOTAL_BATTERY_NUMBER][59] = {
	{
		{925, 4385},
		{925, 4350},
		{929, 4325},
		{932, 4303},
		{925, 4281},
		{926, 4261},
		{916, 4240},
		{913, 4219},
		{908, 4199},
		{902, 4180},
		{896, 4160},
		{898, 4141},
		{888, 4121},
		{884, 4102},
		{885, 4084},
		{890, 4069},
		{898, 4050},
		{882, 4021},
		{869, 3991},
		{864, 3968},
		{865, 3952},
		{870, 3939},
		{870, 3928},
		{871, 3917},
		{873, 3904},
		{870, 3892},
		{878, 3880},
		{879, 3869},
		{880, 3858},
		{884, 3847},
		{891, 3838},
		{901, 3830},
		{905, 3821},
		{908, 3814},
		{913, 3806},
		{923, 3800},
		{924, 3793},
		{933, 3788},
		{939, 3783},
		{952, 3779},
		{963, 3775},
		{973, 3771},
		{986, 3767},
		{1002, 3764},
		{1026, 3759},
		{1050, 3754},
		{1077, 3749},
		{1115, 3743},
		{1152, 3736},
		{1208, 3729},
		{1276, 3722},
		{1366, 3715},
		{1487, 3708},
		{1628, 3700},
		{1743, 3689},
		{1860, 3669},
		{2020, 3633},
		{2285, 3566},
		{2285, 3400}
	},
	{
		{1242,4378},
		{1242,4339},
		{826,4313},
		{1287,4282},
		{1285,4256},
		{1259,4231},
		{1236,4210},
		{1218,4188},
		{1198,4169},
		{1132,4150},
		{1110,4129},
		{1101,4112},
		{1112,4098},
		{1119,4083},
		{1102,4061},
		{1059,4029},
		{1053,3997},
		{857,3976},
		{950,3943},
		{949,3931},
		{955,3920},
		{950,3908},
		{944,3895},
		{945,3884},
		{940,3872},
		{936,3860},
		{935,3849},
		{938,3840},
		{938,3831},
		{941,3822},
		{943,3815},
		{946,3808},
		{951,3801},
		{961,3797},
		{970,3793},
		{985,3789},
		{1003,3787},
		{1024,3784},
		{1053,3780},
		{1167,3776},
		{1201,3773},
		{1240,3769},
		{1282,3765},
		{1324,3760},
		{1374,3756},
		{1437,3750},
		{1482,3743},
		{1529,3736},
		{1552,3727},
		{1557,3721},
		{1612,3713},
		{1661,3707},
		{1708,3701},
		{1602,3695},
		{1746,3684},
		{1815,3662},
		{1994,3612},
		{1956,3582},
		{1460,3400}
	}
};

/* T1 0C*/
R_PROFILE_STRUCT r_profile_t1[TOTAL_BATTERY_NUMBER][59] = {
	{
		{395, 4381},
		{395, 4348},
		{395, 4325},
		{389, 4302},
		{389, 4282},
		{389, 4262},
		{389, 4242},
		{387, 4221},
		{388, 4202},
		{389, 4183},
		{389, 4164},
		{390, 4145},
		{392, 4126},
		{395, 4108},
		{392, 4090},
		{400, 4078},
		{406, 4061},
		{400, 4033},
		{395, 4005},
		{394, 3985},
		{389, 3969},
		{383, 3956},
		{377, 3942},
		{371, 3929},
		{364, 3914},
		{361, 3901},
		{357, 3887},
		{355, 3875},
		{355, 3865},
		{355, 3855},
		{355, 3845},
		{355, 3837},
		{359, 3829},
		{360, 3822},
		{361, 3815},
		{363, 3809},
		{363, 3803},
		{366, 3798},
		{369, 3793},
		{369, 3788},
		{371, 3784},
		{372, 3780},
		{374, 3777},
		{377, 3774},
		{381, 3770},
		{385, 3766},
		{388, 3761},
		{394, 3755},
		{397, 3748},
		{404, 3739},
		{412, 3731},
		{423, 3719},
		{434, 3708},
		{457, 3703},
		{497, 3699},
		{560, 3692},
		{645, 3663},
		{800, 3579},
		{1530, 3400}
	},
	{
		{600,4359},
		{600,4331},
		{632,4306},
		{621,4283},
		{613,4263},
		{600,4241},
		{594,4220},
		{536,4203},
		{520,4183},
		{509,4167},
		{542,4149},
		{567,4130},
		{556,4111},
		{554,4094},
		{576,4084},
		{587,4070},
		{578,4047},
		{547,4015},
		{525,3987},
		{513,3966},
		{512,3950},
		{514,3940},
		{498,3927},
		{478,3899},
		{478,3886},
		{470,3872},
		{468,3861},
		{469,3851},
		{467,3841},
		{465,3831},
		{470,3823},
		{472,3815},
		{477,3809},
		{478,3803},
		{482,3795},
		{485,3789},
		{496,3786},
		{502,3783},
		{443,3779},
		{521,3777},
		{538,3775},
		{557,3772},
		{576,3768},
		{604,3766},
		{626,3761},
		{647,3756},
		{675,3749},
		{709,3741},
		{774,3732},
		{819,3723},
		{871,3710},
		{933,3699},
		{1011,3694},
		{1111,3689},
		{1226,3684},
		{1344,3670},
		{1422,3607},
		{1526,3492},
		{1515,3400}
	}
};

/* T2 25C*/
R_PROFILE_STRUCT r_profile_t2[TOTAL_BATTERY_NUMBER][59] = {
	{
		{137, 4385},
		{137, 4355},
		{135, 4332},
		{138, 4311},
		{136, 4288},
		{138, 4268},
		{140, 4247},
		{138, 4227},
		{139, 4206},
		{141, 4187},
		{143, 4167},
		{146, 4148},
		{146, 4129},
		{149, 4110},
		{151, 4092},
		{154, 4075},
		{158, 4060},
		{158, 4041},
		{161, 4020},
		{166, 4004},
		{169, 3989},
		{175, 3977},
		{177, 3963},
		{180, 3948},
		{177, 3933},
		{167, 3915},
		{146, 3895},
		{135, 3878},
		{130, 3866},
		{128, 3855},
		{127, 3845},
		{127, 3837},
		{129, 3829},
		{130, 3822},
		{133, 3814},
		{138, 3808},
		{141, 3803},
		{144, 3798},
		{146, 3793},
		{147, 3788},
		{147, 3783},
		{147, 3779},
		{144, 3773},
		{141, 3766},
		{138, 3759},
		{136, 3752},
		{138, 3747},
		{139, 3741},
		{141, 3734},
		{140, 3725},
		{143, 3716},
		{143, 3703},
		{141, 3693},
		{146, 3690},
		{152, 3688},
		{163, 3681},
		{155, 3634},
		{169, 3539},
		{202, 3400}
	},
	{
		{140,4367},
		{140,4341},
		{143,4320},
		{145,4300},
		{140,4279},
		{144,4259},
		{140,4239},
		{141,4219},
		{142,4200},
		{138,4180},
		{142,4162},
		{139,4143},
		{144,4125},
		{145,4107},
		{146,4088},
		{146,4073},
		{157,4063},
		{159,4043},
		{158,4017},
		{155,3996},
		{166,3986},
		{167,3976},
		{172,3964},
		{171,3949},
		{171,3935},
		{158,3915},
		{147,3896},
		{136,3878},
		{139,3868},
		{139,3857},
		{139,3848},
		{134,3839},
		{136,3831},
		{137,3824},
		{140,3817},
		{140,3811},
		{143,3804},
		{143,3798},
		{144,3793},
		{146,3788},
		{149,3785},
		{151,3781},
		{145,3775},
		{139,3767},
		{134,3761},
		{136,3755},
		{131,3748},
		{135,3742},
		{134,3736},
		{133,3727},
		{138,3717},
		{141,3708},
		{140,3695},
		{153,3689},
		{164,3686},
		{173,3672},
		{174,3605},
		{202,3494},
		{304,3263}
	}
};

/* T3 50C*/
R_PROFILE_STRUCT r_profile_t3[TOTAL_BATTERY_NUMBER][59] = {
	{
		{115, 4387},
		{115, 4343},
		{115, 4320},
		{115, 4298},
		{118, 4278},
		{115, 4257},
		{116, 4237},
		{116, 4217},
		{118, 4198},
		{118, 4178},
		{119, 4159},
		{116, 4139},
		{118, 4121},
		{119, 4102},
		{119, 4084},
		{121, 4066},
		{121, 4049},
		{124, 4033},
		{124, 4017},
		{127, 4001},
		{126, 3986},
		{129, 3971},
		{133, 3958},
		{135, 3943},
		{140, 3930},
		{143, 3914},
		{129, 3893},
		{119, 3875},
		{116, 3862},
		{116, 3851},
		{116, 3842},
		{118, 3833},
		{115, 3824},
		{116, 3817},
		{118, 3810},
		{118, 3804},
		{121, 3798},
		{121, 3792},
		{121, 3787},
		{124, 3782},
		{126, 3778},
		{129, 3774},
		{124, 3765},
		{116, 3752},
		{115, 3743},
		{116, 3736},
		{116, 3730},
		{118, 3724},
		{121, 3718},
		{119, 3710},
		{118, 3700},
		{121, 3690},
		{115, 3677},
		{121, 3674},
		{126, 3672},
		{134, 3667},
		{132, 3645},
		{133, 3571},
		{178, 3400}
	},
	{
		{100,4352},
		{100,4329},
		{100,4308},
		{103,4288},
		{101,4267},
		{103,4247},
		{101,4227},
		{105,4207},
		{104,4188},
		{107,4170},
		{103,4150},
		{102,4131},
		{102,4113},
		{107,4096},
		{105,4078},
		{109,4062},
		{111,4046},
		{109,4028},
		{112,4013},
		{113,3997},
		{120,3984},
		{118,3970},
		{123,3956},
		{126,3942},
		{128,3926},
		{113,3905},
		{106,3886},
		{103,3873},
		{100,3861},
		{99,3851},
		{106,3844},
		{102,3834},
		{106,3827},
		{103,3819},
		{106,3813},
		{106,3806},
		{105,3800},
		{109,3795},
		{114,3791},
		{112,3785},
		{116,3781},
		{112,3774},
		{102,3760},
		{101,3750},
		{100,3744},
		{105,3738},
		{102,3731},
		{105,3726},
		{108,3720},
		{105,3709},
		{104,3699},
		{105,3687},
		{100,3680},
		{108,3679},
		{115,3677},
		{127,3669},
		{113,3623},
		{125,3535},
		{151,3400}
	}
};

/* r-table profile for actual temperature. The size should be the same as T1, T2 and T3*/
R_PROFILE_STRUCT r_profile_temperature[TOTAL_BATTERY_NUMBER][59] = {
	{
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
	},
	{
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
	}
};

/* ============================================================
// function prototype
// ============================================================*/
int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUCT_P fgauge_get_profile(unsigned int temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUCT_P fgauge_get_profile_r_table(unsigned int temperature);

#endif

