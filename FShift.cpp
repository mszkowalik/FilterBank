#include "FShift.h"
#include "Filter.h"
#include <cstring>
//#include "fft.h"


FShift::FShift(FilterSettings _settings, Effect * _child, ParameterList params) : Effect(_settings, _child)
{
	Name = "Frequency Shift";
	type = Effects::Effect_FShift;
	if (params == ParameterList())
		ParamsList = defaultParams();
	ParamsList.parent = this;
	for (uint16_t i = 0; i < params.list.size(); i++)
		ParamsList.addParameter(params.list[i].Name, params.list[i].value); // adding them here,  that way will force parametersChanged to vaildate input

	FFTSize = settings.bufferSize;
	FFTSamples = FFTSize / 2;
	input.clear();
	output.clear();
	Spectrum.clear();
	SpectrumCmplx.clear();
	FFTPlaceholder.clear();
	Spectrum.resize(FFTSize, sampleInter_t(0));// fills everything with zeros
	SpectrumCmplx.resize(FFTSamples, complex(0, 0));
	input.resize(FFTSize, sampleInter_t(0));
	FFTPlaceholder.resize(FFTSize);
	output.resize(FFTSize, sampleInter_t(0));

	Filter::HanningWindowInit(&HannWindow, FFTSize);
	fft_object = new ffft::FFTReal <sampleInter_t>(FFTSize);

}

FShift::FShift(FShift * _delay) :FShift(_delay->settings, _delay->child, _delay->getParamsList())
{
}

FShift::~FShift()
{
	delete fft_object;
}

int16_t FShift::process(vector<sampleInter_t>& inBuffer, vector<sampleInter_t>& outBuffer)
{
	//frame is processed in two passes. 1# first half of buffer is added to input, then second
	int pass = 0;
	do
	{
		memmove(&input.data()[0], &input.data()[FFTSize/2], (FFTSize / 2)*sizeof(sampleInter_t));
		for (auto i = 0; i < FFTSize / 2; i++) // copy data from inBuffer to second half of input
		{
			input[(FFTSize / 2) + i] = inBuffer[i + (pass * (FFTSize / 2))];// ; // this will take care of copyind first and second half of buffer
		}
		for (int i = 0; i < FFTSize; i++)
		{
			FFTPlaceholder[i] = input[i] * HannWindow[i]; // real numbers
		}

		fft_object->do_fft(Spectrum.data(), FFTPlaceholder.data());
		for (int i = 0; i < FFTSamples; i++)
		{
			SpectrumCmplx[i] = complex(Spectrum[i],Spectrum[i+FFTSamples]);
			Spectrum[i] = SpectrumCmplx[i].amp();
		}
		//convert complex to square Magnitude (stored in spectrum vector)
		//convert Magnitude to Complex, to calculate FFT;
		// FROM HERE YOU CAN WORK ON SpectrumAmp
		sampleInter_t frequency = ParamsList.getParameter("Frequency Shift") / settings.samplingRate; // frequency shift converted to digital frequency
		frequency *= FFTSamples; // frequency now stores value of how many FFT Samples to shift;
		frequency = int(frequency);
		
		for (int i = FFTSamples - frequency; i >= 0; i--)
		{
			Spectrum[i + frequency] = Spectrum[i];
		}
		for (int i = 0; i < frequency; i++)
		{
			Spectrum[i] = 1e-10;
		}

		// TO HERE YOU CAN WORK ON SpectrumAmp
		sampleInter_t factor = 0;
		for (int i = 0; i < FFTSamples; i++)
		{
			factor = Spectrum[i]/ SpectrumCmplx[i].amp();
			SpectrumCmplx[i] *= factor;
		}
		for (int i = 0; i < FFTSamples; i++)
		{
			Spectrum[i] = SpectrumCmplx[i].re();
			Spectrum[i + FFTSamples] = SpectrumCmplx[i].im();
		}
		
		fft_object->do_ifft(Spectrum.data(), FFTPlaceholder.data());
		fft_object->rescale(FFTPlaceholder.data());
		//move vector to left by half size;
		//fill right half with zeros
		//add IFFT result to output buffer
		memmove(&output.data()[0], &output.data()[FFTSize/2], (FFTSize / 2) * sizeof(sampleInter_t));
		memset(&(output.data()[FFTSize/2]), sampleInter_t(0.0), (FFTSize / 2) * sizeof(sampleInter_t));

		//move first half of input buffer to the beggining

		for (auto i = 0; i < FFTSize; i++)
		{
			output[i] += FFTPlaceholder[i];
		}

		for (auto i = 0; i < FFTSize/2; i++)
		{
			outBuffer[i + (pass * (FFTSize / 2))] = output[i];
		}


		pass++;
	} while (pass < 2); // do two passes



	return int16_t();
}

int32_t FShift::minimumSamples()
{
	return int32_t();
}

ParameterList FShift::getParamsList()
{
	return ParamsList;
}

ParameterList FShift::defaultParams()
{
	ParameterList params;
	params.addParameter("Frequency Shift", 100);//hz
	return params;
}

void FShift::parameterChanged(string Name)
{

	int64_t i = 0;
}
