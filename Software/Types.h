#pragma once
#ifndef _TYPES
#define _TYPES

#include <stdint.h>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <queue>
#include "CircularBuffer.h"

using namespace std;

typedef uint16_t sampleIn_t;
typedef uint16_t sampleOut_t;
typedef double sampleParam_t;

#define INTER_T(x) ((sampleInter_t)(x))
#define PARAM_T(x) ((sampleParam_t)(x))

typedef double sampleInter_t; // only floating point - because of FFT algorithm
const sampleInter_t _PI = INTER_T(3.14159265358979323846);
enum Effects
{
	Effect_Delay,
	Effect_FShift,
	Effect_Resample,
	Effect_End
};

#endif