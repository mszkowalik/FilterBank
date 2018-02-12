#include "Parameter.h"


Parameter::Parameter(string _name, sampleParam_t _value)
{
	Name = _name;
	value = _value;
}

Parameter::~Parameter()
{
}

bool Parameter::operator==(Parameter & rhs) const
{
	bool ret;
	ret = (rhs.value == value && rhs.Name == Name) ? true : false;
	return ret;
}

