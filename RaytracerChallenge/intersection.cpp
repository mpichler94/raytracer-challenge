#include "intersection.h"

#include <algorithm>
#include <sstream>

#include "math.h"
#include "shape.h"
#include "ray.h"
#include "world.h"
#include "material.h"

Computations::Computations(float t, const Shape* object, const Ray& ray, const Tuple& normal, const Intersections& xs)
	: t(t), object(object), point(ray.pos(t)), eyev(-ray.direction), normal(normal), inside(false), n1(1.f), n2(1.f)
{
	if (dot(normal, eyev) < 0.f)
	{
		inside = true;
		this->normal = -normal;
	}

	overPoint = point + this->normal * EPSILON;
	reflectv = reflect(ray.direction, this->normal);
	underPoint = point - this->normal * EPSILON;
}

Color Computations::shade(const World& w, unsigned int remaining) const
{
	bool isShadowed = w.isShadowed(overPoint);

	auto surface = object->material.lighting(*object, w.light, overPoint, eyev, normal, isShadowed);

	auto reflected = reflectedColor(w, remaining);
	auto refracted = refractedColor(w, remaining);

	if (object->material.reflective > 0.f && object->material.transparency > 0.f)
	{
		auto reflectance = schlick();
		return surface + reflected * reflectance + refracted * (1.f - reflectance);
	}

	return surface + reflected + refracted;
}

Color Computations::reflectedColor(const World& w, unsigned int remaining) const
{
	if (object->material.reflective < EPSILON || remaining < 1)
		return Color(0);

	auto reflectRay = Ray(overPoint, reflectv);
	auto color = w.colorAt(reflectRay, remaining - 1);

	return color * object->material.reflective;
}

Color Computations::refractedColor(const World& w, unsigned int remaining) const
{
	if (object->material.transparency < EPSILON || remaining < 1)
		return Color(0);

	auto nRatio = n1 / n2;
	auto cosi = dot(eyev, normal);
	auto sin2t = nRatio * nRatio * (1.f - cosi * cosi);
	if (sin2t > 1.f) // total internal reflection
		return Color(0);

	auto cost = sqrtf(1.f - sin2t);
	auto direction = normal * (nRatio * cosi - cost) - eyev * nRatio;
	auto refractRay = Ray(underPoint, direction);

	return w.colorAt(refractRay, remaining - 1) * object->material.transparency;

}

float Computations::schlick() const
{
	auto cos = dot(eyev, normal);

	if (n1 > n2)	// total internal reflection can occur
	{
		auto n = n1 / n2;
		auto sin2t = n * n * (1.f - cos * cos);
		if (sin2t > 1.f)
			return 1.f;

		auto cost = sqrtf(1.f - sin2t);

		cos = cost;
	}

	auto r0 = ((n1 - n2) / (n1 + n2)) * ((n1 - n2) / (n1 + n2));

	return r0 + (1.f - r0) * powf(1.f - cos, 5);
}

Intersection::Intersection(float t, const Shape* primitive)
	: t(t), primitive(primitive)
{
}

Computations Intersection::prepare(const Ray& ray) const
{
	return prepare(ray, Intersections{ *this });
}

Computations Intersection::prepare(const Ray& ray, const Intersections& xs) const
{
	Computations comps(t, primitive, ray, primitive->normal(ray.pos(t)), xs);
	std::vector<const Shape*> containers;

	for (const auto& i : xs)
	{
		if (i == *this)
		{
			if (containers.empty())
			{
				comps.n1 = 1.f;
			}
			else
			{
				comps.n1 = containers.back()->material.refractiveIndex;
			}
		}

		auto it = containers.end();
		if ((it = std::find(containers.begin(), containers.end(), i.primitive)) != containers.end())
			containers.erase(it);
		else
			containers.push_back(i.primitive);

		if (i == *this)
		{
			if (containers.empty())
			{
				comps.n2 = 1.f;
			}
			else
			{
				comps.n2 = containers.back()->material.refractiveIndex;
			}
			break;
		}
	}

	return comps;
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
	const Intersection* ret = nullptr;
	for (auto& i : intersections)
	{
		if (i.t > 0 && (ret == nullptr || i.t < ret->t))
			ret = &i;
	}
	return ret;
}

std::vector<Intersection>::iterator Intersections::begin()
{
	return intersections.begin();
}

std::vector<Intersection>::const_iterator Intersections::begin() const
{
	return intersections.begin();
}

std::vector<Intersection>::iterator Intersections::end()
{
	return intersections.end();
}

std::vector<Intersection>::const_iterator Intersections::end() const
{
	return intersections.end();
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
