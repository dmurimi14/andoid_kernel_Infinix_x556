#include <mt-plat/charging.h>
#include <mt-plat/upmu_common.h>
#include <linux/delay.h>
#include <linux/reboot.h>
#include <mt-plat/mt_boot.h>
#include <mt-plat/battery_meter.h>
#include <mach/mt_battery_meter.h>
#include <mach/mt_charging.h>
#include <mach/mt_pmic.h>
#include "sm5414.h"
//#include <mach/mt_sleep.h>
#include <mt-plat/mt_gpio.h>
/* ============================================================ // */
/* Define */
/* ============================================================ // */
#define STATUS_OK    0
#define STATUS_UNSUPPORTED    -1
#define GETARRAYNUM(array) (sizeof(array)/sizeof(array[0]))

#define GPIO_SM5414_CHGEN_PIN	(62 | 0x80000000)
#define GPIO_SM5414_SHDN_PIN	(80 | 0x80000000)

/* ============================================================ // */
/* Global variable */
/* ============================================================ // */

#if defined(MTK_WIRELESS_CHARGER_SUPPORT)
#define WIRELESS_CHARGER_EXIST_STATE 0

#if defined(GPIO_PWR_AVAIL_WLC)
/*K.S.?*/
unsigned int wireless_charger_gpio_number = GPIO_PWR_AVAIL_WLC;
#else
unsigned int wireless_charger_gpio_number = 0;
#endif

#endif

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
static CHARGER_TYPE g_charger_type = CHARGER_UNKNOWN;
#endif

kal_bool charging_type_det_done = KAL_TRUE;

const unsigned int VBAT_CV_VTH[] = {
    BATTERY_VOLT_04_100000_V,   BATTERY_VOLT_04_125000_V,   BATTERY_VOLT_04_150000_V,   BATTERY_VOLT_04_175000_V,
    BATTERY_VOLT_04_200000_V,   BATTERY_VOLT_04_225000_V,   BATTERY_VOLT_04_250000_V,   BATTERY_VOLT_04_275000_V,
    BATTERY_VOLT_04_300000_V,   BATTERY_VOLT_04_325000_V,   BATTERY_VOLT_04_350000_V,   BATTERY_VOLT_04_375000_V,
    BATTERY_VOLT_04_400000_V,   BATTERY_VOLT_04_425000_V,   BATTERY_VOLT_04_450000_V,   BATTERY_VOLT_04_475000_V,  
};

const unsigned int CS_VTH[] = {
	CHARGE_CURRENT_100_00_MA,   CHARGE_CURRENT_150_00_MA,	CHARGE_CURRENT_200_00_MA, CHARGE_CURRENT_250_00_MA,
    CHARGE_CURRENT_300_00_MA,   CHARGE_CURRENT_350_00_MA,   CHARGE_CURRENT_400_00_MA, CHARGE_CURRENT_450_00_MA,
    CHARGE_CURRENT_500_00_MA,   CHARGE_CURRENT_550_00_MA,   CHARGE_CURRENT_600_00_MA, CHARGE_CURRENT_650_00_MA,
    CHARGE_CURRENT_700_00_MA,   CHARGE_CURRENT_750_00_MA,   CHARGE_CURRENT_800_00_MA, CHARGE_CURRENT_850_00_MA,
    CHARGE_CURRENT_900_00_MA,   CHARGE_CURRENT_950_00_MA,   CHARGE_CURRENT_1000_00_MA, CHARGE_CURRENT_1050_00_MA,
    CHARGE_CURRENT_1100_00_MA,   CHARGE_CURRENT_1150_00_MA,   CHARGE_CURRENT_1200_00_MA, CHARGE_CURRENT_1250_00_MA,
    CHARGE_CURRENT_1300_00_MA,   CHARGE_CURRENT_1350_00_MA,   CHARGE_CURRENT_1400_00_MA, CHARGE_CURRENT_1450_00_MA,
    CHARGE_CURRENT_1500_00_MA,   CHARGE_CURRENT_1550_00_MA,   CHARGE_CURRENT_1600_00_MA, CHARGE_CURRENT_1650_00_MA,
    CHARGE_CURRENT_1700_00_MA,   CHARGE_CURRENT_1750_00_MA,   CHARGE_CURRENT_1800_00_MA, CHARGE_CURRENT_1850_00_MA,
    CHARGE_CURRENT_1900_00_MA,   CHARGE_CURRENT_1950_00_MA,   CHARGE_CURRENT_2000_00_MA, CHARGE_CURRENT_2050_00_MA,
    CHARGE_CURRENT_2100_00_MA,   CHARGE_CURRENT_2150_00_MA,   CHARGE_CURRENT_2200_00_MA, CHARGE_CURRENT_2250_00_MA,
    CHARGE_CURRENT_2300_00_MA,   CHARGE_CURRENT_2350_00_MA,   CHARGE_CURRENT_2400_00_MA, CHARGE_CURRENT_2450_00_MA,
    CHARGE_CURRENT_2500_00_MA,
};

