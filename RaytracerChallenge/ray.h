#pragma once

#include "matrix.h"
#include "tuple.h"


class Ray
{
public:
	Tuple origin;
	Tuple direction;

public:
	Ray(const Tuple& origin, const Tuple& direction);

	Tuple pos(float t) const;
	Ray transform(const Matrix<4, 4>& transform) const;
};

