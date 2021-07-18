#pragma once

#include <vector>
#include <memory>

#include "light.h"
#include "intersection.h"

class Shape;

class World
{
private:
	std::vector<Shape*> objects;

public:
	Light light;


public:
	World();

	static World Default();

	void dispose();

	size_t getObjectCount() const;
	bool contains(const Shape& p) const;
	void addObject(Shape* p);
	Shape* getObject(size_t index);
	Intersections intersect(const Ray& ray) const;

	Color colorAt(const Ray& r) const;

	bool isShadowed(const Tuple& point) const;
};

