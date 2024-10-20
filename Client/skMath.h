#pragma once
#include <cmath>

namespace sk::math
{
#define PI 3.141592f

	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		float x;
		float y;

		Vector2() : 
			x(0.0f), 
			y(0.0f)
		{

		}

		Vector2(float _x, float _y) :
			x(_x),
			y(_y)
		{

		}

		Vector2 operator -()
		{
			return Vector2(-x, -y);
		}

		Vector2 operator+(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}

		Vector2 operator-(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}
		Vector2 operator/(const float& value)
		{
			Vector2 temp;
			temp.x = x / value;
			temp.y = y / value;
			return temp;
		}

		Vector2 operator*(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x * other.x;
			temp.y = y * other.y;

			return temp;
		}

		Vector2 operator/(const Vector2& other)
		{
			Vector2 temp;
			temp.x = x / other.x;
			temp.y = y / other.y;

			return temp;
		}

		Vector2 operator*(const float& value)
		{
			Vector2 temp;
			temp.x = x * value;
			temp.y = y * value;
			return temp;
		}
		Vector2& operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}
		Vector2& operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}
		Vector2& operator *=(const float& value)
		{
			x *= value;
			y *= value;

			return *this;
		}

		bool operator ==(const Vector2& other)
		{
			return (x == other.x && y == other.y);
		}

		bool operator !=(const Vector2& other)
		{
			return (x != other.x && y != other.y);
		}


		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 normalize()	// 크기1 방향 벡터
		{
			float len = length();
			x /= len;
			y /= len;

			return *this;
		}
	};

	inline Vector2 Rotate(Vector2 vector, float degree)		// 회전
	{
		float radian = (degree / 180.f) * PI;
		vector.normalize();
		float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
		float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

		return Vector2(x, y);
	}
	inline float Dot(Vector2& v1, Vector2& v2) // 내적
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline float Cross(Vector2 v1, Vector2 v2) // 외적
	{
		return v1.x * v2.y - v1.y * v2.x;
	}


	//float lerp(float a, float b, float t)
	//{
	//	return a + t * (b - a);
	//}
}