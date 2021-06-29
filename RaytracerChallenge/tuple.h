#pragma once

#include <string>

class Tuple
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	Tuple() = default;
	Tuple(float x, float y, float z, float w);
	static Tuple point(float x, float y, float z);
	static Tuple vector(float x, float y, float z);
	static Tuple color(float r, float g, float b);

	bool isPoint() const;
	bool isVector() const;

	void normalize();

	Tuple operator-() const ;


	friend bool operator==(const Tuple& lhs, const Tuple& rhs);

	friend const Tuple operator+(const Tuple& lhs, const Tuple& rhs);
	friend const Tuple operator-(const Tuple& lhs, const Tuple& rhs);

	friend const Tuple operator*(const Tuple& lhs, const float f);
	friend const Tuple operator/(const Tuple& lhs, const float f);

	friend Tuple rcp(const Tuple& t);
	friend float length(const Tuple& t);
	friend Tuple normalize(const Tuple& t);
	friend float dot(const Tuple& lhs, const Tuple& rhs);
	friend Tuple cross(const Tuple& lhs, const Tuple& rhs);

	friend std::wstring ToString(const Tuple& tuple);

	friend bool areEqual(const Tuple& lhs, const Tuple& rhs);
};


