#include "color.h"
#include "math.h"
#include <format>

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

bool operator==(const Color& lhs, const Color& rhs)
{
	if (lhs.r != rhs.r || lhs.g != rhs.g || lhs.b != rhs.b)
		return false;

	return true;
}

const Color operator+(const Color& lhs, const Color& rhs)
{
	return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}

const Color operator-(const Color& lhs, const Color& rhs)
{
	return Color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
}

const Color operator*(const Color& lhs, const float f)
{
	return Color(lhs.r * f, lhs.g * f, lhs.b * f);
}

const Color operator/(const Color& lhs, const float f)
{
	return Color(lhs.r / f, lhs.g / f, lhs.b / f);
}


std::wstring ToString(const Color& c)
{
	return std::format(L"(%.5f, %.5f, %.5f)", c.r, c.g, c.b);
}

bool areEqual(const Color& lhs, const Color& rhs)
{
	return areEqual(lhs.r, rhs.r) && areEqual(lhs.g, rhs.g) && areEqual(lhs.b, rhs.b);
}

