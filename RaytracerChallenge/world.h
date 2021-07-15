#pragma once

#include <vector>
#include <memory>
#include "light.h"
#include "primitive.h"

class World
{
private:
	std::vector<Primitive*> objects;

public:
	Light light;


public:
	World();

	static World Default();

	void dispose();

	size_t getObjectCount() const;
	bool contains(const Primitive& p) const;
	void addObject(Primitive* p);
	Primitive* getObject(size_t index);
	Intersections intersect(const Ray& ray) const;

	Color colorAt(const Ray& r) const;
};

