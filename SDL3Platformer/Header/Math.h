#pragma once
#include <cmath>

#define PI 3.141592

typedef struct Vector2
{
	float x;
	float y;

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2 operator+(Vector2& other)
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 operator-(Vector2& other)
	{
		return Vector2(this->x - other.x, this->y - other.y);
	}

	Vector2 operator*(float scalar)
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	Vector2 operator/(float scalar)
	{
		return Vector2(this->x / scalar, this->y / scalar);
	}

	Vector2 operator*(Vector2& other)
	{
		return Vector2(this->x * other.x, this->y * other.y);
	}

	Vector2 operator/(Vector2& other)
	{
		return Vector2(this->x / other.x, this->y / other.y);
	}

	Vector2 operator+(float scalar)
	{
		return Vector2(this->x + scalar, this->y + scalar);
	}

	Vector2 operator-(float scalar)
	{
		return Vector2(this->x - scalar, this->y - scalar);
	}

	Vector2 operator*(float scalar) const
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	Vector2 operator/(float scalar) const
	{
		return Vector2(this->x / scalar, this->y / scalar);
	}




} Vec2;

typedef struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{

	}

	Vector3 operator+(Vector3& other)
	{
		return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3 operator-(Vector3& other)
	{
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3 operator*(float scalar)
	{
		return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
	}


	Vector3 operator/(float scalar)
	{
		return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
	}

	Vector3 operator*(Vector3& other)
	{
		return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
	}

	Vector3 operator/(Vector3& other)
	{
		return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
	}


} Vec3;

typedef struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4(float x, float y, float z, float w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{

	}

	Vector4 operator+(Vector4& other)
	{
		return Vector4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
	}

	Vector4 operator-(Vector4& other)
	{
		return Vector4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
	}

	Vector4 operator*(float scalar)
	{
		return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}

	Vector4 operator/(float scalar)
	{
		return Vector4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
	}

	Vector4 operator*(Vector4& other)
	{
		return Vector4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
	}

	Vector4 operator/(Vector4& other)
	{
		return Vector4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
	}

	Vector4 operator+(float scalar)
	{
		return Vector4(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
	}

	Vector4 operator-(float scalar)
	{
		return Vector4(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
	}

	Vector4 operator*(float scalar) const
	{
		return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}

	Vector4 operator/(float scalar) const
	{
		return Vector4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
	}



	

} Vec4;


inline float toRadians(float degrees)
{
	return degrees * (PI / 180.0f);
}

inline float toDegrees(float radians)
{
	return radians * (180.0f / PI);
}

inline float length(Vec2 v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

inline float length(Vec3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float length(Vec4 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

inline Vec2 normalize(Vec2 v)
{
	float len = length(v);
	if (len == 0) return Vec2(0, 0);
	return Vec2(v.x / len, v.y / len);
}

inline Vec3 normalize(Vec3 v)
{
	float len = length(v);
	if (len == 0) return Vec3(0, 0, 0);
	return Vec3(v.x / len, v.y / len, v.z / len);
}

inline Vec4 normalize(Vec4 v)
{
	float len = length(v);
	if (len == 0) return Vec4(0, 0, 0, 0);
	return Vec4(v.x / len, v.y / len, v.z / len, v.w / len);
}

inline float dot(Vec2 a, Vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

inline float dot(Vec3 a, Vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float dot(Vec4 a, Vec4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vec2 cross(Vec2 a, Vec2 b)
{
	return Vec2(a.x * b.y - a.y * b.x, 0);
}

inline Vec3 cross(Vec3 a, Vec3 b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vec2 lerp(Vec2 a, Vec2 b, float t)
{
	return Vec2(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}

inline Vec3 lerp(Vec3 a, Vec3 b, float t)
{
	return Vec3(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z));
}

inline Vec4 lerp(Vec4 a, Vec4 b, float t)
{
	return Vec4(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y), a.z + t * (b.z - a.z), a.w + t * (b.w - a.w));
}