const unsigned int INPUT_CS_VTH[] = {
	CHARGE_CURRENT_100_00_MA,   CHARGE_CURRENT_150_00_MA,	CHARGE_CURRENT_200_00_MA, CHARGE_CURRENT_250_00_MA,
    CHARGE_CURRENT_300_00_MA,   CHARGE_CURRENT_350_00_MA,   CHARGE_CURRENT_400_00_MA, CHARGE_CURRENT_450_00_MA,
    CHARGE_CURRENT_500_00_MA,   CHARGE_CURRENT_550_00_MA,   CHARGE_CURRENT_600_00_MA, CHARGE_CURRENT_650_00_MA,
    CHARGE_CURRENT_700_00_MA,   CHARGE_CURRENT_750_00_MA,   CHARGE_CURRENT_800_00_MA, CHARGE_CURRENT_850_00_MA,
    CHARGE_CURRENT_900_00_MA,   CHARGE_CURRENT_950_00_MA,   CHARGE_CURRENT_1000_00_MA, CHARGE_CURRENT_1050_00_MA,
    CHARGE_CURRENT_1100_00_MA,   CHARGE_CURRENT_1150_00_MA,   CHARGE_CURRENT_1200_00_MA, CHARGE_CURRENT_1250_00_MA,
    CHARGE_CURRENT_1300_00_MA,   CHARGE_CURRENT_1350_00_MA,   CHARGE_CURRENT_1400_00_MA, CHARGE_CURRENT_1450_00_MA,
    CHARGE_CURRENT_1500_00_MA,   CHARGE_CURRENT_1550_00_MA,   CHARGE_CURRENT_1600_00_MA, CHARGE_CURRENT_1650_00_MA,
    CHARGE_CURRENT_1700_00_MA,   CHARGE_CURRENT_1750_00_MA,   CHARGE_CURRENT_1800_00_MA, CHARGE_CURRENT_1850_00_MA,
    CHARGE_CURRENT_1900_00_MA,   CHARGE_CURRENT_1950_00_MA,   CHARGE_CURRENT_2000_00_MA, CHARGE_CURRENT_2050_00_MA,
};

const unsigned int VCDT_HV_VTH[] = {
	BATTERY_VOLT_04_200000_V, BATTERY_VOLT_04_250000_V,	  BATTERY_VOLT_04_300000_V,   BATTERY_VOLT_04_350000_V,
	BATTERY_VOLT_04_400000_V, BATTERY_VOLT_04_450000_V,	  BATTERY_VOLT_04_500000_V,   BATTERY_VOLT_04_550000_V,
	BATTERY_VOLT_04_600000_V, BATTERY_VOLT_06_000000_V,	  BATTERY_VOLT_06_500000_V,   BATTERY_VOLT_07_000000_V,
	BATTERY_VOLT_07_500000_V, BATTERY_VOLT_08_500000_V,	  BATTERY_VOLT_09_500000_V,   BATTERY_VOLT_10_500000_V		  
};

#ifdef CONFIG_MTK_DUAL_INPUT_CHARGER_SUPPORT
#ifndef CUST_GPIO_VIN_SEL
#define CUST_GPIO_VIN_SEL 18
#endif
DISO_IRQ_Data DISO_IRQ;
int g_diso_state = 0;
int vin_sel_gpio_number = (CUST_GPIO_VIN_SEL | 0x80000000);
static char *DISO_state_s[8] = {
	"IDLE",
	"OTG_ONLY",
	"USB_ONLY",
	"USB_WITH_OTG",
	"DC_ONLY",
	"DC_WITH_OTG",
	"DC_WITH_USB",
	"DC_USB_OTG",
};
#endif

/* ============================================================ // */
/* function prototype */
/* ============================================================ // */


/* ============================================================ // */
/* extern variable */
/* ============================================================ // */

/* ============================================================ // */
/* extern function */
/* ============================================================ // */
/* extern unsigned int upmu_get_reg_value(unsigned int reg); upmu_common.h, _not_ used */
/* extern bool mt_usb_is_device(void); _not_ used */
/* extern void Charger_Detect_Init(void); _not_ used */
/* extern void Charger_Detect_Release(void); _not_ used */
/* extern int hw_charging_get_charger_type(void);  included in charging.h*/
/* extern void mt_power_off(void); _not_ used */
/* extern unsigned int mt6311_get_chip_id(void); _not_ used*/
/* extern int is_mt6311_exist(void); _not_ used */
/* extern int is_mt6311_sw_ready(void); _not_ used */
extern unsigned int sm5414_get_topoff_status(void);
#ifdef CONFIG_MTK_BIF_SUPPORT
static int bif_exist;
static int bif_checked;
#endif
static unsigned int charging_error;
static unsigned int charging_get_error_state(void);
static unsigned int charging_set_error_state(void *data);
static unsigned int charging_set_vindpm(void *data);

