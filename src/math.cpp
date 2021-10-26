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

	int time_to_ticks(float time, float interval) {
		return (int)(0.5f + time / interval);
	}

	float ticks_to_time(int ticks, float interval) {
		return interval * (float)(ticks);
	}

	float rad_to_deg(float value) {
		return value * (180.f / M_PI);
	}

	float deg_to_rad(float value) {
		return value * (M_PI / 180.f);
	}

	template<typename T>
	inline T my_abs(T t) {
		return t > 0 ? t : -t;
	}

	float my_atan2(const float y, const float x) {
		if (x == 0.0f) {
			if (y > 0.0f) return M_HALF_PI;
			if (y == 0.0f) return 0.0f;
			return -M_HALF_PI;
		}
		float atan;
		float z = y / x;
		if (my_abs<float>(z) < 1.0f) {
			atan = z / (1.0f + 0.28f * z * z);
			if (x < 0.0f) {
				if (y < 0.0f) return atan - M_PI;
				return atan + M_PI;
			}
		}
		else {
			atan = M_HALF_PI - z / (z * z + 0.28f);
			if (y < 0.0f) return atan - M_PI;
		}
		return atan;
	}


	void vector_angles(g_cheat::sdk::c_vec2 forward, g_cheat::sdk::c_vec2& angles) {
		if (forward.get_y() == 0.0f && forward.get_x() == 0.0f) {
			angles.get_x() = 90.0f;
			angles.get_y() = 0.0f;
		}
		else {
			angles.get_x() = my_atan2(0.f, sqrt(forward.get_x() * forward.get_x() + forward.get_y() + forward.get_y())) * -180.f / M_PI;
			angles.get_y() = my_atan2(forward.get_y(), forward.get_x()) * 180.f / M_PI;

			if (angles.get_y() > 90)
				angles.get_y() -= 180;
			else if (angles.get_y() < 90)
				angles.get_y() += 180;
			else if (angles.get_y() == 90)
				angles.get_y() = 0;
		}
	}

}