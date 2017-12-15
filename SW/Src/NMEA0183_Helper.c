#include "NMEA0183_Helper.h"

	
bool NMEA_CheckCRC(const uint8_t *CRC1, const uint8_t *CRC2, const uint8_t *Checksum)
{
	uint8_t checksum = 0;
	if (*CRC1 >= '0' && *CRC1 <= '9') checksum = (*CRC1 - '0') << 4;	
	else if (*CRC1 >= 'A' && *CRC1 <= 'F') checksum = ((*CRC1 - 'A') + 10) << 4;
	
	if (*CRC2 >= '0' && *CRC2 <= '9') checksum |= (*CRC2 - '0');	
	else if (*CRC2 >= 'A' && *CRC2 <= 'F') checksum |= ((*CRC2 - 'A') + 10);
	
	return checksum == *Checksum;
}

bool NMEA_BuildSentence(tNMEA_States *pState, uint8_t *pCurPos, uint8_t *pCurCRC, uint8_t *pCurChar, uint8_t curSentence[], uint8_t *pCRC1, uint8_t *pCRC2, uint32_t *pStatSentences, uint32_t *pStatCrcOk, uint32_t *pStatCrcError, bool *sentenceReady)
{
	*sentenceReady = false;
	switch (*pState)
	{
	case NMEA_STATE_UNDEFINED: //Wait for SOS
		(*pCurPos) = 0;
		(*pCurCRC) = 0;
		if ((*pCurChar) != '$') break;
		// $ received we have a new sentence
		++(*pStatSentences);
		curSentence[(*pCurPos)++] = (*pCurChar);
		(*pState) = NMEA_STATE_REC;
		break;
	case NMEA_STATE_REC:
		if ((*pCurChar) == '*') (*pState) = NMEA_STATE_CRC1; 
		else if ((*pCurChar) == '\r') (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) == '\n') (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) == '$')  (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) ==  0)  (*pState) = NMEA_STATE_UNDEFINED;
		else
		{					
			curSentence[(*pCurPos)++] = (*pCurChar);
			(*pCurCRC) ^= (*pCurChar);
			break;
		}
	case NMEA_STATE_CRC1:				
		curSentence[(*pCurPos)++] = (*pCurChar);
		if ((*pCurChar) == '*') break;
		else if ((*pCurChar) == '\r') (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) == '\n') (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) == '$')  (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) ==  0)   (*pState) = NMEA_STATE_UNDEFINED;
		else 
		{
			(*pCRC1) = (*pCurChar);
			(*pState) = NMEA_STATE_CRC2;
		}
		break;
	case NMEA_STATE_CRC2:					
		curSentence[(*pCurPos)++] = (*pCurChar);
		if ((*pCurChar) == '\r')	  (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) == '\n') (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) == '$')  (*pState) = NMEA_STATE_UNDEFINED;
		else if ((*pCurChar) ==  0)   (*pState) = NMEA_STATE_UNDEFINED;
		else 
		{
			(*pCRC2) = (*pCurChar);
			(*pState) = NMEA_STATE_CPL1;
		}
		break;
	case NMEA_STATE_CPL1:		
		curSentence[(*pCurPos)++] = (*pCurChar);
		if ((*pCurChar) != '\r') (*pState) = NMEA_STATE_UNDEFINED;
		else (*pState) = NMEA_STATE_CPL2;
		break;
	case NMEA_STATE_CPL2:		
		curSentence[(*pCurPos)++] = (*pCurChar);
		if ((*pCurChar) != '\n') (*pState) = NMEA_STATE_UNDEFINED;
		else 
		{				
			if (NMEA_CheckCRC(pCRC1, pCRC2, pCurCRC))
			{
				++(*pStatCrcOk);
				*sentenceReady = true;
			}	
			else
			{
				++(*pStatCrcError);
			}
			(*pState) = NMEA_STATE_UNDEFINED;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}