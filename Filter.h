#pragma once
#ifndef _FILTER
#define _FILTER

#include "Types.h"
#include "FilterSettings.h"
#include "Effect.h"
#include "ParameterList.h"

using namespace std;

/**********************************************************************************************//**
 * \class	Filter
 *
 * \brief	Governor class, divides incoming stream of data into smaller frames of size defined in filtersettings instance passed in constructor.
 * 			stores hann window samples - this way space is spared.
 *
 * \author	Mateusz Kowalik
 * \date	12.02.2018
 **************************************************************************************************/

class Filter 
{
public:

	/**********************************************************************************************//**
	 * \fn	Filter::Filter(FilterSettings Settings = FilterSettings());
	 *
	 * \brief	Creates new filter instance, set up input and output buffer, to match frame size.
	 *
	 * \author	Mateusz Kowalik
	 * \date	12.02.2018
	 *
	 * \param	Settings	(Optional) Options for controlling the operation.
	 **************************************************************************************************/

	Filter(FilterSettings Settings = FilterSettings());

	///<summary> Destructor makes sure, that any passed effect will be destroyed. Effect clas will
	///			 make sure any other effect down the line.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>

	~Filter();

	///<summary> Adds samples to input buffer.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="buffer">	    [in,out] If non-null, input buffer containing samples.</param>
	///<param name="samplesNumber"> The samples number.</param>
	///<param name="stride">	    (Optional) 1 if input samples are intertwined (left and right
	///								channel).</param>
	///
	///<returns> how many samples to fill input buffer, if samplesNumber is bigger than samples needed
	///			 to fill buffer, negative number is returned with discarded samples amount.</returns>

	int16_t addSamples(sampleIn_t* buffer, uint16_t samplesNumber, uint8_t stride = 1);

	///<summary> Returns output buffer samples in proper order.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="buffer">	    [in,out] If non-null, buffer to which write samples.</param>
	///<param name="samplesNumber"> Amount of samples to be copied into buffer array.</param>
	///<param name="stride">	    (Optional) Whether samples are intertwined.</param>
	///
	///<returns> The samples.</returns>

	int16_t getSamples(sampleOut_t* buffer, uint16_t samplesNumber, uint8_t stride = 1);

	int16_t Process();
	int16_t howMuchToFill() { return untilNextFrame; };
	int16_t untilNextFrame; //stores number of samples needed to fill input buffer

	Effect* effect = nullptr; //stores all Effects that are in use
	FilterSettings getSettings() { return settings;};
	Effect* getChild() { return effect; };
	void setChild(Effect*_child) { effect = _child; };

	///<summary> Initializes Hanning window, wchich is used in Effect objects.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="buffer"> [in,out] If non-null, buffer to which Windows is written to.</param>
	///<param name="size">   The size.</param>

	static void HanningWindowInit(vector<sampleInter_t>* buffer, uint16_t size);
private:
	
	FilterSettings settings;

	vector<sampleInter_t> HannWindow;
	///<summary> stores all inputData.</summary>
	vector<sampleInter_t> inputBuffer;
	///<summary> stores all inputData.</summary>
	vector<sampleInter_t> outputBuffer;

	uint16_t outputHead = 0;
	uint16_t inputHead = 0;
};
#endif