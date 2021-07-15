#pragma once

#include "tuple.h"
#include "color.h"

class Light
{
public:
	Color intensity;
	Tuple position;

public:
	Light() = default;
	Light(const Tuple& position, const Color& intensity);

	virtual bool operator==(const Light& rhs) const;
};

class PointLight : public Light
{

public:
	PointLight(const Tuple& position, const Color& intensity);

	virtual bool operator==(const Light& rhs) const;

	friend std::wstring ToString(const PointLight& l);
};

