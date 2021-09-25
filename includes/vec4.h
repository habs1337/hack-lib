#pragma once

namespace g_cheat {
	namespace sdk {

		class c_vec4 {
			float m_x, m_y, m_z, m_w;
		public:

			c_vec4();
			c_vec4(float x, float y, float z, float w);
			c_vec4(int x, int y, int z, float w);

			bool operator==(c_vec4 vec3);
			bool operator!=(c_vec4 vec3);

			bool operator>=(c_vec4 vec3);
			bool operator<=(c_vec4 vec3);

			c_vec4& operator=(c_vec4 vec3);
			c_vec4& operator-();

			c_vec4 operator+(c_vec4 vec3);
			c_vec4 operator-(c_vec4 vec3);
			c_vec4 operator*(c_vec4 vec3);
			c_vec4 operator/(c_vec4 vec3);


			c_vec4& operator+=(c_vec4 vec3);
			c_vec4& operator-=(c_vec4 vec3);
			c_vec4& operator*=(c_vec4 vec3);
			c_vec4& operator/=(c_vec4 vec3);
			c_vec4 operator>(c_vec4 vec3);
			c_vec4 operator<(c_vec4 vec3);


			c_vec4 operator+(float val);
			c_vec4 operator-(float val);
			c_vec4 operator*(float val);
			c_vec4 operator/(float val);


			c_vec4& operator+=(float val);
			c_vec4& operator-=(float val);
			c_vec4& operator*=(float val);
			c_vec4& operator/=(float val);

			float& get_x();
			float& get_y();
			float& get_z();
			float& get_w();

			c_vec4 get_positive();

			float get_dot(c_vec4 vec3);
			float get_dot(float val);

			float get_length_4d_sqr();
			float get_length_3d_sqr();
			float get_length_2d_sqr();
			float length_4d();
			float length_3d();
			float length_2d();

			c_vec4 angle_normalize();

			float vector_normalize();
			c_vec4 vector_normalized();


			float dist_to_4d(c_vec4 vec3);
			float dist_to_3d(c_vec4 vec3);
			float dist_to_2d(c_vec4 vec3);


		};
	}
}