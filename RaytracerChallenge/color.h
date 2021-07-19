#pragma once

#include <string>

class Color
{
public:
	float r;
	float g;
	float b;

public:
	Color() = default;
	Color(float r, float g, float b);
	Color(float gray);

	Color& operator=(const Color& c);

	friend bool operator==(const Color& lhs, const Color& rhs);

	friend const Color operator+(const Color& a, const Color& b);
	friend const Color operator-(const Color& a, const Color& b);

	friend const Color operator*(const Color& a, const Color& b);
	friend const Color operator*(const Color& c, const float f);

	friend std::wstring ToString(const Color& c);

	friend bool areEqual(const Color& a, const Color& b);
};


