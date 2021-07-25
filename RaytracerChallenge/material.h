#pragma once

#include "color.h"

class Tuple;
class Pattern;
class Shape;
class Light;

class Material
{
public:
	float ambient;
	float diffuse;
	float specular;
	float shininess;
	float reflective;
	float transparency;
	float refractiveIndex;
	Color color;
	Pattern* pattern;


public:
	Material();

	Color lighting(const Shape& object, const Light& light, const Tuple& pos, const Tuple& eye, const Tuple& normal, const bool inShadow) const;

	bool operator==(const Material& rhs) const;

	friend std::wstring ToString(const Material& m);
};

