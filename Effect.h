#pragma once
#ifndef _EFFECT
#define _EFFECT

#include "Types.h"
#include "ParameterList.h"
#include "FilterSettings.h"

class Effect
{
public:

	///<summary> When _settings is assigned to settings, mechanism is commenced, which calls
	///			 	parameterCchanged method.This way all internal buffers and safeguards are created
	///			 		and checked.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="_settings"> Options for controlling the operation.</param>
	///<param name="_child">    [in,out] (Optional) If non-null, the child.</param>

	Effect(FilterSettings _settings, Effect* _child = nullptr);
	Effect(Effect* _effect);
	~Effect();

	virtual int16_t process(vector<sampleInter_t>& inBuffer, vector<sampleInter_t>& outBuffer) = 0;


	///<summary> Effect factory, creates effect based on type passed to it</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="params">   Parameters of the filter.</param>
	///<param name="type">	   Type of effect to be created.</param>
	///<param name="settings"> Setting of parent filter object. In most cases defines frame size.</param>
	///
	///<returns> Null if it fails, else a pointer to an Effect.</returns>

	static Effect* EffectFactory(ParameterList params, Effects type, FilterSettings settings);

	///<summary> Searches for last effect in daisy chain, and returns its pointer.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="parent"> [in,out] If non-null, pointer to where start.</param>
	///
	///<returns> Null if it fails, else a pointer to last Effect.</returns>

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

