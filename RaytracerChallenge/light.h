#pragma once

#include "tuple.h"
#include "color.h"

class Light
{
public:
	Color intensity;
	Tuple position;

public:
	Light(const Tuple& position, const Color& intensity);
};

class PointLight : public Light
{

public:
	PointLight(const Tuple& position, const Color& intensity);
};

