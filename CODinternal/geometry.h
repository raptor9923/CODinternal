#pragma once
#include<math.h>
struct Vec3
{
	float x, y, z;
	Vec3(float a, float b, float c) :
		x(a),y(b),z(c){}
	Vec3()
	{
		x = y = z = 0;
	}
	friend Vec3 operator +(const Vec3& vec1, const Vec3& vec2)
	{
		return { vec1.x + vec2.x,vec1.y + vec2.y,vec1.z + vec2.z };
	}
	friend Vec3 operator -(const Vec3& vec1, const Vec3& vec2)
	{
		return { vec1.x - vec2.x,vec1.y - vec2.y,vec1.z - vec2.z };
	}

};

float Distance(const Vec3& a,const Vec3& b);
float DotProduct(const Vec3& a, const Vec3& b);