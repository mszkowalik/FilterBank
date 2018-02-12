#pragma once
#include "Effect.h"
#include "complex.h"
#include "RFFT/FFTReal.h"
class FShift :
	public Effect
{
public:
	FShift(FilterSettings _settings, Effect* _child = nullptr, ParameterList params = ParameterList());
	FShift(FShift* _delay);
	~FShift();

	virtual int16_t process(vector<sampleInter_t>& inBuffer, vector<sampleInter_t>& outBuffer);
	virtual int32_t minimumSamples();
	virtual ParameterList getParamsList();
	static ParameterList defaultParams() ;

	vector<sampleInter_t> input;// array with transform source/effect
	vector<sampleInter_t> output;// half of last frame is always left
	vector<sampleInter_t> Spectrum;
	vector<sampleInter_t> FFTPlaceholder;
	vector<complex> SpectrumCmplx;
	vector<sampleInter_t> HannWindow;

	uint64_t FFTSize = 512;
	uint16_t FFTSamples;;
	sampleInter_t freqShift;
	virtual void parameterChanged(string Name);
	ffft::FFTReal <sampleInter_t> *fft_object;
};

