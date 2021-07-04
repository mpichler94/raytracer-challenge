#include "ray.h"

Ray::Ray(const Tuple& origin, const Tuple& direction)
	: origin(origin), direction(direction)
{
}

Tuple Ray::pos(float t) const
{
	return origin + direction * t;
}

Ray Ray::transform(const Matrix<4, 4>& transform) const
{
	return Ray(transform * origin, transform * direction);
}
