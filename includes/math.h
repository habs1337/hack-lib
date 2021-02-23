#pragma once

#define FLT_EPSILON 1.192092896e-07F

namespace g_cheat::math {

	float sqrt(float val);

	int TIME_TO_TICKS(float time, float interval);
	float TICKS_TO_TIME(int ticks, float interval);

}