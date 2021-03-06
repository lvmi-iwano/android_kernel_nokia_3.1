/* Copyright Statement:
*
* This software/firmware and related documentation ("MediaTek Software") are
* protected under relevant copyright laws. The information contained herein
* is confidential and proprietary to MediaTek Inc. and/or its licensors.
* Without the prior written permission of MediaTek inc. and/or its licensors,
* any reproduction, modification, use or disclosure of MediaTek Software,
* and information contained herein, in whole or in part, shall be strictly prohibited.
*/
/* MediaTek Inc. (C) 2015. All rights reserved.
*
* BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
* THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
* RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
* AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
* NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
* SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
* SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
* THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
* THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
* CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
* SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
* STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
* CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
* AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
* OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
* MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*/

#define LOG_TAG "LCM"

#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/kernel.h>
#endif

#include "lcm_drv.h"


#ifdef BUILD_LK
#include <platform/upmu_common.h>
#include <platform/mt_gpio.h>
#include <platform/mt_i2c.h>
#include <platform/mt_pmic.h>
#include <string.h>
#elif defined(BUILD_UBOOT)
#include <asm/arch/mt_gpio.h>
#else
#if 0
#include <mach/mt_pm_ldo.h>
#include <mach/mt_gpio.h>
#else
#include <mach/gpio_const.h>
#include <mt-plat/mt_gpio.h>
#endif
#endif

#if 0
#include <cust_gpio_usage.h>

#ifndef MACH_FPGA
#include <cust_i2c.h>
#endif
#endif


#ifdef BUILD_LK
#define LCM_LOGI(string, args...)  dprintf(0, "[LK/"LOG_TAG"]"string, ##args)
#define LCM_LOGD(string, args...)  dprintf(1, "[LK/"LOG_TAG"]"string, ##args)
#else
#define LCM_LOGI(fmt, args...)  pr_notice("[KERNEL/"LOG_TAG"]"fmt, ##args)
#define LCM_LOGD(fmt, args...)  pr_debug("[KERNEL/"LOG_TAG"]"fmt, ##args)
#endif

#define LCM_ID_NT35695 (0xf5)

static const unsigned int BL_MIN_LEVEL = 20;
static LCM_UTIL_FUNCS lcm_util;

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))
#define MDELAY(n)       (lcm_util.mdelay(n))
#define UDELAY(n)       (lcm_util.udelay(n))


/* --------------------------------------------------------------------------- */
/* Local Functions */
/* --------------------------------------------------------------------------- */

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update) \
    lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update) \
        lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd) lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums) \
        lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd) \
      lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size) \
        lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


#define I2C_I2C_LCD_BIAS_CHANNEL 	1
#define GPIO_DISP_LRSTB_PIN		(GPIO158 | 0x80000000) 	//LCM_RST
#define GPIO_LCDBL_EN_PIN		(GPIO11  | 0x80000000) 	//GPIO_LCM_LED_EN
#define GPIO_LCM_BIAS_EN_PIN		(GPIO12 | 0x80000000) 	//GPIO_LCM_BIAS_EN

 /*****************************************************************************
 * Define
 *****************************************************************************/
/*for I2C channel 1*/
#define I2C_RT5081_PMU_CHANNEL	I2C_I2C_LCD_BIAS_CHANNEL
#define I2C_RT5081_PMU_SLAVE_7_BIT_ADDR		0x34
#define I2C_ID_NAME		"RT5081"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>

/* static unsigned char lcd_id_pins_value = 0xFF; */
static const unsigned char LCD_MODULE_ID = 0x01;
/* --------------------------------------------------------------------------- */
/* Local Constants */
/* --------------------------------------------------------------------------- */
#define LCM_DSI_CMD_MODE                                    0
#define FRAME_WIDTH                                     (720)
#define FRAME_HEIGHT                                    (1440)

#define REGFLAG_DELAY       0xFFFC
#define REGFLAG_UDELAY  0xFFFB
#define REGFLAG_END_OF_TABLE    0xFFFD
#define REGFLAG_RESET_LOW   0xFFFE
#define REGFLAG_RESET_HIGH  0xFFFF

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[64];
};
/*
static struct LCM_setting_table lcm_suspend_setting[] = {
	{0x28, 0, {} },
	{0x10, 0, {} },
	{REGFLAG_DELAY, 120, {} },
	{0x4F, 1, {0x01} },
	{REGFLAG_DELAY, 120, {} }
};
*/
#if 1
#if 1
static struct LCM_setting_table lcm_initialization_setting_4lane[] = {
	{REGFLAG_DELAY,20, {}},
        {0x00,1,{0x00}},
        {0xff,3,{0x87,0x16,0x01}},

        {0x00,1,{0x80}},
        {0xff,2,{0x87,0x16}},

