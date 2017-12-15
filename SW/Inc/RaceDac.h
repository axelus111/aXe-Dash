/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __racedac_H
#define __racedac_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdafx.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "usart.h"
#include "cmsis_os.h"

#include "TelemetryManager.h"
	
#define RD_UART_HANDLE &huart3
#define RD_MAX_SENTENCE_SIZE 128
#define RD_SENTENCE_BUFFER_DATA_SIZE 100
#define RD_SENTENCE_BUFFER_SIZE 2
	
/*
 * Sentence format:
 * $RC1,<time>,<count>,<xacc>,<yacc>,<zacc>,<xgyro>,<ygyro>,<zgyro>,
 * <rpm>,<a1>,<a2>,<a3>,<a4>,<a5>*checksum
 * Or
 * $RC2,<time>,<count>,<xacc>,<yacc>,<zacc>,
 * <d1>,<d2>,<a1>,<a2>,<a3>,<a4>,<a5>,<a6>,<a7>,<a8>*checksum	
 Where:
- $ is message start character
- RC1 or RC2 is message identifier
- Time stamp is not used (empty)
- count is an overflowing line counter 0-65535
- xacc,yacc,zacc,xgyro,ygyro,zgyro fields are not used so far (empty)
- dx are digital channel fields, range 0-65535
- ax are analog channel fields, range 0-65535, negative values roll back to 65535 (-1)
- * is message separator character
- NMEA 0183 type checksum
- Each line is terminated with CR LF
*/
		
typedef struct 
{
	uint8_t SentenceData[RD_SENTENCE_BUFFER_DATA_SIZE];
	bool	SentenceReady;	
}tRD_SentenceBuffer;
	
//Last sentences
typedef struct
{
	TickType_t timeStamp;
	uint8_t length;
	uint8_t Sentence[RD_MAX_SENTENCE_SIZE];
}tRD_Sentence;
	
typedef enum
{
	RD_STATE_UNDEFINED,
	RD_STATE_REC,
	RD_STATE_CRC1,
	RD_STATE_CRC2,
	RD_STATE_CPL1,
	RD_STATE_CPL2
}tRD_RdacStates;
	
osThreadId RD_TaskHandle;
	
void RD_Init(void);
	
void RD_CyclicTask(void const * argument);
void RD_RxCpltItCallback(void);
	
tRD_SentenceBuffer RD_SentenceBuffer[RD_SENTENCE_BUFFER_SIZE];
tRD_SentenceBuffer *RD_pCurBuffer;
tRD_SentenceBuffer *RD_pLastBuffer;
	
//parser
tRD_RdacStates RD_ParserState;
	
SemaphoreHandle_t RD_SentenceMutex;
tRD_Sentence RD_Last_RC1_Sentence;
tRD_Sentence RD_Last_RC2_Sentence;
	
	//statistics
uint32_t RD_Status_BufferParsed;
uint32_t RD_Status_BufferDiscarded;
uint32_t RD_Status_Sentences;
uint32_t RD_Status_CRC_Ok;
uint32_t RD_Status_CRC_Error;

#ifdef __cplusplus
}
#endif
#endif /* __racedac_H */