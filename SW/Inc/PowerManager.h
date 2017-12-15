/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __powermanager_H
#define __powermanager_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
	

#define WS_VCC_PINSTATE_EN GPIO_PIN_SET
#define TEL_VCC_PINSTATE_EN GPIO_PIN_SET
#define GPS_VCC_PINSTATE_EN GPIO_PIN_RESET
#define RDAC_VCC_PINSTATE_EN GPIO_PIN_RESET
#define USB_VCC_PINSTATE_EN GPIO_PIN_RESET
#define DIS_VCC_PINSTATE_EN GPIO_PIN_RESET

	typedef enum 
	{
		PM_NONE_VCC    = 0,
		PM_WS2812B_VCC,
		PM_TEL_VCC,
		PM_GPS_VCC,
		PM_RDAC_VCC,
		PM_USB_VCC,
		PM_DIS_VCC
	}tPM_Peripheral_Vcc;
	
	typedef enum 
	{
		PM_NONE        = 0,
		PM_WS2812B,
		PM_TEL,
		PM_GPS,
		PM_RDAC,
		PM_USB,
		PM_DIS,
		PM_DIS_BL,
		PM_SDCARD,
		PM_CAN
	}tPM_Peripheral;

	void PM_Init(void);
	void PM_Enable_Vcc(tPM_Peripheral_Vcc per, bool enable);
	
	void PM_Enable(tPM_Peripheral per);
	void PM_Disable(tPM_Peripheral per);
	
	bool m_bTelEnabled;
	bool m_bWS2812bEnabled;
#ifdef __cplusplus
}
#endif
#endif /*__ __powermanager_H */