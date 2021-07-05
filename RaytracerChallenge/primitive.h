#pragma once

#include <vector>
#include "tuple.h"
#include "matrix.h"
#include "material.h"

class Ray;
class Intersections;

class Primitive
{
public:
	Matrix<4, 4> transform;
	Material material;

public:
	Primitive();

	virtual Intersections intersect(const Ray& r) const = 0;
	virtual Tuple normal(const Tuple& point) const = 0;

	virtual bool operator==(const Primitive& rhs) const = 0;

	virtual std::wstring toString() const = 0;
};

class Sphere : public Primitive
{
private:
	Tuple center;
	float radius;

public:
	Sphere();

	virtual Intersections intersect(const Ray& r) const override;
	virtual Tuple normal(const Tuple& point) const override;

	virtual bool operator==(const Primitive& rhs) const override;

	virtual std::wstring toString() const;

	//friend bool operator==(const Sphere& lhs, const Sphere& rhs);

	friend std::wstring ToString(const Primitive& s);
	friend std::wstring ToString(const Sphere& s);
};

