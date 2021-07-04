#pragma once

#include <optional>
#include <vector>

#include "primitive.h"

class Intersection
{
public :
	float t;
	const Primitive& primitive;

public:
	Intersection(float t, const Primitive& primitive);

	friend bool operator==(const Intersection& lhs, const Intersection& rhs);

	friend std::wstring ToString(const Intersection& i);
	friend std::wstring ToString(const Intersection* i);
};

class Intersections
{
private:
	std::vector<Intersection> intersections;
public:
	Intersections() = default;
	Intersections(std::initializer_list<Intersection> il);

	size_t count() const;
	const Intersection* hit() const;

	const Intersection& operator[](int i) const;
	Intersection& operator[](int i);
};