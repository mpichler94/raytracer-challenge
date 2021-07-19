#include "intersection.h"

#include <algorithm>
#include <sstream>

#include "math.h"
#include "shape.h"
#include "ray.h"
#include "world.h"
#include "material.h"

Computations::Computations(float t, const Shape* object, const Ray& ray, const Tuple& normal)
	: t(t), object(object), point(ray.pos(t)), eyev(-ray.direction), normal(normal), inside(false)
{
	if (dot(normal, eyev) < 0.f)
	{
		inside = true;
		this->normal = -normal;
	}

	overPoint = point + this->normal * 1e-4f;
	reflectv = reflect(ray.direction, this->normal);
}

Color Computations::shade(const World& w, unsigned int remaining) const
{
	bool isShadowed = w.isShadowed(overPoint);
	auto surface = object->material.lighting(*object, w.light, overPoint, eyev, normal, isShadowed);
	auto reflected = reflectedColor(w, remaining);
	return surface + reflected;
}

Color Computations::reflectedColor(const World& w, unsigned int remaining) const
{
	if (object->material.reflective < EPSILON || remaining < 1)
		return Color(0);

	auto reflectRay = Ray(overPoint, reflectv);
	auto color = w.colorAt(reflectRay, remaining - 1);

	return color * object->material.reflective;
}

Intersection::Intersection(float t, const Shape* primitive)
	: t(t), primitive(primitive)
{
}

Computations Intersection::prepare(const Ray& ray) const
{
	return Computations(t, primitive, ray, primitive->normal(ray.pos(t)));
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