/* ============================================================ // */
unsigned int charging_value_to_parameter(const unsigned int *parameter, const unsigned int array_size,
				       const unsigned int val)
{
	if (val < array_size)
		return parameter[val];

		battery_log(BAT_LOG_CRTI, "Can't find the parameter \r\n");
		return parameter[0];

}

unsigned int charging_parameter_to_value(const unsigned int *parameter, const unsigned int array_size,
				       const unsigned int val)
{
	unsigned int i;

	battery_log(BAT_LOG_FULL, "array_size = %d \r\n", array_size);

	for (i = 0; i < array_size; i++) {
		if (val == *(parameter + i))
			return i;
	}

	battery_log(BAT_LOG_CRTI, "NO register value match \r\n");
	/* TODO: ASSERT(0);    // not find the value */
	return 0;
}

static unsigned int bmt_find_closest_level(const unsigned int *pList, unsigned int number,
					 unsigned int level)
{
	unsigned int i;
	unsigned int max_value_in_last_element;

	if (pList[0] < pList[1])
		max_value_in_last_element = KAL_TRUE;
	else
		max_value_in_last_element = KAL_FALSE;

	if (max_value_in_last_element == KAL_TRUE) {
		for (i = (number - 1); i != 0; i--) {	/* max value in the last element */
			if (pList[i] <= level) {
				battery_log(2, "zzf_%d<=%d     i=%d\n", pList[i], level, i);
				return pList[i];
			}
		}

		battery_log(BAT_LOG_CRTI, "Can't find closest level \r\n");
		return pList[0];
		/* return CHARGE_CURRENT_0_00_MA; */
	} else {
		for (i = 0; i < number; i++) {	/* max value in the first element */
			if (pList[i] <= level)
				return pList[i];
		}

		battery_log(BAT_LOG_CRTI, "Can't find closest level \r\n");
		return pList[number - 1];
		/* return CHARGE_CURRENT_0_00_MA; */
	}
}
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
static unsigned int is_chr_det(void)
{
	unsigned int val = 0;

	val = pmic_get_register_value(PMIC_RGS_CHRDET);
	battery_log(BAT_LOG_CRTI, "[is_chr_det] %d\n", val);

	return val;
}
#endif

static unsigned int charging_hw_init(void *data)
{
	unsigned int status = STATUS_OK;

       sm5414_set_topoff(TOPOFF_150mA);/* termianation current default 150mA */

	sm5414_set_batreg(BATREG_4_4_0_0_V); /* VREG=CV 4.352V (default 4.208V) */

#if defined(SM5414_TOPOFF_TIMER_SUPPORT)
    sm5414_set_autostop(AUTOSTOP_EN); /* enable Autostop function */
    sm5414_set_topofftimer(TOPOFFTIMER_10MIN);
#else
    sm5414_set_autostop(AUTOSTOP_DIS); /* disable Autostop function */
#endif

/*	upmu_set_rg_vcdt_hv_en(0);*/
  
	//SM : set nSHDN pin to high(I2C Function)
	mt_set_gpio_mode(GPIO_SM5414_SHDN_PIN,GPIO_MODE_GPIO);  
	mt_set_gpio_dir(GPIO_SM5414_SHDN_PIN,GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_SM5414_SHDN_PIN,GPIO_OUT_ONE);

#if defined(MTK_WIRELESS_CHARGER_SUPPORT)
	if (wireless_charger_gpio_number != 0) {
#ifdef CONFIG_MTK_LEGACY
		mt_set_gpio_mode(wireless_charger_gpio_number, 0);	/* 0:GPIO mode */
		mt_set_gpio_dir(wireless_charger_gpio_number, 0);	/* 0: input, 1: output */
#else
/*K.S. way here*/
#endif
	}
#endif

#ifdef CONFIG_MTK_DUAL_INPUT_CHARGER_SUPPORT
#ifdef CONFIG_MTK_LEGACY
	mt_set_gpio_mode(vin_sel_gpio_number, 0);	/* 0:GPIO mode */
	mt_set_gpio_dir(vin_sel_gpio_number, 0);	/* 0: input, 1: output */
#else
/*K.S. way here*/
#endif
#endif
	mt_set_gpio_dir((254 | 0x80000000), 1);
	return status;
}

static unsigned int charging_get_bif_vbat(void *data);

static unsigned int charging_dump_register(void *data)
{
	unsigned int status = STATUS_OK;

	battery_log(BAT_LOG_FULL, "charging_dump_register\r\n");
	sm5414_dump_register();

	/*unsigned int vbat;
	   charging_get_bif_vbat(&vbat);
	   battery_log(BAT_LOG_CRTI,"[BIF] vbat=%d mV\n", vbat); */


	return status;
}

static unsigned int charging_enable(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int enable = *(unsigned int *) (data);

	if (KAL_TRUE == enable) {
		sm5414_chg_en(enable);
	} else {
		sm5414_chg_en(enable);
		if (charging_get_error_state())
			battery_log(BAT_LOG_CRTI, "[charging_enable] under test mode: disable charging\n");
	}

	return status;
}

