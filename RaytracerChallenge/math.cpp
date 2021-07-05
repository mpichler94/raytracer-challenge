#include "math.h"
#include <cmath>

bool areEqual(float a, float b, float epsilon)
{
	return (fabs(a - b) <= epsilon);
}

Matrix<4, 4> translation(float x, float y, float z)
{
	return Matrix<4, 4>(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}

Matrix<4, 4> scaling(float x, float y, float z)
{
	return Matrix<4, 4>(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
}

Matrix<4, 4> rotationX(float r)
{
	return Matrix<4, 4>(1, 0, 0, 0, 0, cosf(r), -sinf(r), 0, 0, sinf(r), cosf(r), 0, 0, 0, 0, 1);
}

Matrix<4, 4> rotationY(float r)
{
	return Matrix<4, 4>(cosf(r), 0, sinf(r), 0, 0, 1, 0, 0, -sinf(r), 0, cosf(r), 0, 0, 0, 0, 1);
}

Matrix<4, 4> rotationZ(float r)
{
	return Matrix<4, 4>(cosf(r), -sinf(r), 0, 0, sinf(r), cosf(r), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

Matrix<4, 4> shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	return Matrix<4, 4>(1, xy, xz, 0, yx, 1, yz, 0, zx, zy, 1, 0, 0, 0, 0, 1);
}

Tuple reflect(const Tuple& v, const Tuple& n)
{
	return v - n * 2 * dot(v, n);
}