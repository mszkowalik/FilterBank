#pragma once

#ifndef _DELAY
#define _DELAY
#include "Effect.h"

using namespace std;

class Delay :
	public Effect
{
public:
	Delay(FilterSettings _settings = FilterSettings(), Effect* _child = nullptr, ParameterList params = ParameterList());
	Delay(Delay* _delay);
	~Delay();

	int16_t process(vector<sampleInter_t>& inBuffer, vector<sampleInter_t>& outBuffer);
	static ParameterList defaultParams();
	void parameterChanged(string Name);

	circular_buffer<sampleInter_t>* delayCirBuff = nullptr;
	uint64_t delaySamples=0;



};

#endif // !_DELAY

