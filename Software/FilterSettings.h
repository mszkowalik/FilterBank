#pragma once
#ifndef _FILTERSETTINGS
#define _FILTERSETTINGS

#include "Types.h"

class FilterSettings
{
public:
	FilterSettings();
	~FilterSettings();

	uint32_t bufferSize= 1024;
	uint32_t samplingRate = 24000;
	uint32_t sampleBits = sizeof(sampleIn_t) * 8;
	uint32_t sampleBytes = sizeof(sampleIn_t);
	int16_t channels = 1;

};

#endif