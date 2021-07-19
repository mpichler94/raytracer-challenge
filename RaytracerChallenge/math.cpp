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

Matrix<4, 4> scaling(float s)
{
	return Matrix<4, 4>(s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, 1);
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

Matrix<4, 4> viewTransform(const Tuple& from, const Tuple& to, const Tuple& up)
{
	auto forward = normalize(to - from);
	auto left = cross(forward, normalize(up));
	auto trueUp = cross(left, forward);


	auto orientation = Matrix<4, 4>(left.x, left.y, left.z, 0, trueUp.x, trueUp.y, trueUp.z, 0, -forward.x, -forward.y, -forward.z, 0, 0, 0, 0, 1);
	return orientation * translation(-from.x, -from.y, -from.z);
}

