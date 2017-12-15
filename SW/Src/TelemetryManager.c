#include "TelemetryManager.h"
#include "PowerManager.h"
#include "GpsManager.h"
#include "RaceDac.h"
#include "usart.h"

char InitMessage[] =	"aXe-Dashboard: Telemetry Manager Init. \r\n";
char CyclicMessage[] =  "aXe-Dashboard: Cyclic Function: TickVal = xxxxxxxx.\r\n";

#define  DataSize 20
uint8_t  Data;

//GpsSentence
#define LastGpsBufferSize 200
uint8_t LastGpsSentence[LastGpsBufferSize];
uint8_t LastGpsSentencePos = 0;
bool	GpsSentenceReady = false;

void TM_Init(void)
{
	if (m_bTelEnabled)
		HAL_UART_Transmit(&huart2, (uint8_t*)InitMessage, 42, 0xfff);	
	
	if (m_bTelEnabled)
	{
		rxQueue = xQueueCreate(DataSize, sizeof(uint8_t));
		HAL_UART_Receive_IT(&huart2, &Data, 1);
	}
	
	rxQueueGPS = NULL;
}

void TM_CyclicTask(void const * argument)
{
	HAL_StatusTypeDef status;	
	
	TM_xLastWakeTime		= xTaskGetTickCount();
	TM_xGpsNextSendTime		= TM_xLastWakeTime + TM_xGpsFrequency;
	TM_xRdacNextSendTime	= TM_xLastWakeTime + TM_xRdacFrequency;
	
	uint8_t buffer;	
	
	rxQueueGPS   = xQueueCreate(500, sizeof(uint8_t));
	
	for (;;)
	{		
		if (TM_xGpsNextSendTime <= TM_xLastWakeTime) 
		{
			if (pdTRUE == xSemaphoreTake(GM_SentenceMutex, 0))
			{				
				TM_xGpsNextSendTime = TM_xLastWakeTime + TM_xGpsFrequency;
				HAL_UART_Transmit(&huart2, GM_Last_RMC_Sentence.Sentence, GM_Last_RMC_Sentence.length, 0xfff);
				HAL_UART_Transmit(&huart2, GM_Last_GGA_Sentence.Sentence, GM_Last_GGA_Sentence.length, 0xfff);
				HAL_UART_Transmit(&huart2, GM_Last_GSA_Sentence.Sentence, GM_Last_GSA_Sentence.length, 0xfff);
				HAL_UART_Transmit(&huart2, GM_Last_VTG_Sentence.Sentence, GM_Last_VTG_Sentence.length, 0xfff);
				//HAL_UART_Transmit(&huart2, GM_Last_GLL_Sentence.Sentence, GM_Last_GLL_Sentence.length, 0xfff);
				xSemaphoreGive(GM_SentenceMutex);
			}
		}
		if (TM_xRdacNextSendTime <= TM_xLastWakeTime) 
		{
			if (pdTRUE == xSemaphoreTake(RD_SentenceMutex, 0))
			{				
				TM_xRdacNextSendTime = TM_xLastWakeTime + TM_xRdacFrequency;
				HAL_UART_Transmit(&huart2, RD_Last_RC1_Sentence.Sentence, RD_Last_RC1_Sentence.length, 0xfff);
				HAL_UART_Transmit(&huart4, RD_Last_RC1_Sentence.Sentence, RD_Last_RC1_Sentence.length, 0xfff);
				//HAL_UART_Transmit(&huart2, GM_Last_GGA_Sentence.Sentence, GM_Last_GGA_Sentence.length, 0xfff);
				xSemaphoreGive(RD_SentenceMutex);
			}
		}
//		//Update Tick Display
//		for (int i = 7; i >=0 ; --i)
//		{
//			CyclicMessage[42 + i] = (tickCur % 10) + '0';
//			tickCur /= 10;
//			
////			for (i = 9; i >= 0; i--) {
////				string[i] = (zahl % 10) + '0';         // Modulo rechnen, dann den ASCII-Code von '0' addieren
////				zahl /= 10;
////			}
//		}		
		
		//Fill the Last Gps Sentence
//		if (!GpsSentenceReady)
//		{
//			uint8_t buf;
//			while (xQueueReceive(rxQueueGPS, &buf, 0) == pdTRUE)
//			{
//				if (buf == '$') 
//					LastGpsSentencePos = 0;
//				
//				LastGpsSentence[LastGpsSentencePos++] = buf;
//				
//				if (buf == '\n')
//				{
//					GpsSentenceReady = true;
//					break;
//				}
//			}
//		}
		
		if (m_bTelEnabled)
		{
//			if (GpsSentenceReady)
//			{
//				HAL_UART_Transmit(&huart2, LastGpsSentence, LastGpsSentencePos, 0xfff);
//				GpsSentenceReady = false;
//				LastGpsSentencePos = 0;
//			}
			while (xQueueReceive(rxQueueGPS,&buffer,0) == pdTRUE)
			{
				HAL_UART_Transmit(&huart2, &buffer, 1, 0xfff);
			}
			
		}
			//osDelay(1000);
		vTaskDelayUntil(&TM_xLastWakeTime, TM_xTaskFrequency);
	}
	vTaskDelete(NULL);
}

void TM_RxCpltItCallback(void)
{

}
