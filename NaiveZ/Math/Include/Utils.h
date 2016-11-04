#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace NaiveZ3D
{
	const float EPSILON = 0.0001f;
	const float PI = M_PI;

	inline bool FloatEqual(float a, float b) 
	{
		return fabs(a - b) < EPSILON;
	}

	inline float AngleToRadian(float angle)
	{
		return angle * PI / 180.0f;
	}

	inline float RadianToAngle(float radian)
	{
		return 180.0f * radian / PI;
	}
}