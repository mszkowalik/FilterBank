#pragma once
#ifndef _FILTERSETTINGS
#define _FILTERSETTINGS

#include "Types.h"

/**********************************************************************************************//**
 * \class	FilterSettings
 *
 * \brief	Stores settings for filter instance
 *
 * \author	Mateusz Kowalik
 * \date	12.02.2018
 **************************************************************************************************/

class FilterSettings
{
public:
	FilterSettings();
	~FilterSettings();

	/** \brief	Size of the input buffer */
	uint32_t bufferSize= 1024;
	/** \brief	The sampling rate in herz */
	uint32_t samplingRate = 24000;
	/** \brief	 bit per sample */
	uint32_t sampleBits = sizeof(sampleIn_t) * 8;
	/** \brief	Bytes per sample */
	uint32_t sampleBytes = sizeof(sampleIn_t);
	int16_t channels = 1;

};

#endif