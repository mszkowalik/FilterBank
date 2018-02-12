#include "ParameterList.h"
#include "Effect.h"


ParameterList::ParameterList()
{
}


ParameterList::~ParameterList()
{
}

sampleParam_t ParameterList::getParameter(string Name)
{
	for (uint16_t i = 0; i < list.size(); i++)
	{
		if (list[i].Name == Name)
		{
			return list[i].value;
		}
	}

	return sampleParam_t();
}

void ParameterList::addParameter(string Name, sampleParam_t value)
{
	for (uint16_t i = 0; i < list.size(); i++)
	{
		if (list[i].Name == Name)
		{
			list[i].value = value;
			if (parent) parent->parameterChanged(Name);
			return;
		}
	}
	list.push_back(Parameter(Name, value));
	if (parent) parent->parameterChanged(Name);
}

void ParameterList::setParameter(string Name, sampleParam_t value)
{
	for (uint16_t i = 0; i < list.size(); i++)
	{
		if (list[i].Name == Name)
		{
			list[i].value = value;
			if (parent) parent->parameterChanged(Name);
			return;
		}
	}
	addParameter(Name, value);

}

bool ParameterList::operator==(ParameterList  rhs) const
{
	if (list.size() == 0 && rhs.list.size() == 0)
		return true;

	for (uint16_t i = 0; i < list.size(); i++)
	{
		if (rhs.getParameter(list[i].Name) != list[i].value)
			return false;
	}

	return true;
}

void ParameterList::clear()
{
	list.clear();
	parent = nullptr;
}
