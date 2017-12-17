#include "GpsManager.h"

#include <stdlib.h>
#include <string.h>

void GM_Init(void)
{
	//Init the Sentence Buffers
	for (int i = 0; i < GM_SENTENCE_BUFFER_SIZE; ++i)
	{
		for (int j = 0; j < GM_SENTENCE_BUFFER_DATA_SIZE; ++j)
		{
			GM_SentenceBuffer[i].SentenceData[j] = j;
		}
		GM_SentenceBuffer[i].SentenceReady = false;
	}
	GM_pLastBuffer =  &GM_SentenceBuffer[1];
	GM_pCurBuffer = &GM_SentenceBuffer[0];
	
	GM_Status_BufferDiscarded = 0;
	GM_Status_BufferParsed = 0;
}

void GM_CyclicTask(void const * argument)
{	
	HAL_UART_Receive_DMA(&huart6, GM_pCurBuffer->SentenceData, GM_SENTENCE_BUFFER_DATA_SIZE);
	tNMEA_States parserState = NMEA_STATE_UNDEFINED;
	
	bool rdy = false;
	
	uint8_t curChar;
	uint8_t curSentence[GM_MAX_SENTENCE_SIZE];
	uint8_t curPos = 0;
	
	uint8_t CRC1, CRC2;
	uint8_t curCRC = 0;
	
	GM_SentenceMutex = xSemaphoreCreateBinary();
	xSemaphoreGive(GM_SentenceMutex);	
	
	uint32_t tsNow = 0;
	
	for (;;)
	{		
		vTaskSuspend(NULL);
		tsNow = xTaskGetTickCount();
	
		for (int pos = 0; pos < GM_SENTENCE_BUFFER_DATA_SIZE; ++pos)
		{		
			curChar = GM_pLastBuffer->SentenceData[pos];
			
			if (curPos >= GM_MAX_SENTENCE_SIZE) Error_Handler();
			
			if (!NMEA_BuildSentence(&parserState, &curPos, &curCRC, &curChar, curSentence, &CRC1, &CRC2, &GM_Status_Sentences, &GM_Status_CRC_Ok, &GM_Status_CRC_Error, &rdy)) 
				Error_Handler();
			if (rdy) 
			{
				if (pdTRUE == xSemaphoreTake(GM_SentenceMutex, 100)) {
					if (strncmp("$GPVTG", (const char*)curSentence, 6) == 0) {
						GM_Last_VTG_Sentence.timeStamp = tsNow;
						GM_Last_VTG_Sentence.length = curPos;
						strcpy((char*)GM_Last_VTG_Sentence.Sentence, (const char*)curSentence);
					}					
					else if (strncmp("$GPRMC", (const char*)curSentence, 6) == 0) {
						GM_Last_RMC_Sentence.timeStamp = tsNow;
						GM_Last_RMC_Sentence.length = curPos;
						strcpy((char*)GM_Last_RMC_Sentence.Sentence, (const char*)curSentence);
						{
							static uint32_t ts = 0;
							static uint8_t  on = 0;
							if (tsNow - ts > 1000)
							{
								if (on) WS_SetColorF(1, 0, 0, 0);
								else WS_SetColorF(1, 0, 1, 0);
								on = !on;
								ts = tsNow;
							}
						}
					}
					else if (strncmp("$GPGGA", (const char*)curSentence, 6) == 0) {
						GM_Last_GGA_Sentence.timeStamp = tsNow;
						GM_Last_GGA_Sentence.length = curPos;
						strcpy((char*)GM_Last_GGA_Sentence.Sentence, (const char*)curSentence);
					}
					else if (strncmp("$GPGSA", (const char*)curSentence, 6) == 0) {
						GM_Last_GSA_Sentence.timeStamp = tsNow;
						GM_Last_GSA_Sentence.length = curPos;
						strcpy((char*)GM_Last_GSA_Sentence.Sentence, (const char*)curSentence);
					}
					else if (strncmp("$GPGLL", (const char*)curSentence, 6) == 0) {
						GM_Last_GLL_Sentence.timeStamp = tsNow;
						GM_Last_GLL_Sentence.length = curPos;
						strcpy((char*)GM_Last_GLL_Sentence.Sentence, (const char*)curSentence);
					}
					else if (strncmp("$GPGSV", (const char*)curSentence, 6) == 0) {
						GM_Last_GSV_Sentence.timeStamp = tsNow;
						GM_Last_GSV_Sentence.length = curPos;
						strcpy((char*)GM_Last_GSV_Sentence.Sentence, (const char*)curSentence);
					}
					xSemaphoreGive(GM_SentenceMutex);
				}
			}				
		}
		
		//vTaskDelay(20);
		
		GM_pLastBuffer->SentenceReady = false;
	}
	
	vTaskDelete(NULL);
}

void GM_RxCpltItCallback(void)
{
	GM_pCurBuffer->SentenceReady = true;
	
	//sanity check
	if (GM_pLastBuffer->SentenceReady == true)
	{
		++GM_Status_BufferDiscarded;
		WS_SetColorF(GM_LED_ERROR, 1, 0, 0);
	}
	else
		++GM_Status_BufferParsed;
	
	//switch buffer
	GM_pLastBuffer = GM_pCurBuffer;
	GM_pCurBuffer = GM_pCurBuffer == &GM_SentenceBuffer[0] ? &GM_SentenceBuffer[1] : &GM_SentenceBuffer[0];
	
	//notify handling task
	xTaskResumeFromISR(GM_TaskHandle);
	
	HAL_UART_Receive_DMA(&huart6, GM_pCurBuffer->SentenceData, GM_SENTENCE_BUFFER_DATA_SIZE);
}
