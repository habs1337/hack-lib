#include "../includes/includes.h"

namespace g_cheat::sdk {
	bool c_world_to_screen::on_work(g_cheat::sdk::c_vec3 point, g_cheat::sdk::c_vec3& screen, g_cheat::sdk::c_vec2 screen_size, g_cheat::sdk::c_matrix4x4 matrix) {
		bool screen_transform_result = screen_transform(point, screen, matrix);

		float x = screen_size.get_x() / 2.f;
		float y = screen_size.get_y() / 2.f;

		x += 0.5f * screen.get_x() * screen_size.get_x() + 0.5f;
		y -= 0.5f * screen.get_y() * screen_size.get_y() + 0.5f;

		screen.get_x() = x;
		screen.get_y() = y;

		if (screen.get_x() > screen_size.get_x() || screen.get_x() < 0.f ||
			screen.get_y() > screen_size.get_y() || screen.get_y() < 0.f ||
			screen_transform_result) {

			offscreen_point(screen, screen_size.get_x(),
				screen_size.get_y(), screen_size.get_y());

			return false;
		}

		return true;
	}

	bool c_world_to_screen::screen_transform(g_cheat::sdk::c_vec3 point, g_cheat::sdk::c_vec3& screen, g_cheat::sdk::c_matrix4x4 matrix) {
		screen.get_x() = matrix[0][0] * point.get_x() + matrix[0][1] *
			point.get_y() + matrix[0][2] * point.get_z() + matrix[0][3];

		screen.get_y() = matrix[1][0] * point.get_x() + matrix[1][1] *
			point.get_y() + matrix[1][2] * point.get_z() + matrix[1][3];

		screen.get_z() = 0.0f;

		auto w = matrix[3][0] * point.get_x() + matrix[3][1] *
			point.get_y() + matrix[3][2] * point.get_z() + matrix[3][3];

		bool result = w < 0.001f;
		auto mul = result ? -1.f : 1.f;

		screen.get_x() *= mul / w;
		screen.get_y() *= mul / w;

		return result;
	}


	void c_world_to_screen::offscreen_point(g_cheat::sdk::c_vec3& screen, float screen_size_x, float screen_size_y, float degrees) {
		float x2 = screen_size_x / 2.f;
		float y2 = screen_size_y / 2.f;

		float d = sqrtf(powf((screen.get_x() - x2), 2.f)
			+ (powf((screen.get_y() - y2), 2.f)));

		float r = /*degrees /*/ d;

		screen.get_x() = r * screen.get_x() + (1.f - r) * x2;
		screen.get_y() = r * screen.get_y() + (1.f - r) * y2;
	}
	
	c_world_to_screen::points_t c_world_to_screen::on_offscreen(g_cheat::sdk::c_vec3 screen_point, g_cheat::sdk::c_color color, g_cheat::sdk::c_vec2 screen_size) {

		auto points = points_t();

		const auto screen_center_x = screen_size.get_x() / 2.f;
		const auto screen_center_y = screen_size.get_y() / 2.f;

		auto angle = g_cheat::sdk::c_vec2();
		
		g_cheat::math::vector_angles(g_cheat::sdk::c_vec2(screen_center_x - screen_point.get_x(), screen_center_y - screen_point.get_y()), angle);

		const auto angle_yaw_rad = g_cheat::math::deg_to_rad(angle.get_y());

		auto range = 400.f;

		const auto new_point_x = screen_center_x +
			range * cosf(angle_yaw_rad);
		const auto new_point_y = screen_center_y +
			range * sinf(angle_yaw_rad);

		const auto x_size = 8.f;
		const auto y_size = 16.f;
		const auto outline_size = 2.f;

		points.points_outline[0] = g_cheat::sdk::c_vec2(new_point_x - x_size - outline_size, new_point_y - x_size - outline_size);
		points.points_outline[1] = g_cheat::sdk::c_vec2(new_point_x + y_size + outline_size, new_point_y);
		points.points_outline[2] = g_cheat::sdk::c_vec2(new_point_x - x_size - outline_size, new_point_y + x_size + outline_size);

		rotate_triangle(points.points_outline, angle.get_y());

		points.end_points[0] = g_cheat::sdk::c_vec2(new_point_x - x_size, new_point_y - x_size);
		points.end_points[1] = g_cheat::sdk::c_vec2(new_point_x + y_size, new_point_y);
		points.end_points[2] = g_cheat::sdk::c_vec2(new_point_x - x_size, new_point_y + x_size);

		rotate_triangle(points.end_points, angle.get_y());

		return points;
	}

	void c_world_to_screen::rotate_triangle(g_cheat::sdk::c_vec2* points, float rotation) {
		g_cheat::sdk::c_vec2 points_center;

		for (int i = 0; i < 3; i++) {
			points_center = g_cheat::sdk::c_vec2(points_center.get_x() + points[i].get_x(), points_center.get_y() + points[i].get_y());
		}

		points_center = g_cheat::sdk::c_vec2(points_center.get_x() / 3.f, points_center.get_y() / 3.f);

		for (int i = 0; i < 3; i++) {
			points[i] = g_cheat::sdk::c_vec2(points[i].get_x() - points_center.get_x(), points[i].get_y() - points_center.get_y());

			const auto temp_x = points[i].get_x();
			const auto temp_y = points[i].get_y();

			const auto theta = g_cheat::math::deg_to_rad(rotation);
			const auto c = cosf(theta);
			const auto s = sinf(theta);

			points[i].get_x() = temp_x * c - temp_y * s;
			points[i].get_y() = temp_x * s + temp_y * c;

			points[i] = g_cheat::sdk::c_vec2(points[i].get_x() + points_center.get_x(), points[i].get_y() + points_center.get_y());
		}
	}
}