static unsigned int charging_set_cv_voltage(void *data)
{
	unsigned int status;
	unsigned short int array_size;
	unsigned int set_cv_voltage;
	unsigned short int register_value;
	/*static kal_int16 pre_register_value; */

	array_size = GETARRAYNUM(VBAT_CV_VTH);
	status = STATUS_OK;
	/*pre_register_value = -1; */
	battery_log(BAT_LOG_CRTI, "charging_set_cv_voltage set_cv_voltage=%d\n",
		    *(unsigned int *) data);
	set_cv_voltage = bmt_find_closest_level(VBAT_CV_VTH, array_size, *(unsigned int *) data);
	register_value =
	    charging_parameter_to_value(VBAT_CV_VTH, GETARRAYNUM(VBAT_CV_VTH), set_cv_voltage);
	battery_log(BAT_LOG_FULL, "charging_set_cv_voltage register_value=0x%x\n", register_value);
	sm5414_set_batreg(register_value);

	return status;
}


static unsigned int charging_get_current(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int array_size;
	unsigned char reg_value;
	//unsigned int val;

	/*Get current level */
	array_size = GETARRAYNUM(CS_VTH);
    sm5414_read_interface(SM5414_CHGCTRL2, &reg_value, SM5414_CHGCTRL2_FASTCHG_MASK, SM5414_CHGCTRL2_FASTCHG_SHIFT);//FASTCHG
	//*(unsigned int *) data = val;
	*(unsigned int *)data = charging_value_to_parameter(CS_VTH,array_size,reg_value);

	return status;
}


static unsigned int charging_set_current(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int set_chr_current;
	unsigned int array_size;
	unsigned int register_value;
	unsigned int current_value = *(unsigned int *) data;

	array_size = GETARRAYNUM(CS_VTH);
	set_chr_current = bmt_find_closest_level(CS_VTH, array_size, current_value);
	register_value = charging_parameter_to_value(CS_VTH, array_size, set_chr_current);
	/* sm5414_config_interface(sm5414_CON4, register_value, 0x7F, 0); */
    sm5414_set_fastchg(register_value);//FASTCHG
	/*For USB_IF compliance test only when USB is in suspend(Ibus < 2.5mA) or unconfigured(Ibus < 70mA) states*/
#ifdef CONFIG_USBIF_COMPLIANCE
	if (current_value < CHARGE_CURRENT_100_00_MA)
		register_value = 0x7f;
	else
		register_value = 0x13;
	charging_set_vindpm(&register_value);
#endif

	return status;
}

static unsigned int charging_set_input_current(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int current_value = *(unsigned int *) data;
	unsigned int set_chr_current;
	unsigned int array_size;
	unsigned int register_value;

	/*if(current_value >= CHARGE_CURRENT_2500_00_MA)
	   {
	   register_value = 0x6;
	   }
	   else if(current_value == CHARGE_CURRENT_1000_00_MA)
	   {
	   register_value = 0x4;
	   }
	   else
	   { */
	array_size = GETARRAYNUM(INPUT_CS_VTH);
	set_chr_current = bmt_find_closest_level(INPUT_CS_VTH, array_size, current_value);
	register_value = charging_parameter_to_value(INPUT_CS_VTH, array_size, set_chr_current);
	/*} */

	/* sm5414_config_interface(sm5414_CON0, register_value, 0x3F, 0);//input  current */
    sm5414_set_vbuslimit(register_value);//VBUSLIMIT

	return status;
}

static unsigned int charging_get_charging_status(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned char reg_value;

	reg_value = sm5414_get_topoff_status();

	if(reg_value == 0x1)//Fullcharged status
		*(unsigned int *) data = KAL_TRUE;
	else
		*(unsigned int *) data = KAL_FALSE;

	return status;
}

static unsigned int charging_reset_watch_dog_timer(void *data)
{
	unsigned int status = STATUS_OK;

	return status;
}

static unsigned int charging_set_hv_threshold(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int set_hv_voltage;
	unsigned int array_size;
	unsigned short int register_value;
	unsigned int voltage = *(unsigned int *) (data);

	array_size = GETARRAYNUM(VCDT_HV_VTH);
	set_hv_voltage = bmt_find_closest_level(VCDT_HV_VTH, array_size, voltage);
	register_value = charging_parameter_to_value(VCDT_HV_VTH, array_size, set_hv_voltage);
	pmic_set_register_value(PMIC_RG_VCDT_HV_VTH, register_value);

	return status;
}


static unsigned int charging_get_hv_status(void *data)
{
	unsigned int status = STATUS_OK;

	*(kal_bool *) (data) = pmic_get_register_value(PMIC_RGS_VCDT_HV_DET);
	return status;
}


