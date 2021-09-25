#pragma once


namespace g_cheat::math {

	float sqrt(float val);

	int time_to_ticks(float time, float interval);
	float ticks_to_time(int ticks, float interval);

	float rad_to_deg(float value);
	float deg_to_rad(float value);
	
	void vector_angles(sdk::c_vec2 forward, sdk::c_vec2& angles);
}