#include "tuple.h"
#include "math.h"
#include <format>

Tuple::Tuple(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

Tuple Tuple::point(float x, float y, float z)
{
	return Tuple(x, y, z, 1.f);
}

Tuple Tuple::color(float r, float g, float b)
{
	return Tuple(r, g, b, 1.f);
}

Tuple Tuple::vector(float x, float y, float z)
{
	return Tuple(x, y, z, 0.f);
}

bool Tuple::isPoint() const
{
	return areEqual(w, 1.f);
}

bool Tuple::isVector() const
{
	return areEqual(w, 0.f);
}

void Tuple::normalize()
{
	float len = length(*this);
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

Tuple Tuple::operator-() const
{
	return Tuple(-x, -y, -z, -w);
}

bool operator==(const Tuple& lhs, const Tuple& rhs)
{
	if (!areEqual(lhs.x, rhs.x) || !areEqual(lhs.y, rhs.y) || !areEqual(lhs.z, rhs.z) || !areEqual(lhs.w, rhs.w))
		return false;

	return true;
}

const Tuple operator+(const Tuple& lhs, const Tuple& rhs)
{
	return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

const Tuple operator-(const Tuple& lhs, const Tuple& rhs)
{
	return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

const Tuple operator*(const Tuple& lhs, const float f)
{
	return Tuple(lhs.x * f, lhs.y * f, lhs.z * f, lhs.w * f);
}

const Tuple operator/(const Tuple& lhs, const float f)
{
	return Tuple(lhs.x / f, lhs.y / f, lhs.z / f, lhs.w / f);
}

Tuple rcp(const Tuple& t)
{
	return Tuple(1.f / t.x, 1.f / t.y, 1.f / t.z, 1.f / t.w);
}

float length(const Tuple& t)
{
	return sqrtf(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

Tuple normalize(const Tuple& t)
{
	return t * (1.f / length(t));
}

float dot(const Tuple& lhs, const Tuple& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Tuple cross(const Tuple& a, const Tuple& b)
{
	return Tuple::vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

std::wstring ToString(const Tuple& tuple)
{
	return std::format(L"%s(%.5f, %.5f, %.5)f", tuple.isPoint() ? L"Point" : L"Tuple", tuple.x, tuple.y, tuple.z);
}

bool areEqual(const Tuple& lhs, const Tuple& rhs)
{
	return areEqual(lhs.x, rhs.x) && areEqual(lhs.y, rhs.y) && areEqual(lhs.z, rhs.z) && areEqual(lhs.w, rhs.w);
}

