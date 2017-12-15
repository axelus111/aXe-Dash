/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __nmeahelper_H
#define __nmeahelper_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include "stdint.h"
#include "stdbool.h"
	
typedef enum
{
	NMEA_STATE_UNDEFINED,
	NMEA_STATE_REC,
	NMEA_STATE_CRC1,
	NMEA_STATE_CRC2,
	NMEA_STATE_CPL1,
	NMEA_STATE_CPL2
}tNMEA_States;
	
	
bool NMEA_CheckCRC(const uint8_t *CRC1, const uint8_t *CRC2, const uint8_t *Checksum);
	
bool NMEA_BuildSentence(tNMEA_States *pState, uint8_t *pCurPos, uint8_t *pCurCRC, uint8_t *pCurChar, uint8_t curSentence[], uint8_t *pCRC1, uint8_t *pCRC2, uint32_t *pStatSentences, uint32_t *pStatCrcOk, uint32_t *pStatCrcError, bool *sentenceReady);
	
#ifdef __cplusplus
}
#endif
#endif /* __nmeahelper_H */