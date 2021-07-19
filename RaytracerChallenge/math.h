#pragma once

#include "matrix.h"
#include "tuple.h"

const float EPSILON = 1e-4f;

const float pi = 3.1415926535897932384626434f;
const float e = 2.7182818284590452353602875f;
const float sqrtHalf = 0.70710678118654752440084436210485f;
const float sqrtTwo = 1.4142135623730950488016887242097f;


bool areEqual(float a, float b, float epsilon = 1e-5f);

Matrix<4, 4> translation(float x, float y, float z);
Matrix<4, 4> scaling(float x, float y, float z);
Matrix<4, 4> scaling(float s);

Matrix<4, 4> rotationX(float r);
Matrix<4, 4> rotationY(float r);
Matrix<4, 4> rotationZ(float r);

Matrix<4, 4> shearing(float xy, float xz, float yx, float yz, float zx, float zy);

Tuple reflect(const Tuple& v, const Tuple& n);

Matrix<4, 4> viewTransform(const Tuple& from, const Tuple& to, const Tuple& up);