        {0x00,1,{0x00}},
        {0x2A,4,{0x00,0x00,0x02,0xCF}},
        {0x00,1,{0x00}},
        {0x2B,4,{0x00,0x00,0x04,0xFF}},

        {0x00,1,{0x00}},
        {0xD0,1,{0x5A}},
        {0x00,1,{0x00}},
        {0xD1,2,{0x5A,0x5A}},

        {0x00,1,{0x00}},
        {0xff,3,{0x00,0x00,0x00}},
        {0x00,1,{0x80}},
        {0xff,2,{0x00,0x00}},
#if 0
        {0x11,0,{}},
	{REGFLAG_DELAY, 150, {}},
        {0x29,0,{}},
        {0x35,0,{}},
#else
        {0x11,1,{0x00}},
	{REGFLAG_DELAY, 150, {}},
        {0x29,1,{0x00}},
        {0x35,1,{0x00}},
#endif
	{REGFLAG_DELAY, 20, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}},
};
#else
static struct LCM_setting_table lcm_initialization_setting_4lane[] = {
	{REGFLAG_DELAY, 20, {}},
        {0x00,1,{0x00}},
        {0xff,3,{0x87,0x16,0x01}},
        {0x00,1,{0x80}},
        {0xff,2,{0x87,0x16}},

        {0x00,1,{0xA2}},
        {0xC1,1,{0x01}},
        {0x00,1,{0xA0}},
        {0xF6,1,{0x0F}},
        {0x00,1,{0xA9}},
        {0xF6,1,{0x5A}},

        {0x11,1,{0x00}},
	{REGFLAG_DELAY, 150, {}},
        {0x29,1,{0x00}},
        {0x35,1,{0x00}},
	{REGFLAG_DELAY, 20, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}},
};
#endif
#else
static struct LCM_setting_table lcm_initialization_setting_4lane[] = {
	{REGFLAG_DELAY, 10, {}},
        {0x00,1,{0x00}},
        {0xff,3,{0x87,0x16,0x01}},
        {0x00,1,{0x80}},
        {0xff,2,{0x87,0x16}},

	/* Set CABC backlight min & max for UI, ST, MV mode */
        {0x00,1,{0x80}},
        {0xCA,0x0A,{0x80,0xCC,0xFF,0xA5,0xFF,0x80,0xFF,0x00,0x00,0x00}},

	/* Set 53h Dimming frame CAB5 */
        {0x00,1,{0xB5}},
        {0xCA,1,{0x01}},

        {0x00,1,{0x00}},
        {0x2A,4,{0x00,0x00,0x02,0xCF}},
        {0x2B,4,{0x00,0x00,0x04,0xFF}},
        {0x11,1,{0x00}},
	{REGFLAG_DELAY, 150, {}},
        {0x29,1,{0x00}},
        {0x35,1,{0x00}},
	{REGFLAG_DELAY, 20, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}},
};
#endif

#if defined(CONFIG_TOUCHSCREEN_MTK_FTGESTURE)
static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
//	Display off sequence
//	{0x28, 1, {0x00}},
	{0x28, 0, {}},
	{REGFLAG_DELAY, 80, {}},

//	Sleep Mode On
//	{0x10, 1, {0x00}},
	{0x10, 0, {}},
	{REGFLAG_DELAY, 70, {}},
	{0x00, 1, {0x00}},
	{0xF7, 4, {0x5A,0xA5,0x87,0x16}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
#endif

static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
//	Display off sequence
//	{0x28, 1, {0x00}},
	{0x28, 0, {}},
	{REGFLAG_DELAY, 80, {}},

//	Sleep Mode On
//	{0x10, 1, {0x00}},
	{0x10, 0, {}},
	{REGFLAG_DELAY, 20, {}},

//	Deep Standby Mode On
//	{0x00, 0, {}},
	{0x00, 1, {0x00}},
	{0xF7, 4, {0x5A,0xA5,0x87,0x16}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

/*
static struct LCM_setting_table lcm_deep_sleep_out_setting[] = {
//	Display off sequence
	{0x11, 1, {0x00}},
	{REGFLAG_DELAY, 150, {}},

//	Sleep Mode On
	{0x29, 1, {0x00}},
	{REGFLAG_DELAY, 20, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
*/

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

	for(i = 0; i < count; i++)
	{
		unsigned cmd;
		cmd = table[i].cmd;

		switch (cmd) {
		    case REGFLAG_DELAY :
		        if(table[i].count <= 10)
				MDELAY(table[i].count);
		        else
				MDELAY(table[i].count);
		        break;

		    case REGFLAG_END_OF_TABLE :
		        break;

		    default:
			dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
		}
	}
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));
	params->type   = LCM_TYPE_DSI;

	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

	params->physical_width=59;
	params->physical_height=117;


#if (LCM_DSI_CMD_MODE)
	params->dsi.mode   = CMD_MODE;
