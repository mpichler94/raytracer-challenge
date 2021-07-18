#pragma once

#include "color.h"
#include "tuple.h"

class Shape;


class Pattern
{
public:
	virtual Color colorAt(const Tuple& point) const = 0;
	virtual Color colorAt(const Shape& shape, const Tuple& point) const = 0;
};

class StripePattern : public Pattern
{
public:
	Color a;
	Color b;


	StripePattern(const Color& a, const Color& b);

	virtual Color colorAt(const Tuple& point) const override;
	virtual Color colorAt(const Shape& shape, const Tuple& point) const override;
};