static unsigned int charging_get_battery_status(void *data)
{
	unsigned int status = STATUS_OK;
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
	*(kal_bool *) (data) = 0;
	battery_log(BAT_LOG_CRTI, "bat exist for evb\n");
#else
	unsigned int val = 0;

	val = pmic_get_register_value(PMIC_BATON_TDET_EN);
	battery_log(BAT_LOG_FULL, "[charging_get_battery_status] BATON_TDET_EN = %d\n", val);
	if (val) {
		pmic_set_register_value(PMIC_BATON_TDET_EN, 1);
		pmic_set_register_value(PMIC_RG_BATON_EN, 1);
		*(kal_bool *) (data) = pmic_get_register_value(PMIC_RGS_BATON_UNDET);
	} else {
		*(kal_bool *) (data) = KAL_FALSE;
	}
#endif
	return status;
}


static unsigned int charging_get_charger_det_status(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_MTK_FPGA)
	*(kal_bool *) (data) = 1;
	battery_log(BAT_LOG_CRTI, "chr exist for fpga\n");
#else
	*(kal_bool *) (data) = pmic_get_register_value(PMIC_RGS_CHRDET);
#endif
	return status;
}


kal_bool charging_type_detection_done(void)
{
	return charging_type_det_done;
}


static unsigned int charging_get_charger_type(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
	*(CHARGER_TYPE *) (data) = STANDARD_HOST;
#else
#if defined(MTK_WIRELESS_CHARGER_SUPPORT)
	int wireless_state = 0;

	if (wireless_charger_gpio_number != 0) {
#ifdef CONFIG_MTK_LEGACY
		wireless_state = mt_get_gpio_in(wireless_charger_gpio_number);
#else
/*K.S. way here*/
#endif
		if (wireless_state == WIRELESS_CHARGER_EXIST_STATE) {
			*(CHARGER_TYPE *) (data) = WIRELESS_CHARGER;
			battery_log(BAT_LOG_CRTI, "WIRELESS_CHARGER!\n");
			return status;
		}
	} else {
		battery_log(BAT_LOG_CRTI, "wireless_charger_gpio_number=%d\n", wireless_charger_gpio_number);
	}

	if (g_charger_type != CHARGER_UNKNOWN && g_charger_type != WIRELESS_CHARGER) {
		*(CHARGER_TYPE *) (data) = g_charger_type;
		battery_log(BAT_LOG_CRTI, "return %d!\n", g_charger_type);
		return status;
	}
#endif

	if (is_chr_det() == 0) {
		g_charger_type = CHARGER_UNKNOWN;
		*(CHARGER_TYPE *) (data) = CHARGER_UNKNOWN;
		battery_log(BAT_LOG_CRTI, "[charging_get_charger_type] return CHARGER_UNKNOWN\n");
		return status;
	}

	charging_type_det_done = KAL_FALSE;
	*(CHARGER_TYPE *) (data) = hw_charging_get_charger_type();
	charging_type_det_done = KAL_TRUE;
	g_charger_type = *(CHARGER_TYPE *) (data);

#endif

	return status;
}

static unsigned int charging_get_is_pcm_timer_trigger(void *data)
{
	unsigned int status = STATUS_OK;
	/*
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
	*(kal_bool *) (data) = KAL_FALSE;
#else

	if (slp_get_wake_reason() == WR_PCM_TIMER)
		*(kal_bool *) (data) = KAL_TRUE;
	else
		*(kal_bool *) (data) = KAL_FALSE;

	battery_log(BAT_LOG_CRTI, "slp_get_wake_reason=%d\n", slp_get_wake_reason());
#endif
*/
	return status;
}

static unsigned int charging_set_platform_reset(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	battery_log(BAT_LOG_CRTI, "charging_set_platform_reset\n");
	kernel_restart("battery service reboot system");
#endif

	return status;
}

static unsigned int charging_get_platform_boot_mode(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	*(unsigned int *) (data) = get_boot_mode();

	battery_log(BAT_LOG_CRTI, "get_boot_mode=%d\n", get_boot_mode());
#endif

	return status;
}

static unsigned int charging_set_power_off(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	/*added dump_stack to see who the caller is */
	dump_stack();
	battery_log(BAT_LOG_CRTI, "charging_set_power_off\n");
	kernel_power_off();
#endif

	return status;
}

static unsigned int charging_get_power_source(void *data)
{
	unsigned int status = STATUS_OK;

#if 0				/* #if defined(MTK_POWER_EXT_DETECT) */
	if (MT_BOARD_PHONE == mt_get_board_type())
		*(kal_bool *) data = KAL_FALSE;
	else
		*(kal_bool *) data = KAL_TRUE;
#else
	*(kal_bool *) data = KAL_FALSE;
#endif

	return status;
}

static unsigned int charging_get_csdac_full_flag(void *data)
{
	return STATUS_UNSUPPORTED;
}

