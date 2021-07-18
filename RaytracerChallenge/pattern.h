#pragma once

#include "math.h"
#include "matrix.h"
#include "color.h"
#include "tuple.h"

class Shape;

// TODO: UV mapping
// for spheres: query "spherical texture mapping"

// TODO: more patterns:
//		 Radial gradient pattern
//		 Nested patterns
//		 Blended patterns
//		 Perturbed patterns
class Pattern
{
public:
	Matrix<4, 4> transform;

	Pattern();

	virtual Color colorAt(const Tuple& point) const = 0;
	virtual Color colorAtShape(const Shape& shape, const Tuple& point) const final;
};

class StripePattern : public Pattern
{
public:
	Color a;
	Color b;


	StripePattern(const Color& a, const Color& b);

	virtual Color colorAt(const Tuple& point) const override;
};

class GradientPattern : public Pattern
{
public:
	Color a;
	Color b;

	GradientPattern(const Color& a, const Color& b);

	virtual Color colorAt(const Tuple& point) const override;
};

class RingPattern : public Pattern
{
public:
	Color a;
	Color b;

	RingPattern(const Color& a, const Color& b);

	virtual Color colorAt(const Tuple& point) const override;
};

class CheckersPattern : public Pattern
{
public:
	Color a;
	Color b;

	CheckersPattern(const Color& a, const Color& b);

	virtual Color colorAt(const Tuple& point) const override;
};

