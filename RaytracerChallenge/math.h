#pragma once

#include "matrix.h"

const float pi = 3.1415926535897932384626434f;
const float e = 2.7182818284590452353602875f;
const float sqrtHalf = 0.70710678118654752440084436210485f;
const float sqrtTwo = 1.4142135623730950488016887242097f;

bool areEqual(float a, float b, float epsilon = 1e-5f);

Matrix<4, 4> translation(float x, float y, float z);
Matrix<4, 4> scaling(float x, float y, float z);

Matrix<4, 4> rotationX(float r);
Matrix<4, 4> rotationY(float r);
Matrix<4, 4> rotationZ(float r);

Matrix<4, 4> shearing(float xy, float xz, float yx, float yz, float zx, float zy);