static unsigned int charging_set_ta_current_pattern(void *data)
{
	kal_bool pumpup;
	unsigned int increase;

	pumpup = *(kal_bool *) (data);
	if (pumpup == KAL_TRUE)
		increase = 1;
	else
		increase = 0;
	/*unsigned int charging_status = KAL_FALSE; */
#if 0
	//sm5414_pumpx_up(increase);
	battery_log(BAT_LOG_FULL, "Pumping up adaptor...");

#else
	if (increase == KAL_TRUE) {
		sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() on 1");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() off 1");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() on 2");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() off 2");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() on 3");
        msleep(281);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() off 3");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() on 4");
        msleep(281);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() off 4");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() on 5");
        msleep(281);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() off 5");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() on 6");
        msleep(485);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_increase() off 6");
        msleep(50);
        
        battery_log(BAT_LOG_CRTI, "mtk_ta_increase() end \n");
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        msleep(200);
	} else {
		sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() on 1");
        msleep(281);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() off 1");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() on 2");
        msleep(281);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() off 2");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() on 3");
        msleep(281);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() off 3");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() on 4");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() off 4");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() on 5");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() off 5");
        msleep(85);
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() on 6");
        msleep(485);
        
        sm5414_set_vbuslimit(VBUSLIMIT_100mA); /* 100mA */
        battery_log(BAT_LOG_FULL, "mtk_ta_decrease() off 6");
        msleep(50);
        
        battery_log(BAT_LOG_CRTI, "mtk_ta_decrease() end \n");
        
        sm5414_set_vbuslimit(VBUSLIMIT_500mA); /* 500mA */
	}
#endif
	return STATUS_OK;
}

static unsigned int charging_set_vindpm(void *data)
{
	unsigned int status = STATUS_OK;
	//unsigned int v = *(unsigned int *) data;

	//sm5414_set_VINDPM(v);

	return status;
}

static unsigned int charging_set_vbus_ovp_en(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int e = *(unsigned int *) data;

	pmic_set_register_value(PMIC_RG_VCDT_HV_EN, e);

	return status;
}

static unsigned int charging_get_bif_vbat(void *data)
{
	unsigned int status = STATUS_OK;
#ifdef CONFIG_MTK_BIF_SUPPORT
	int vbat = 0;

	/* turn on VBIF28 regulator*/
	/*bif_init();*/

	/*change to HW control mode*/
	/*pmic_set_register_value(PMIC_RG_VBIF28_ON_CTRL, 0);
	pmic_set_register_value(PMIC_RG_VBIF28_EN, 1);*/
	if (bif_checked != 1 || bif_exist == 1) {
		bif_ADC_enable();
		vbat = bif_read16(MW3790_VBAT);
		*(unsigned int *) (data) = vbat;
	}
	/*turn off LDO and change SW control back to HW control */
	/*pmic_set_register_value(PMIC_RG_VBIF28_EN, 0);
	pmic_set_register_value(PMIC_RG_VBIF28_ON_CTRL, 1);*/
#else
	*(unsigned int *) (data) = 0;
#endif
	return status;
}

static unsigned int charging_get_bif_tbat(void *data)
{
	unsigned int status = STATUS_OK;
#ifdef CONFIG_MTK_BIF_SUPPORT
	int tbat = 0;
	int ret;
	int tried = 0;

	mdelay(50);

	if (bif_exist == 1) {
		do {
			bif_ADC_enable();
			ret = bif_read8(MW3790_TBAT, &tbat);
			tried++;
			mdelay(50);
			if (tried > 3)
				break;
		} while (ret != 1);

		if (tried <= 3)
			*(int *) (data) = tbat;
		else
			status =  STATUS_UNSUPPORTED;
	}
#endif
	return status;
}

