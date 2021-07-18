#pragma once

#include <vector>

#include "math.h"
#include "color.h"

class Shape;
class Ray;
class World;

struct Computations
{
	float t;
	const Shape* object;
	Tuple point;
	Tuple eyev;
	Tuple normal;
	bool inside;
	Tuple overPoint;

	Computations(float t, const Shape* object, const Tuple& point, const Tuple& eyev, const Tuple& normal)
		: t(t), object(object), point(point), eyev(eyev), normal(normal), inside(false)
	{
		if (dot(normal, eyev) < 0.f)
		{
			inside = true;
			this->normal = -normal;
		}

		overPoint = point + this->normal * 1e-1f;
	}

	Color shade(const World& w) const;
};

class Intersection
{
public :
	float t;
	const Shape* primitive;

public:
	Intersection(float t, const Shape* primitive);

	Computations prepare(const Ray& ray) const;

	Intersection& operator=(const Intersection& i);

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

	Intersections& operator+=(const Intersections& rhs);
};