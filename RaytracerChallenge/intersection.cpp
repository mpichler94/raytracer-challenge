#include "intersection.h"

#include <algorithm>
#include <sstream>

#include "math.h"
#include "shape.h"
#include "ray.h"



Intersection::Intersection(float t, const Shape* primitive)
	: t(t), primitive(primitive)
{
}

Computations Intersection::prepare(const Ray& ray) const
{
	return Computations(t, primitive, ray.pos(t), -ray.direction, primitive->normal(ray.pos(t)));
}

Intersection& Intersection::operator=(const Intersection& i)
{
	primitive = i.primitive;
	t = i.t;

	return *this;
}

bool operator==(const Intersection& lhs, const Intersection& rhs)
{
	return areEqual(lhs.t, rhs.t) && lhs.primitive == rhs.primitive;
}

std::wstring ToString(const Intersection& i)
{
	std::wstringstream ss;
	ss << "Intersection at " << i.t << " with " << i.primitive->toString();
	return ss.str();
}

std::wstring ToString(const Intersection* i)
{
	return ToString(*i);
}

Intersections::Intersections(std::initializer_list<Intersection> il)
	: intersections(il)
{
}

size_t Intersections::count() const
{
	return intersections.size();
}

const Intersection* Intersections::hit() const
{
	/*std::sort(intersections.begin(), intersections.end(), [](auto i1, auto i2) {return i1.t < i2.t; });

	for (auto i : intersections)
		if (i.t > 0) return i;
*/


	//std::optional<const Intersection&> ret = std::nullopt;
	const Intersection* ret = nullptr;
	for (auto& i : intersections)
	{
		if (i.t > 0 && (ret == nullptr || i.t < ret->t))
			ret = &i;
	}
	return ret;
}

const Intersection& Intersections::operator[](int i) const
{
	return intersections.at(i);
}

Intersection& Intersections::operator[](int i)
{
	return intersections.at(i);
}

Intersections& Intersections::operator+=(const Intersections& rhs)
{
	for (auto i : rhs.intersections)
		intersections.push_back(i);
	std::sort(intersections.begin(), intersections.end(), [](const auto& l, const auto& r) { return l.t < r.t; });
	return *this;
}
