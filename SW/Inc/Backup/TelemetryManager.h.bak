/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __telemetrymanager_H
#define __telemetrymanager_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "cmsis_os.h"
	
osThreadId TM_TaskHandle;
	
//Tickrates
#define TM_xTaskFrequency	50		//ms CycleTime
#define TM_xGpsFrequency	1000	//ms CycleTime
#define TM_xRdacFrequency	250		//ms CycleTime
	
TickType_t TM_xLastWakeTime;
TickType_t TM_xGpsNextSendTime;
TickType_t TM_xRdacNextSendTime;
	
void TM_Init(void);
	
void TM_CyclicTask(void const * argument);
void TM_RxCpltItCallback(void);
	
	
xQueueHandle rxQueue;	
xQueueHandle rxQueueGPS;

#ifdef __cplusplus
}
#endif
#endif /* __telemetrymanager_H */