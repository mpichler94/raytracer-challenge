#include "pattern.h"

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

Color StripePattern::colorAt(const Shape& shape, const Tuple& point) const
{
	return Color();
}
