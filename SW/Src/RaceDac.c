#include "RaceDac.h"

void RD_Init(void)
{
	strcpy((char*)RD_Last_RC1_Sentence.Sentence, "$RC1,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345*20\r\n");
	strcpy((char*)RD_Last_RC2_Sentence.Sentence, "$RC2,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345,12345*23\r\n");
	RD_Last_RC1_Sentence.length = strlen((char*)RD_Last_RC1_Sentence.Sentence);
	RD_Last_RC2_Sentence.length = strlen((char*)RD_Last_RC2_Sentence.Sentence);
}

void RD_CyclicTask(void const * argument)
{
	TickType_t rc_TimeStamp;
		
	HAL_UART_Receive_DMA(&huart3, RD_pCurBuffer->SentenceData, RD_SENTENCE_BUFFER_DATA_SIZE);
	
	RD_SentenceMutex = xSemaphoreCreateBinary();
	xSemaphoreGive(RD_SentenceMutex);
	
	for (;;)
	{
		vTaskDelay(10);
		rc_TimeStamp = xTaskGetTickCount();
		if (pdTRUE == xSemaphoreTake(RD_SentenceMutex, 100)) {
			RD_Last_RC1_Sentence.timeStamp = rc_TimeStamp;
			RD_Last_RC2_Sentence.timeStamp = rc_TimeStamp;
			xSemaphoreGive(RD_SentenceMutex);
		}
	}
	vTaskDelete(NULL);
}

void RD_RxCpltItCallback(void)
{
	RD_pCurBuffer->SentenceReady = true;
	
	//sanity check
	if (RD_pLastBuffer->SentenceReady == true) 
		++RD_Status_BufferDiscarded;
	else
		++RD_Status_BufferParsed;
	
	//switch buffer
	RD_pLastBuffer = RD_pCurBuffer;
	RD_pCurBuffer = RD_pCurBuffer == &RD_SentenceBuffer[0] ? &RD_SentenceBuffer[1] : &RD_SentenceBuffer[0];
	
	//notify handling task
	xTaskResumeFromISR(RD_TaskHandle);
	
	HAL_UART_Receive_DMA(&huart3, RD_pCurBuffer->SentenceData, RD_SENTENCE_BUFFER_DATA_SIZE);
}