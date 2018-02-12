#pragma once
#ifndef _EFFECT
#define _EFFECT

#include "Types.h"
#include "ParameterList.h"
#include "FilterSettings.h"

class Effect
{
public:
	Effect(FilterSettings _settings, Effect* _child = nullptr);
	Effect(Effect* _effect);
	~Effect();

	virtual int16_t process(vector<sampleInter_t>& inBuffer, vector<sampleInter_t>& outBuffer) = 0;
	static Effect* EffectFactory(ParameterList params, Effects type, FilterSettings settings);
	Effect* lastChild(Effect* parent);
	ParameterList getParamsList();
	virtual void parameterChanged(string Name) = 0;
	void setParameter(string Name, sampleInter_t value);
	void setParamsList(ParameterList _list);
	
	Effect* child = nullptr; //children effect - for now only wirking in daisy chain
	Effects type;
	string Name;

protected:
	ParameterList ParamsList;
	FilterSettings settings;
	sampleInter_t*inputArray;
	vector<sampleInter_t> sinc;

private:

};

#endif // !_EFFECT

