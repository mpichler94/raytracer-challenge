#pragma once

#include <vector>

#include "math.h"
#include "color.h"


class Shape;
class Ray;
class World;
class Intersections;

struct Computations
{
	float t;
	const Shape* object;
	Tuple point;
	Tuple eyev;
	Tuple normal;
	bool inside;
	Tuple overPoint;
	Tuple reflectv;
	float n1;
	float n2;
	Tuple underPoint;

	Computations(float t, const Shape* object, const Ray& ray, const Tuple& normal, const Intersections& xs);

	Color shade(const World& w, unsigned int remaining) const;
	Color reflectedColor(const World& w, unsigned int remaining) const;
	Color refractedColor(const World& w, unsigned int remaining) const;
	float schlick() const;
};

class Intersection
{
public :
	float t;
	const Shape* primitive;

public:
	Intersection(float t, const Shape* primitive);

	Computations prepare(const Ray& ray) const;
	Computations prepare(const Ray& ray, const Intersections& xs) const;

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

	std::vector<Intersection>::iterator begin();
	std::vector<Intersection>::const_iterator begin() const;
	std::vector<Intersection>::iterator end();
	std::vector<Intersection>::const_iterator end() const;

	const Intersection& operator[](int i) const;
	Intersection& operator[](int i);

	Intersections& operator+=(const Intersections& rhs);
};