static unsigned int charging_diso_init(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(MTK_DUAL_INPUT_CHARGER_SUPPORT)
	struct device_node *node;
	DISO_ChargerStruct *pDISO_data = (DISO_ChargerStruct *) data;

	int ret;
	/* Initialization DISO Struct */
	pDISO_data->diso_state.cur_otg_state = DISO_OFFLINE;
	pDISO_data->diso_state.cur_vusb_state = DISO_OFFLINE;
	pDISO_data->diso_state.cur_vdc_state = DISO_OFFLINE;

	pDISO_data->diso_state.pre_otg_state = DISO_OFFLINE;
	pDISO_data->diso_state.pre_vusb_state = DISO_OFFLINE;
	pDISO_data->diso_state.pre_vdc_state = DISO_OFFLINE;

	pDISO_data->chr_get_diso_state = KAL_FALSE;

	pDISO_data->hv_voltage = VBUS_MAX_VOLTAGE;

	/* Initial AuxADC IRQ */
	DISO_IRQ.vdc_measure_channel.number = AP_AUXADC_DISO_VDC_CHANNEL;
	DISO_IRQ.vusb_measure_channel.number = AP_AUXADC_DISO_VUSB_CHANNEL;
	DISO_IRQ.vdc_measure_channel.period = AUXADC_CHANNEL_DELAY_PERIOD;
	DISO_IRQ.vusb_measure_channel.period = AUXADC_CHANNEL_DELAY_PERIOD;
	DISO_IRQ.vdc_measure_channel.debounce = AUXADC_CHANNEL_DEBOUNCE;
	DISO_IRQ.vusb_measure_channel.debounce = AUXADC_CHANNEL_DEBOUNCE;

	/* use default threshold voltage, if use high voltage,maybe refine */
	DISO_IRQ.vusb_measure_channel.falling_threshold = VBUS_MIN_VOLTAGE / 1000;
	DISO_IRQ.vdc_measure_channel.falling_threshold = VDC_MIN_VOLTAGE / 1000;
	DISO_IRQ.vusb_measure_channel.rising_threshold = VBUS_MIN_VOLTAGE / 1000;
	DISO_IRQ.vdc_measure_channel.rising_threshold = VDC_MIN_VOLTAGE / 1000;

	node = of_find_compatible_node(NULL, NULL, "mediatek,AUXADC");
	if (!node) {
		battery_log(BAT_LOG_CRTI, "[diso_adc]: of_find_compatible_node failed!!\n");
	} else {
		pDISO_data->irq_line_number = irq_of_parse_and_map(node, 0);
		battery_log(BAT_LOG_FULL, "[diso_adc]: IRQ Number: 0x%x\n",
			    pDISO_data->irq_line_number);
	}

	mt_irq_set_sens(pDISO_data->irq_line_number, MT_EDGE_SENSITIVE);
	mt_irq_set_polarity(pDISO_data->irq_line_number, MT_POLARITY_LOW);

	ret = request_threaded_irq(pDISO_data->irq_line_number, diso_auxadc_irq_handler,
				   pDISO_data->irq_callback_func, IRQF_ONESHOT, "DISO_ADC_IRQ",
				   NULL);

	if (ret) {
		battery_log(BAT_LOG_CRTI, "[diso_adc]: request_irq failed.\n");
	} else {
		set_vdc_auxadc_irq(DISO_IRQ_DISABLE, 0);
		set_vusb_auxadc_irq(DISO_IRQ_DISABLE, 0);
		battery_log(BAT_LOG_FULL, "[diso_adc]: diso_init success.\n");
	}

#if defined(MTK_DISCRETE_SWITCH) && defined(MTK_DSC_USE_EINT)
	battery_log(BAT_LOG_CRTI, "[diso_eint]vdc eint irq registitation\n");
	mt_eint_set_hw_debounce(CUST_EINT_VDC_NUM, CUST_EINT_VDC_DEBOUNCE_CN);
	mt_eint_registration(CUST_EINT_VDC_NUM, CUST_EINTF_TRIGGER_LOW, vdc_eint_handler, 0);
	mt_eint_mask(CUST_EINT_VDC_NUM);
#endif
#endif

	return status;
}

static unsigned int charging_get_diso_state(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(MTK_DUAL_INPUT_CHARGER_SUPPORT)
	int diso_state = 0x0;
	DISO_ChargerStruct *pDISO_data = (DISO_ChargerStruct *) data;

	_get_diso_interrupt_state();
	diso_state = g_diso_state;
	battery_log(BAT_LOG_FULL, "[do_chrdet_int_task] current diso state is %s!\n",
		    DISO_state_s[diso_state]);
	if (((diso_state >> 1) & 0x3) != 0x0) {
		switch (diso_state) {
		case USB_ONLY:
			set_vdc_auxadc_irq(DISO_IRQ_DISABLE, 0);
			set_vusb_auxadc_irq(DISO_IRQ_DISABLE, 0);
#ifdef MTK_DISCRETE_SWITCH
#ifdef MTK_DSC_USE_EINT
			mt_eint_unmask(CUST_EINT_VDC_NUM);
#else
			set_vdc_auxadc_irq(DISO_IRQ_ENABLE, 1);
#endif
#endif
			pDISO_data->diso_state.cur_vusb_state = DISO_ONLINE;
			pDISO_data->diso_state.cur_vdc_state = DISO_OFFLINE;
			pDISO_data->diso_state.cur_otg_state = DISO_OFFLINE;
			break;
		case DC_ONLY:
			set_vdc_auxadc_irq(DISO_IRQ_DISABLE, 0);
			set_vusb_auxadc_irq(DISO_IRQ_DISABLE, 0);
			set_vusb_auxadc_irq(DISO_IRQ_ENABLE, DISO_IRQ_RISING);
			pDISO_data->diso_state.cur_vusb_state = DISO_OFFLINE;
			pDISO_data->diso_state.cur_vdc_state = DISO_ONLINE;
			pDISO_data->diso_state.cur_otg_state = DISO_OFFLINE;
			break;
		case DC_WITH_USB:
			set_vdc_auxadc_irq(DISO_IRQ_DISABLE, 0);
			set_vusb_auxadc_irq(DISO_IRQ_DISABLE, 0);
			set_vusb_auxadc_irq(DISO_IRQ_ENABLE, DISO_IRQ_FALLING);
			pDISO_data->diso_state.cur_vusb_state = DISO_ONLINE;
			pDISO_data->diso_state.cur_vdc_state = DISO_ONLINE;
			pDISO_data->diso_state.cur_otg_state = DISO_OFFLINE;
			break;
		case DC_WITH_OTG:
			set_vdc_auxadc_irq(DISO_IRQ_DISABLE, 0);
			set_vusb_auxadc_irq(DISO_IRQ_DISABLE, 0);
			pDISO_data->diso_state.cur_vusb_state = DISO_OFFLINE;
			pDISO_data->diso_state.cur_vdc_state = DISO_ONLINE;
			pDISO_data->diso_state.cur_otg_state = DISO_ONLINE;
			break;
		default:	/* OTG only also can trigger vcdt IRQ */
			pDISO_data->diso_state.cur_vusb_state = DISO_OFFLINE;
			pDISO_data->diso_state.cur_vdc_state = DISO_OFFLINE;
			pDISO_data->diso_state.cur_otg_state = DISO_ONLINE;
			battery_log(BAT_LOG_FULL, " switch load vcdt irq triggerd by OTG Boost!\n");
			break;	/* OTG plugin no need battery sync action */
		}
	}

	if (DISO_ONLINE == pDISO_data->diso_state.cur_vdc_state)
		pDISO_data->hv_voltage = VDC_MAX_VOLTAGE;
	else
		pDISO_data->hv_voltage = VBUS_MAX_VOLTAGE;
#endif

	return status;
}