#else
	params->dsi.mode   = SYNC_PULSE_VDO_MODE;  //SYNC_EVENT_VDO_MODE  BURST_VDO_MODE    SYNC_PULSE_VDO_MODE
#endif

	// DSI
	/* Command mode setting */
	params->dsi.LANE_NUM		= 4;	// 4
	params->dsi.PLL_CLOCK 		= 210;	//371/2;  //4lane

#if 1
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;
#else
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_LSB_FIRST;
	params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_MSB;
	params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;
#endif

	// Highly depends on LCD driver capability.
	// Not support in MT6573
	params->dsi.packet_size=256;
	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

	params->dsi.vertical_sync_active	= 6;
	params->dsi.vertical_backporch		= 16;
	params->dsi.vertical_frontporch		= 16;
	params->dsi.vertical_active_line	= FRAME_HEIGHT;

	params->dsi.horizontal_sync_active	= 6;
	params->dsi.horizontal_backporch	= 32;
	params->dsi.horizontal_frontporch	= 32;
	params->dsi.horizontal_active_pixel	= FRAME_WIDTH;

	//improve clk quality
	//params->dsi.PLL_CLOCK 		= 390; 	  //3lane
	//params->dsi.PLL_CLOCK 		= 257;    //4lane

	params->dsi.compatibility_for_nvk 	= 1;
	params->dsi.ssc_disable 		= 1;

	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
	params->dsi.lcm_esd_check_table[0].cmd = 0x0A;
	params->dsi.lcm_esd_check_table[0].count = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;

	params->dsi.lcm_esd_check_table[1].cmd = 0xAC;
	params->dsi.lcm_esd_check_table[1].count = 1;
	params->dsi.lcm_esd_check_table[1].para_list[0] = 0x00;
}

extern int display_bias_enable(void);
extern int display_bias_disable(void);
static void lcm_init(void)
{
	int i = 0;
#if 0
	SET_RESET_PIN(0);
	MDELAY(5);
#else
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ZERO);
	MDELAY(5);
#endif

/******************************1.VIO18_PMU***************************
 * Once RESET,VIO18_CON0->RG_VIO18_EN will be set to 1 automatically,
 * So even if we don't do the follow operation it will still output 1.8V.
 ********************************************************************/
#if 0
	//Enable VIO18_PMU 1.8V
	pmic_config_interface(0xA36, 0x1, 0x1, 1);
	pmic_config_interface(0xA80, 0x00, 0x0F, 8);
#endif
/******************************2.AVDD & AVEE*************************/
#if 1
	display_bias_enable();
	MDELAY(5);
#else
	mt_set_gpio_out(GPIO_LCM_BIAS_EN_PIN, GPIO_OUT_ONE);
	MDELAY(5);
#endif
/******************************3.reset high to low to high*************************/
#if 0
	SET_RESET_PIN(1);
	MDELAY(2);
	SET_RESET_PIN(0);
	MDELAY(2);
	SET_RESET_PIN(1);
	MDELAY(10);
#else
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ONE);
	MDELAY(2);
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ZERO);
	MDELAY(2);
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ONE);
	MDELAY(10);
#endif

	LCM_LOGD("******  st7701_lcm_init  *****\n");
	push_table(lcm_initialization_setting_4lane, sizeof(lcm_initialization_setting_4lane) / sizeof(struct LCM_setting_table), 1);

/******************************3.Backlight Enable******************************
 * platform/mt6735/platform.c
 * platform_init(void)
 * ******mt65xx_backlight_on();
 * **************led_brightness backlight_level = get_cust_led_default_level();
 * **************mt65xx_leds_brightness_set(MT65XX_LED_TYPE_LCD, backlight_level);
 ******************************************************************************/
//Backlight has open in platform_init,so we do not need do follow operation
#if 1
	for (i = 0; i < 5; i++) {
		mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ONE);
		UDELAY(2);

		mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ZERO);
		UDELAY(2);
		LCM_LOGD("kernel:GPIO_LCDBL_EN_PIN\n");
	}
	mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ONE);
	UDELAY(10);
#endif
	LCM_LOGD("st7701_lcm_init\n");
}

#if defined(CONFIG_TOUCHSCREEN_MTK_FTGESTURE)
extern uint8_t g_ftgesture;
#endif
static void lcm_suspend(void)
{
#if defined(CONFIG_TOUCHSCREEN_MTK_FTGESTURE)
	if (g_ftgesture == 0) {
		push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
		MDELAY(15);
	} else {
		push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
		MDELAY(15);
	}
#else
		push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
		MDELAY(15);
#endif
#if 0
	//reset low
	SET_RESET_PIN(0);
	MDELAY(2);
#else
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ZERO);
	MDELAY(2);
#endif
        mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ZERO);
        MDELAY(5);

