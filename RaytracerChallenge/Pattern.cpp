#include "pattern.h"

#include "shape.h"

Pattern::Pattern()
	: transform(Matrix<4, 4>::identity())
{
}

Color Pattern::colorAtShape(const Shape& shape, const Tuple& point) const
{
	auto objectPoint = inverse(shape.transform) * point;
	auto patternPoint = inverse(transform) * objectPoint;

	return colorAt(patternPoint);
}

StripePattern::StripePattern(const Color& a, const Color& b)
	: a(a), b(b)
{
}

Color StripePattern::colorAt(const Tuple& point) const
{
	if ((int)floorf(point.x) % 2 == 0)
		return a;
	return b;
}

GradientPattern::GradientPattern(const Color& a, const Color& b)
	: a(a), b(b)
{
}

Color GradientPattern::colorAt(const Tuple& point) const
{
	return a + (b - a) * (point.x - floorf(point.x));
}

RingPattern::RingPattern(const Color& a, const Color& b)
	: a(a), b(b)
{
}

Color RingPattern::colorAt(const Tuple& point) const
{
	if ((int) floorf(sqrtf(point.x * point.x + point.z * point.z)) % 2 < EPSILON)
		return a;
	return b;
}

CheckersPattern::CheckersPattern(const Color& a, const Color& b)
	: a(a), b(b)
{
}

Color CheckersPattern::colorAt(const Tuple& point) const
{
	if ((int)(floorf(point.x) + floorf(point.y) + floorf(point.z)) % 2 == 0)
		return a;
	return b;
}
