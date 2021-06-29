#include "color.h"
#include "math.h"
#include <sstream>
#include <iomanip>

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

Color& Color::operator=(const Color& c)
{
	r = c.r;
	g = c.g;
	b = c.b;

	return *this;
}

bool operator==(const Color& lhs, const Color& rhs)
{
	if (!areEqual(lhs.r, rhs.r) || !areEqual(lhs.g, rhs.g) || !areEqual(lhs.b, rhs.b))
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

const Color operator*(const Color& a, const Color& b)
{
	return Color(a.r * b.r, a.g * b.g, a.b * b.b);
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
	std::wstringstream ss;
	ss << std::fixed << std::setprecision(5) << "("<< c.r << ", " << c.g << ", " << c.b << ")";
	return ss.str();
}

bool areEqual(const Color& lhs, const Color& rhs)
{
	return areEqual(lhs.r, rhs.r) && areEqual(lhs.g, rhs.g) && areEqual(lhs.b, rhs.b);
}

