#pragma once

#include <vector>
#include "tuple.h"
#include "matrix.h"
#include "material.h"

class Ray;
class Intersections;

class Shape
{
public:
	Matrix<4, 4> transform;
	Material material;

public:
	Shape();
	Shape(const Shape& other) = default;

	virtual Intersections intersect(const Ray& r) const final;
	virtual Tuple normal(const Tuple& point) const final;

	virtual bool operator==(const Shape& rhs) const = 0;

	virtual std::wstring toString() const = 0;

	friend std::wstring ToString(const Shape& p);
	friend std::wstring ToString(const Shape* p);

private:
	virtual Intersections intersectIntenal(const Ray& r) const = 0;
	virtual Tuple normalInternal(const Tuple& point) const = 0;
};

class Sphere : public Shape
{
private:
	Tuple center;
	float radius;

public:
	Sphere();
	Sphere(const Sphere& other) = default;

	static Sphere glass();

	virtual bool operator==(const Shape& rhs) const override;

	virtual std::wstring toString() const;

	Sphere& operator=(const Sphere& other);

	friend std::wstring ToString(const Sphere& s);

private:
	virtual Intersections intersectIntenal(const Ray& r) const override;
	virtual Tuple normalInternal(const Tuple& point) const override;
};

class Plane : public Shape
{
private:


public:
	Plane();

	virtual bool operator==(const Shape& rhs) const override;

	virtual std::wstring toString() const;


private:
	virtual Intersections intersectIntenal(const Ray& r) const override;
	virtual Tuple normalInternal(const Tuple& point) const override;
};