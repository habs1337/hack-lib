#include "../includes/includes.h"


namespace g_cheat::math {

	float sqrt(float val) {
		long i;
		float x2, y;
		float threehalfs = 1.5F;

		x2 = val * 0.5F;
		y = val;
		i = *(long*)&y;                     // floating point bit level hacking [sic]
		i = 0x5f3759df - (i >> 1);             // Newton's approximation
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y)); // 1st iteration
		y = y * (threehalfs - (x2 * y * y)); // 2nd iteration
		y = y * (threehalfs - (x2 * y * y)); // 3rd iteration

		return 1 / y;
	}

	int TIME_TO_TICKS(float time, float interval) {
		return (int)(0.5f + time / interval);
	}

	float TICKS_TO_TIME(int ticks, float interval) {
		return interval * (float)(ticks);
	}

}