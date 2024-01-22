#include"geometry.h"

float Distance(const Vec3& a, const Vec3& b)
{
	Vec3 temp;
	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	temp.x *= temp.x;
	temp.y *= temp.y;
	temp.z *= temp.z;
	float len = temp.x + temp.y + temp.z;
	len = sqrtf(len);
	return len;
}
float DotProduct(const Vec3& a, const Vec3& b)
{
	return a.x * b.x+a.y * b.y + a.z * b.z;
}