#if 1
#if defined(CONFIG_TOUCHSCREEN_MTK_FTGESTURE)
	/* disable AVDD & AVEE */
	if (g_ftgesture == 0) {
		display_bias_disable();
		MDELAY(5);
	}
#else
	display_bias_disable();
	MDELAY(5);
#endif
#else
	mt_set_gpio_out(GPIO_LCM_BIAS_EN_PIN, GPIO_OUT_ZERO);
	MDELAY(5);
#endif

	LCM_LOGD("kernel:st7701_lcm_suspend\n");
}

static void lcm_resume(void)
{
	int i = 0;

#if 0
	SET_RESET_PIN(0);
	MDELAY(5);
#else
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ZERO);
	MDELAY(5);
#endif
#if 1
#if defined(CONFIG_TOUCHSCREEN_MTK_FTGESTURE)
	/* enable AVDD & AVEE */
	if (g_ftgesture == 0) {
		display_bias_enable();
		MDELAY(5);
	}
#else
	display_bias_enable();
	MDELAY(5);
#endif
#else
	//enable VSP:5.8v & VSN:-5.8v
	mt_set_gpio_out(GPIO_LCM_BIAS_EN_PIN, GPIO_OUT_ONE);
	MDELAY(5);
#endif

#if 0
	SET_RESET_PIN(1);
	MDELAY(2);
	SET_RESET_PIN(0);
	MDELAY(2);
	SET_RESET_PIN(1);
	MDELAY(10);
#else
	//reset low to high
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ONE);
	MDELAY(2);
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ZERO);
	MDELAY(2);
	mt_set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ONE);
	MDELAY(10);
#endif

#if 1
	push_table(lcm_initialization_setting_4lane, sizeof(lcm_initialization_setting_4lane) / sizeof(struct LCM_setting_table), 1);
#else
	push_table(lcm_deep_sleep_out_setting, sizeof(lcm_deep_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
#endif

#if 1
	for (i = 0; i < 5; i++) {
		mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ONE);
		UDELAY(2);

		mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ZERO);
		UDELAY(2);
		LCM_LOGD("kernel:GPIO_LCDBL_EN_PIN\n");
	}
	mt_set_gpio_out(GPIO_LCDBL_EN_PIN, GPIO_OUT_ONE);
	UDELAY(10);
#endif
	LCM_LOGD("kernel:st7701_lcm_resume\n");
}

#if 0
static unsigned int lcm_compare_id(void)
{
	unsigned int id=0;
	unsigned char buffer[3]={0};
	unsigned int data_array[16];

/********************************************************************
 * Once RESET,VIO18_CON0->RG_VIO18_EN will be set to 1 automatically,
 * So even if we don't do the follow operation it will still output 1.8V.
 ********************************************************************/
	//Enable VIO18_PMU 1.8V
	pmic_config_interface(0xA36, 0x1, 0x1, 1);
	pmic_config_interface(0xA80, 0x00, 0x0F, 8);
	//Enable VGP1_PMU 2.8V
	pmic_config_interface(0xA2C, 0x1, 0x1, 1);
	pmic_config_interface(0xA72, 0x05, 0x07, 4);

	//reset high to low to high
	lcm_util.set_gpio_mode(GPIO_DISP_LRSTB_PIN, GPIO_MODE_00);
	lcm_util.set_gpio_dir(GPIO_DISP_LRSTB_PIN, GPIO_DIR_OUT);
	lcm_util.set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ONE);
	MDELAY(2);
	lcm_util.set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ZERO);
	MDELAY(2);
	lcm_util.set_gpio_out(GPIO_DISP_LRSTB_PIN, GPIO_OUT_ONE);
	MDELAY(10);

#if 0
	data_array[0]=0x00043902;
	data_array[1]=0x9483FFB9;
	dsi_set_cmdq(data_array, 2, 1);
	MDELAY(10);
#endif

#if 1
	data_array[0] = 0x00033700;
	dsi_set_cmdq(data_array, 1, 1);

	read_reg_v2(0x04, buffer, 3);
	LCM_LOGD("Read ID, buf:0x%02x,0x%02x,0x%02x\n",buffer[0], buffer[1], buffer[2]);
#endif
	if(LCM_ID1 == buffer[0]&&LCM_ID2 == buffer[1]&&LCM_ID3 == buffer[2])
		return 1;
	else
		return 0;
}
#endif

LCM_DRIVER ft8613_dsi_vdo_hd720p_rt5081_lcm_drv =
{
    .name           	= "ft8613_dsi_vdo_hd720p_rt5081",
    .set_util_funcs 	= lcm_set_util_funcs,
    .get_params     	= lcm_get_params,
    .init           	= lcm_init,
    .suspend        	= lcm_suspend,
    .resume         	= lcm_resume,
//    .compare_id     	= lcm_compare_id,
};
