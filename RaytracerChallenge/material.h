#pragma once

#include "color.h"
#include "light.h"

class Pattern;

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

	Color lighting(const Light& light, const Tuple& pos, const Tuple& eye, const Tuple& normal, const bool inShadow) const;

	bool operator==(const Material& rhs) const;

	friend std::wstring ToString(const Material& m);
};

