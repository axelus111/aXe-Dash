/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define WS_5VPW_EN_Pin GPIO_PIN_0
#define WS_5VPW_EN_GPIO_Port GPIOC
#define TL_5VPW_EN_Pin GPIO_PIN_1
#define TL_5VPW_EN_GPIO_Port GPIOC
#define PON_Pin GPIO_PIN_2
#define PON_GPIO_Port GPIOC
#define DIS_RESET_Pin GPIO_PIN_3
#define DIS_RESET_GPIO_Port GPIOC
#define CTS_TX_Pin GPIO_PIN_0
#define CTS_TX_GPIO_Port GPIOA
#define RTS_RX_Pin GPIO_PIN_1
#define RTS_RX_GPIO_Port GPIOA
#define TEL_TX_Pin GPIO_PIN_2
#define TEL_TX_GPIO_Port GPIOA
#define TEL_RX_Pin GPIO_PIN_3
#define TEL_RX_GPIO_Port GPIOA
#define AN_12V_Pin GPIO_PIN_4
#define AN_12V_GPIO_Port GPIOA
#define AN_IN5_Pin GPIO_PIN_5
#define AN_IN5_GPIO_Port GPIOA
#define AN_IN6_Pin GPIO_PIN_6
#define AN_IN6_GPIO_Port GPIOA
#define AN_IN7_Pin GPIO_PIN_7
#define AN_IN7_GPIO_Port GPIOA
#define DIS_NEN_Pin GPIO_PIN_4
#define DIS_NEN_GPIO_Port GPIOC
#define GPS_NEN_Pin GPIO_PIN_5
#define GPS_NEN_GPIO_Port GPIOC
#define WS2812B_DO_Pin GPIO_PIN_0
#define WS2812B_DO_GPIO_Port GPIOB
#define RDAC_NEN_Pin GPIO_PIN_1
#define RDAC_NEN_GPIO_Port GPIOB
#define RDAC_TX_Pin GPIO_PIN_10
#define RDAC_TX_GPIO_Port GPIOB
#define RDAC_RX_Pin GPIO_PIN_11
#define RDAC_RX_GPIO_Port GPIOB
#define DIS_CS_Pin GPIO_PIN_12
#define DIS_CS_GPIO_Port GPIOB
#define DIS_SCK_Pin GPIO_PIN_13
#define DIS_SCK_GPIO_Port GPIOB
#define DIS_CD_Pin GPIO_PIN_14
#define DIS_CD_GPIO_Port GPIOB
#define DIS_MOSI_Pin GPIO_PIN_15
#define DIS_MOSI_GPIO_Port GPIOB
#define GPS_TX_Pin GPIO_PIN_6
#define GPS_TX_GPIO_Port GPIOC
#define GPS_RX_Pin GPIO_PIN_7
#define GPS_RX_GPIO_Port GPIOC
#define USB_5V_EXT_NEN_Pin GPIO_PIN_8
#define USB_5V_EXT_NEN_GPIO_Port GPIOA
#define SDIO_SW_Pin GPIO_PIN_15
#define SDIO_SW_GPIO_Port GPIOA
#define DIS_BL_PWM_Pin GPIO_PIN_4
#define DIS_BL_PWM_GPIO_Port GPIOB
#define CAN_EN_Pin GPIO_PIN_7
#define CAN_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
void Error_Handler(void);
/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
