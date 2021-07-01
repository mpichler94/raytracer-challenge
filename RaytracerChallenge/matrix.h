#pragma once
#include <string>

class Tuple;

template <unsigned int M, unsigned int N>
class Matrix;

template <>
class Matrix<2u, 2u>
{
public:
	float _11, _12;
	float _21, _22;


public:
	Matrix() = default;

	Matrix(float f);
	Matrix(float m11, float m12, float m21, float m22);

	static Matrix fromRows(const Tuple& r1, const Tuple& r2);
	static Matrix fromCols(const Tuple& c1, const Tuple& c2);

	friend float determinant(const Matrix& m);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);

	friend Matrix operator*(const Matrix& a, const Matrix& b);

	friend std::wstring ToString(const Matrix& m);
};

template <>
class Matrix<3u, 3u>
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;


public:
	Matrix() = default;

	Matrix(float f);
	Matrix(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

	static Matrix fromRows(const Tuple& r1, const Tuple& r2, const Tuple& r3);
	static Matrix fromCols(const Tuple& c1, const Tuple& c2, const Tuple& c3);

	friend Matrix<2, 2> submatrix(const Matrix& m, size_t i, size_t j);
	friend float minor(const Matrix& m, size_t i, size_t j);
	friend float cofactor(const Matrix& m, size_t i, size_t j);
	friend float determinant(const Matrix& m);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);

	friend Matrix operator*(const Matrix& a, const Matrix& b);

	friend std::wstring ToString(const Matrix& m);
};

template <>
class Matrix<4u, 4u>
{
public:
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;


public:
	Matrix() = default;

	Matrix(float f);
	Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	bool isInvertible() const;

	static Matrix fromRows(const Tuple& r1, const Tuple& r2, const Tuple& r3, const Tuple& r4);
	static Matrix fromCols(const Tuple& c1, const Tuple& c2, const Tuple& c3, const Tuple& c4);

	static Matrix identity();

	friend Matrix transpose(const Matrix& m);

	friend Matrix<3, 3> submatrix(const Matrix& m, size_t i, size_t j);
	friend float cofactor(const Matrix& m, size_t i, size_t j);
	friend float determinant(const Matrix& m);
	friend Matrix<4, 4> inverse(const Matrix& m);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);

	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend Tuple operator*(const Matrix& m, const Tuple& v);
	friend Matrix operator*(const Matrix& m, const float f);

	friend std::wstring ToString(const Matrix& m);
};


