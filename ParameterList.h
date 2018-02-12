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
	sampleParam_t getParameter(string Name);
	void addParameter(string Name, sampleParam_t value);
	void setParameter(string Name, sampleParam_t value);
	bool operator==(ParameterList rhs)const;
	uint16_t size() { return list.size(); };
	Effect* parent = nullptr;
	void clear();
};

#endif