/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ws2812b_H
#define __ws2812b_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include "stdafx.h"
#include "PowerManager.h"
	
#include "stm32f4xx_hal.h"
#include "main.h"
#include "tim.h"
	
#define WS2812_FREQ		 		(800000) 			// it is fixed: WS2812 require 800kH
#define TIMER_PERIOD	 		(16800000 / WS2812_FREQ)
#define LED_NUMBER		 		(19)					// how many LEDs the MCU should control?
#define LED_DATA_SIZE	 		(LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN		(50)
#define RESET_SLOTS_END	 		(50)
#define WS2812_LAST_SLOT 		(1)
#define LED_BUFFER_SIZE	 		(RESET_SLOTS_BEGIN + LED_DATA_SIZE + WS2812_LAST_SLOT + RESET_SLOTS_END)
#define WS2812_0		 		(TIMER_PERIOD / 3)				// WS2812's zero high time is long about one third of the period
#define WS2812_1		 		(TIMER_PERIOD * 2 / 3)		// WS2812's one high time is long about two thirds of the period
#define WS2812_RESET	 		(0)
	
	void WS_Init();
	
	void WS_FillBufferBlack(void);
	void WS_FillBufferWhite(void);
	
	void WS_SetLedColor(uint32_t LEDnumber, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
	void WS_SetWholeColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE);
	
	void WS_SetColorF(uint32_t LEDnumber, float red, float green, float blue);
	void WS_SetBrightnessF(float brightness);
	
	//internal
	void WS_UpdateBrightness();
	
	float m_Brightness;
	
#ifdef __cplusplus
}
#endif
#endif /* __ws2812b_H */