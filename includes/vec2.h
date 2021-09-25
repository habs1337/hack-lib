#pragma once

namespace g_cheat::sdk {


	class c_vec2 {
		float m_x, m_y;
	public:

		c_vec2();
		c_vec2(float x, float y);
		c_vec2(int x, int y);

		bool operator==(c_vec2 vec2);
		bool operator!=(c_vec2 vec2);

		bool operator>=(c_vec2 vec2);
		bool operator<=(c_vec2 vec2);

		c_vec2& operator=(c_vec2 vec2);
		c_vec2& operator-();

		c_vec2 operator+(c_vec2 vec2);
		c_vec2 operator-(c_vec2 vec2);
		c_vec2 operator*(c_vec2 vec2);
		c_vec2 operator/(c_vec2 vec2);


		c_vec2& operator+=(c_vec2 vec2);
		c_vec2& operator-=(c_vec2 vec2);
		c_vec2& operator*=(c_vec2 vec2);
		c_vec2& operator/=(c_vec2 vec2);
		c_vec2 operator>(c_vec2 vec2);
		c_vec2 operator<(c_vec2 vec2);


		c_vec2 operator+(float val);
		c_vec2 operator-(float val);
		c_vec2 operator*(float val);
		c_vec2 operator/(float val);


		c_vec2& operator+=(float val);
		c_vec2& operator-=(float val);
		c_vec2& operator*=(float val);
		c_vec2& operator/=(float val);

		float& get_x();
		float& get_y();

		c_vec2 get_positive();

		float get_dot(c_vec2& vec2);
		float get_dot(float val);


		float get_length_sqr();
		float length();

		c_vec2 angle_normalize();

		float dist_to(c_vec2& vec2);

	};

}