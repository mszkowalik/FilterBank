#pragma once
#ifndef _PARAMETER
#define _PARAMETER

#include "Types.h"

using namespace std;
class Parameter
{
public:
	Parameter(string _name = "", sampleParam_t _value = sampleParam_t(0));
	~Parameter();
	string Name;
	sampleParam_t value;
	bool visible = false;
	bool operator==(Parameter& rhs)const;
};

#endif // !_PARAMETER
