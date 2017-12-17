#include "PowerManager.h"
#include "usart.h"

const char WelcomeMessage[] = "aXe-Dashboard: Telemetry starting up.  \r\n";
const char ExitMessage[] =	"aXe-Dashboard: Telemetry shutting down.\r\n";

void PM_Init(void)
{	
	PM_Enable_Vcc(PM_TEL_VCC, false);
	PM_Enable_Vcc(PM_WS2812B_VCC, false);
	PM_Enable_Vcc(PM_GPS_VCC, false);
	PM_Enable_Vcc(PM_RDAC_VCC, true); //curently enabled for safety reasons, R24 too small -> high current when disabled. Fix R26!
	PM_Enable_Vcc(PM_USB_VCC, false);
	PM_Enable_Vcc(PM_DIS_VCC, false);
	
	m_bWS2812bEnabled = false;
	m_bTelEnabled = false;
	
	PM_Enable(PM_RDAC);
	PM_Enable(PM_GPS);
	PM_Enable(PM_TEL);
}

void PM_Enable_Vcc(tPM_Peripheral_Vcc per, bool enable)
{
	switch (per)
	{
	case PM_NONE_VCC:
		break;
	case PM_WS2812B_VCC:
		HAL_GPIO_WritePin(WS_5VPW_EN_GPIO_Port, WS_5VPW_EN_Pin, enable ? WS_VCC_PINSTATE_EN : !WS_VCC_PINSTATE_EN);
		break;
	case PM_TEL_VCC:
		HAL_GPIO_WritePin(TL_5VPW_EN_GPIO_Port, TL_5VPW_EN_Pin, enable ? TEL_VCC_PINSTATE_EN : !TEL_VCC_PINSTATE_EN);
		break;
	case PM_GPS_VCC:
		HAL_GPIO_WritePin(GPS_NEN_GPIO_Port, GPS_NEN_Pin, enable ? GPS_VCC_PINSTATE_EN : !GPS_VCC_PINSTATE_EN);
		break;
	case PM_RDAC_VCC:
		//HAL_GPIO_WritePin(RDAC_NEN_GPIO_Port, RDAC_NEN_Pin, enable ? RDAC_VCC_PINSTATE_EN : !RDAC_VCC_PINSTATE_EN);
		HAL_GPIO_WritePin(RDAC_NEN_GPIO_Port, RDAC_NEN_Pin, RDAC_VCC_PINSTATE_EN); //allways enable
		break;
	case PM_USB_VCC:
		HAL_GPIO_WritePin(USB_5V_EXT_NEN_GPIO_Port, USB_5V_EXT_NEN_Pin, enable ? USB_VCC_PINSTATE_EN : !USB_VCC_PINSTATE_EN);
		break;
	case PM_DIS_VCC:
		HAL_GPIO_WritePin(DIS_NEN_GPIO_Port, DIS_NEN_Pin, enable ? DIS_VCC_PINSTATE_EN : !DIS_VCC_PINSTATE_EN);
		break;
	default:
		break;
	}
}

void PM_Enable(tPM_Peripheral per)
{
	switch (per)
	{
	case PM_RDAC:
		PM_Enable_Vcc(PM_RDAC_VCC, true);
		break;
	case PM_GPS:
		PM_Enable_Vcc(PM_GPS_VCC, true);
		break;
	case PM_TEL:
		PM_Enable_Vcc(PM_TEL_VCC, true);
		m_bTelEnabled = true;
		
		//Transmit the Welcome Message
		HAL_Delay(2000);
		HAL_UART_Transmit(&huart2, (uint8_t*)WelcomeMessage, 42, 0xfff);
		
		break;	
	case PM_WS2812B:
		PM_Enable_Vcc(PM_WS2812B_VCC, true);
		m_bWS2812bEnabled = true;		
		break;
	default:
		break;		
	}
}

void PM_Disable(tPM_Peripheral per)
{
	switch (per)
	{
	case PM_RDAC:
		PM_Enable_Vcc(PM_RDAC_VCC, false);
		break;
	case PM_GPS:
		PM_Enable_Vcc(PM_GPS_VCC, false);
		break;
	case PM_TEL:		
		//Transmit the Exit Message
		HAL_UART_Transmit(&huart2, (uint8_t*)ExitMessage, 42, 0xfff);		
		HAL_Delay(100);
		
		m_bTelEnabled = false;
		PM_Enable_Vcc(PM_TEL_VCC, false);
		break;
	default:
		break;		
	}
}