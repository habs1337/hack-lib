#pragma once

namespace g_cheat::sdk {	

		class c_vec3 {
			float m_x, m_y, m_z;
		public:

			c_vec3();
			c_vec3(float x, float y, float z);
			c_vec3(int x, int y, int z);

			bool operator==(c_vec3 vec3);
			bool operator!=(c_vec3 vec3);

			bool operator>=(c_vec3 vec3);
			bool operator<=(c_vec3 vec3);

			c_vec3& operator=(c_vec3 vec3);
			c_vec3& operator-();

			c_vec3 operator+(c_vec3 vec3);
			c_vec3 operator-(c_vec3 vec3);
			c_vec3 operator*(c_vec3 vec3);
			c_vec3 operator/(c_vec3 vec3);


			c_vec3& operator+=(c_vec3 vec3);
			c_vec3& operator-=(c_vec3 vec3);
			c_vec3& operator*=(c_vec3 vec3);
			c_vec3& operator/=(c_vec3 vec3);
			c_vec3 operator>(c_vec3 vec3);
			c_vec3 operator<(c_vec3 vec3);


			c_vec3 operator+(float val);
			c_vec3 operator-(float val);
			c_vec3 operator*(float val);
			c_vec3 operator/(float val);


			c_vec3& operator+=(float val);
			c_vec3& operator-=(float val);
			c_vec3& operator*=(float val);
			c_vec3& operator/=(float val);

			float& get_x();
			float& get_y();
			float& get_z();

			c_vec3 get_positive();

			float get_dot(c_vec3 vec3);
			float get_dot(float val);

			c_vec3 get_cross(c_vec3 vec3);
			c_vec3 get_cross(float val);

			float get_length_3d_sqr();
			float get_length_2d_sqr();
			float length_3d();
			float length_2d();

			c_vec3 angle_normalize();

			float vector_normalize();
			c_vec3 vector_normalized();


			float dist_to_3d(c_vec3 vec3);
			float dist_to_2d(c_vec3 vec3);

			c_vec3 matrix_mutliply(g_cheat::sdk::c_matrix4x4 matrix);
			

		};
	
}