static unsigned int charging_get_error_state(void)
{
	return charging_error;
}

static unsigned int charging_set_error_state(void *data)
{
	unsigned int status = STATUS_OK;

	charging_error = *(unsigned int *) (data);

	return status;
}
/*
static unsigned int charging_set_chrind_ck_pdn(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int pwr_dn;

	pwr_dn = *(unsigned int *) data;

	pmic_set_register_value(PMIC_RG_DRV_CHRIND_CK_PDN, pwr_dn);

	return status;
}
*/
static unsigned int charging_sw_init(void *data)
{
	unsigned int status = STATUS_OK;
	/*put here anything needed to be init upon battery_common driver probe*/
#ifdef CONFIG_MTK_BIF_SUPPORT
	int vbat;

	vbat = 0;
	if (bif_checked != 1) {
		bif_init();
		charging_get_bif_vbat(&vbat);
		if (vbat != 0) {
			battery_log(BAT_LOG_CRTI, "[BIF]BIF battery detected.\n");
			bif_exist = 1;
		} else
			battery_log(BAT_LOG_CRTI, "[BIF]BIF battery _NOT_ detected.\n");
		bif_checked = 1;
	}
#endif
	return status;
}

static unsigned int charging_enable_safetytimer(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int en;

	en = *(unsigned int *) data;
	//sm5414_en_chg_timer(en);

	return status;
}

static unsigned int charging_set_hiz_swchr(void *data)
{
	unsigned int status = STATUS_OK;
	unsigned int en;

	en = *(unsigned int *) data;
	//sm5414_set_en_hiz(en);

	return status;
}

static unsigned int (*const charging_func[CHARGING_CMD_NUMBER]) (void *data) = {
charging_hw_init, charging_dump_register, charging_enable, charging_set_cv_voltage,
	    charging_get_current, charging_set_current, charging_set_input_current,
	    charging_get_charging_status, charging_reset_watch_dog_timer,
	    charging_set_hv_threshold, charging_get_hv_status, charging_get_battery_status,
	    charging_get_charger_det_status, charging_get_charger_type,
	    charging_get_is_pcm_timer_trigger, charging_set_platform_reset,
	    charging_get_platform_boot_mode, charging_set_power_off,
	    charging_get_power_source, charging_get_csdac_full_flag,
	    charging_set_ta_current_pattern, charging_set_error_state, charging_diso_init,
	    charging_get_diso_state, charging_set_vindpm, charging_set_vbus_ovp_en,
	    charging_get_bif_vbat, 
		NULL, //charging_set_chrind_ck_pdn,
		charging_sw_init, charging_enable_safetytimer,
	charging_set_hiz_swchr, charging_get_bif_tbat};

/*
* FUNCTION
*        Internal_chr_control_handler
*
* DESCRIPTION
*         This function is called to set the charger hw
*
* CALLS
*
* PARAMETERS
*        None
*
* RETURNS
*
*
* GLOBALS AFFECTED
*       None
*/
signed int chr_control_interface(CHARGING_CTRL_CMD cmd, void *data)
{
	signed int status;

	if (cmd < CHARGING_CMD_NUMBER) {
		if (charging_func[cmd] != NULL)
			status = charging_func[cmd](data);
		else {
			battery_log(BAT_LOG_CRTI, "[chr_control_interface]cmd:%d not supported\n", cmd);
			status = STATUS_UNSUPPORTED;
		}
	} else
		status = STATUS_UNSUPPORTED;

	return status;
}
