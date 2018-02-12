#include "Filter.h"
#include "Delay.h"
#include "FShift.h"


Filter::Filter(FilterSettings Settings)
{
	settings = Settings;

	untilNextFrame = settings.bufferSize;


	inputBuffer.resize(settings.bufferSize);
	outputBuffer.resize(settings.bufferSize);
}
Filter::~Filter()
{
	if (effect) delete effect;
}

int16_t Filter::addSamples(sampleIn_t * buffer, uint16_t samplesNumber, uint8_t stride)
{

	int16_t samplesToAdd = 0;
	int16_t ret = 0;
	if (samplesNumber > untilNextFrame)
		samplesToAdd = untilNextFrame;
	else
		samplesToAdd = samplesNumber;

	ret = untilNextFrame - samplesNumber;

	for (int16_t i = 0; i < samplesToAdd; i++)
	{
		inputBuffer[inputHead + i] = INTER_T(buffer[i*stride]);
	}

	inputHead += samplesToAdd;
	untilNextFrame -= samplesToAdd;

	return ret;
}

int16_t Filter::getSamples(sampleOut_t * buffer, uint16_t samplesNumber, uint8_t stride)
{
	int dataToSend;
	if (samplesNumber > settings.bufferSize - outputHead)
		dataToSend = settings.bufferSize - outputHead;
	else dataToSend = samplesNumber;

	for (int i = 0; i < dataToSend; i++)
	{
		buffer[i*stride] = outputBuffer[i + outputHead];
	}

	if (outputHead + dataToSend >= settings.bufferSize)
		outputHead = 0;
	else
		outputHead += dataToSend;

	return (settings.bufferSize) - outputHead;
}

int16_t Filter::Process()
{
	untilNextFrame = settings.bufferSize;
	inputHead = 0;

	Effect* currentEffect = effect;

	if (currentEffect == nullptr)
		outputBuffer = inputBuffer;

	else
		while (currentEffect)
		{
			currentEffect->process(inputBuffer, outputBuffer);
			currentEffect = currentEffect->child;
		}



	return 0;
}

void Filter::HanningWindowInit(vector<sampleInter_t>* buffer, uint16_t size)
{
	buffer->resize(size);
	for (auto i = 0; i < buffer->size(); i++)
	{
		//buffer->at(i) = INTER_T(0.54) - (INTER_T(0.46) * cos((2 * _PI * i) / (size - 1)));
		buffer->at(i) = INTER_T(0.5) * (1 - cos(INTER_T(2) * _PI * i / (size)));
	}
	return;
}
