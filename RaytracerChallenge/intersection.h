#pragma once

#include <optional>
#include <vector>

#include "primitive.h"
#include "world.h"

struct Computations
{
	float t;
	const Primitive* object;
	Tuple point;
	Tuple eyev;
	Tuple normal;
	bool inside;

	Computations(float t, const Primitive* object, const Tuple& point, const Tuple& eyev, const Tuple& normal)
		: t(t), object(object), point(point), eyev(eyev), normal(normal), inside(false)
	{
		if (dot(normal, eyev) < 0)
		{
			inside = true;
			this->normal = -normal;
		}
	}

	Color shade(const World& w) const
	{
		return object->material.lighting(w.light, point, eyev, normal);
	}
};

class Intersection
{
public :
	float t;
	const Primitive* primitive;

public:
	Intersection(float t, const Primitive* primitive);

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