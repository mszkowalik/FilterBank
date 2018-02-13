#pragma once
#ifndef _PARAMETERSLIST
#define _PARAMETERSLIST

#include "Types.h"
#include "Parameter.h"

class Effect; // forward declaration

class ParameterList
{
public:
	ParameterList();
	~ParameterList();
	vector<Parameter> list;

	///<summary> Returns value of parameter with name Name.</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="Name"> Parameter name.</param>
	///
	///<returns> Parameter Value.</returns>

	sampleParam_t getParameter(string Name);

	///<summary> Adds a parameter to list</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="Name">  Parameter name</param>
	///<param name="value"> Value of added parameter</param>

	void addParameter(string Name, sampleParam_t value);

	///<summary> Sets a parameter with given name to value</summary>
	///
	///<remarks> Mateusz Kowalik, 12.02.2018.</remarks>
	///
	///<param name="Name">  The parameter name.</param>
	///<param name="value"> The new value.</param>

	void setParameter(string Name, sampleParam_t value);
	bool operator==(ParameterList rhs)const;
	uint16_t size() { return list.size(); };
	Effect* parent = nullptr;
	void clear();
};

#endif