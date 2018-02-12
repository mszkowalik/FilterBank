#include "Delay.h"
#include "Filter.h"

Delay::Delay(FilterSettings _settings, Effect * _child, ParameterList params):Effect(_settings,_child)
{
	Name = "Delay";
	type = Effects::Effect_Delay;
	if (params == ParameterList())
		ParamsList = defaultParams();
	ParamsList.parent = this;
	for (uint16_t i = 0; i < params.list.size(); i++)
		ParamsList.addParameter(params.list[i].Name, params.list[i].value); // adding them that way will force parametersChanged to vaildate input

	delayCirBuff = new circular_buffer<sampleInter_t>(delaySamples);
	delayCirBuff->clear();
}

Delay::Delay(Delay * _delay):Delay(_delay->settings,_delay->child,_delay->getParamsList())
{
	
}


Delay::~Delay()
{
}

int16_t Delay::process(vector<sampleInter_t>& inBuffer, vector<sampleInter_t>& outBuffer)
{
	for (int i = 0; i < settings.bufferSize; i++)
	{
		delayCirBuff->put(inBuffer[i]);
		if (i < delaySamples)
			outBuffer[i] = inBuffer[i] + delayCirBuff->get();
		else
			outBuffer[i] = inBuffer[i];
	}
	return 0;
}

ParameterList Delay::defaultParams()
{
	ParameterList params;
	params.addParameter("delay_ms", 100);
	return params;
}

void Delay::parameterChanged(string Name)
{
	if (Name == "delay_ms")
	{
		delaySamples = (ParamsList.getParameter("delay_ms")/1000)*settings.samplingRate;
		delaySamples = (delaySamples >  0) ? delaySamples : 0;
		
		if(delayCirBuff)
		{
			if (delaySamples != delayCirBuff->size())
			{
				delete delayCirBuff;
				delayCirBuff = new circular_buffer<sampleInter_t>(delaySamples);
				delayCirBuff->clear();
			}
		}

		else
		{
			delayCirBuff = new circular_buffer<sampleInter_t>(delaySamples);
			delayCirBuff->clear();
		}
		
	}

}
