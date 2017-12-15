#include "WS2812B.h"

static uint16_t LEDbuffer[LED_BUFFER_SIZE];

void WS_Init()
{
	PM_Enable(PM_WS2812B);
	
	m_Brightness = 0;
	
	WS_FillBufferBlack();
	//WS_FillBufferWhite();
	
//	WS_SetLedColor(0, 255, 0, 0);
//	WS_SetLedColor(1, 0, 255, 0);
//	WS_SetLedColor(2, 0, 0, 255);
//	WS_SetLedColor(3, 255, 255, 255);
//	WS_SetLedColor(4, 100, 0, 0);
//	WS_SetLedColor(5, 0, 100, 0);
//	WS_SetLedColor(6, 0, 0, 100);
//	WS_SetLedColor(7, 100, 100, 100);
	
	//WS_SetBrightnessF(0.1);
	WS_SetBrightnessF(1.0/255.0);
//	WS_SetColorF(0, 1, 0, 0);
//	WS_SetColorF(1, 0, 1, 0);
//	WS_SetColorF(2, 0, 0, 1);
//	WS_SetColorF(3, 1, 1, 0);
//	WS_SetColorF(4, 1, 0, 1);
//	WS_SetColorF(5, 0, 1, 1);
//	WS_SetColorF(6, 1, 1, 1);
//	WS_SetColorF(7, 1, 1, 1);
//	WS_SetColorF(8, 1, 1, 1);
//	WS_SetColorF(9, 1, 1, 1);	
//	WS_SetColorF(10, 0, 1, 1);
//	WS_SetColorF(11, 1, 0, 1);
//	WS_SetColorF(12, 1, 1, 0);
//	WS_SetColorF(13, 0, 0, 1);
//	WS_SetColorF(14, 0, 0, 1);
//	WS_SetColorF(15, 0, 1, 0);
//	WS_SetColorF(16, 1, 0, 0);
	
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, (uint32_t *)  LEDbuffer, LED_BUFFER_SIZE);
}

void WS_FillBufferBlack()
{
		/*Fill LED buffer - ALL OFF*/
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < RESET_SLOTS_BEGIN; index++) {
		LEDbuffer[buffIndex++] = WS2812_RESET;
	}
	for (index = 0; index < LED_DATA_SIZE; index++) {
		LEDbuffer[buffIndex++] = WS2812_0;
	}
	LEDbuffer[buffIndex++] = WS2812_0;
	for (index = 0; index < RESET_SLOTS_END; index++) {
		LEDbuffer[buffIndex++] = 0;
	}
}
void WS_FillBufferWhite(void) {
	/*Fill LED buffer - ALL ON*/
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < RESET_SLOTS_BEGIN; index++) {
		LEDbuffer[buffIndex++] = WS2812_RESET;
	}
	for (index = 0; index < LED_DATA_SIZE; index++) {
		LEDbuffer[buffIndex++] = WS2812_1;
	}
	LEDbuffer[buffIndex++] = WS2812_0;
	for (index = 0; index < RESET_SLOTS_END; index++) {
		LEDbuffer[buffIndex++] = 0;
	}
}

void WS_SetLedColor(uint32_t LEDnumber, uint8_t RED, uint8_t GREEN, uint8_t BLUE) {
	uint8_t tempBuffer[24];
	uint32_t i;
	uint32_t LEDindex;
	LEDindex = LEDnumber % LED_NUMBER;

	for (i = 0; i < 8; i++) // GREEN data
		tempBuffer[i] = ((GREEN << i) & 0x80) ? WS2812_1 : WS2812_0;
	for (i = 0; i < 8; i++) // RED
		tempBuffer[8 + i] = ((RED << i) & 0x80) ? WS2812_1 : WS2812_0;
	for (i = 0; i < 8; i++) // BLUE
		tempBuffer[16 + i] = ((BLUE << i) & 0x80) ? WS2812_1 : WS2812_0;

	for (i = 0; i < 24; i++)
		LEDbuffer[RESET_SLOTS_BEGIN + LEDindex * 24 + i] = tempBuffer[i];
}
void WS_SetWholeColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE) {
	uint32_t index;

	for (index = 0; index < LED_NUMBER; index++)
		WS_SetLedColor(index, RED, GREEN, BLUE);
}

void WS_SetColorF(uint32_t LEDnumber, float red, float green, float blue)
{
	uint8_t rd, gn, bl;
	//saturation	
	if (red > 1)				rd = m_Brightness;
	else if (red < 0)			rd = 0;
	else						rd = m_Brightness * red;
	
	if (green > 1)				gn = m_Brightness;
	else if (green < 0)			gn = 0;
	else						gn = m_Brightness * green;
	
	if (blue > 1)				bl = m_Brightness;
	else if (blue < 0)			bl = 0;
	else						bl = m_Brightness * blue;
	
	WS_SetLedColor(LEDnumber, rd, gn, bl);
}

void WS_SetBrightnessF(float brightness)
{
	static const float MAX_BRIGHTNESS = 255;
	
	//saturation
	if (brightness > 1)			m_Brightness = MAX_BRIGHTNESS;
	else if (brightness < 0)	m_Brightness = 0;
	else						m_Brightness = brightness * MAX_BRIGHTNESS;
}
