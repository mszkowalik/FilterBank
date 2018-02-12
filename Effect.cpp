#include "Effect.h"
#include "Delay.h"
#include "FShift.h"


Effect::Effect(FilterSettings _settings, Effect* _child)
{ 
	settings = _settings;
	child = _child;
}

Effect::Effect(Effect * _effect)
{
}


Effect::~Effect()
{
	if (child)
		delete child;
}

ParameterList Effect::getParamsList()
{
	return ParamsList;
}

Effect * Effect::lastChild(Effect * parent)
{
	Effect* ret = parent;
	while (ret)
	{
		if (ret->child)
			ret = ret->child;
		else return ret;
	}
	return nullptr; // never gona reach this point if parent exists
}
void Effect::setParameter(string Name, sampleInter_t value)
{
	ParamsList.setParameter(Name, value);
}
void Effect::setParamsList(ParameterList _list)
{
	ParamsList = _list ;

}
Effect * Effect::EffectFactory(ParameterList params, Effects type, FilterSettings settings)
{
	Effect* ret = nullptr;
	switch (type)
	{
	case Effects::Effect_Delay:
		ret = new Delay(settings, nullptr, params);
		break;
	case Effects::Effect_FShift:
		ret = new FShift(settings, nullptr, params);
		break;
	default:
		break;
	}

	return ret;
}