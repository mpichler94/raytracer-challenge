#pragma once

#include "color.h"

class Tuple;
class Pattern;
class Shape;
class Light;

class Material
{
public:
	Color color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
	Pattern* pattern;

public:
	Material();

	Color lighting(const Shape& object, const Light& light, const Tuple& pos, const Tuple& eye, const Tuple& normal, const bool inShadow) const;

	bool operator==(const Material& rhs) const;

	friend std::wstring ToString(const Material& m);
};

