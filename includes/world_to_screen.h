#pragma once


namespace g_cheat::sdk {
	
	class c_world_to_screen {

		struct points_t {
			g_cheat::sdk::c_vec2 points_outline[3];
			g_cheat::sdk::c_vec2 end_points[3];
		};

		static bool screen_transform(g_cheat::sdk::c_vec3 point, g_cheat::sdk::c_vec3& screen, g_cheat::sdk::c_matrix4x4 matrix);
		static void offscreen_point(g_cheat::sdk::c_vec3& screen, float screen_size_x, float screen_size_y, float degrees);
		static void rotate_triangle(g_cheat::sdk::c_vec2* points, float rotation);
		
	public:

		static bool on_work(g_cheat::sdk::c_vec3 point, g_cheat::sdk::c_vec3& screen, g_cheat::sdk::c_vec2 screen_size, g_cheat::sdk::c_matrix4x4 matrix);

		static points_t on_offscreen(g_cheat::sdk::c_vec3 screen_point, g_cheat::sdk::c_color color, g_cheat::sdk::c_vec2 screen_size);
	};
}