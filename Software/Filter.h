#pragma once
#ifndef _FILTER
#define _FILTER

#include "Types.h"
#include "FilterSettings.h"
#include "Effect.h"
#include "ParameterList.h"

using namespace std;

class Filter 
{
public:
	Filter(FilterSettings Settings = FilterSettings());
	~Filter();

	int16_t addSamples(sampleIn_t* buffer, uint16_t samplesNumber, uint8_t stride = 1);
	int16_t getSamples(sampleOut_t* buffer, uint16_t samplesNumber, uint8_t stride = 1);

	int16_t Process();
	int16_t howMuchToFill() { return untilNextFrame; };
	int16_t untilNextFrame; //stores number of samples needed to fill input buffer

	Effect* effect = nullptr; //stores all Effects that are in use
	FilterSettings getSettings() { return settings;};
	Effect* getChild() { return effect; };
	void setChild(Effect*_child) { effect = _child; };
	static void HanningWindowInit(vector<sampleInter_t>* buffer, uint16_t size);
private:
	
	FilterSettings settings;
	vector<sampleInter_t> HannWindow;// [256];
	vector<sampleInter_t> inputBuffer; // stores all inputData
	vector<sampleInter_t> outputBuffer; // stores all inputData

	uint16_t outputHead = 0;
	uint16_t inputHead = 0;
};
#endif