#include <sstream>
#include <iomanip>
#include "matrix.h"
#include "math.h"
#include "tuple.h"

Matrix<2u, 2u>::Matrix(float f)
    : _11(f), _12(f), _21(f), _22(f)
{
}

Matrix<2u, 2u>::Matrix(float m11, float m12, float m21, float m22)
    : _11(m11), _12(m12), _21(m21), _22(m22)
{
}

float determinant(const Matrix<2, 2>& m)
{
    return m._11 * m._22 - m._12 * m._21;
}

bool operator==(const Matrix<2, 2>& lhs, const Matrix<2, 2>& rhs)
{
    if (!areEqual(lhs._11, rhs._11) || !areEqual(lhs._12, rhs._12))
        return false;
    if (!areEqual(lhs._21, rhs._21) || !areEqual(lhs._22, rhs._22))
        return false;

    return true;
}

Matrix<2, 2> operator*(const Matrix<2, 2>& a, const Matrix<2, 2>& b)
{
    return Matrix<2, 2>(a._11 * b._11 + a._12 * b._21, a._11 * b._12 + a._12 * b._22, a._21 * b._11 + a._22 * b._21, a._21 * b._12 + a._22 * b._22);
}

std::wstring ToString(const Matrix<2, 2>& m)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(5);
    ss << "| " << m._11 << " " << m._12 << " |" << std::endl;
    ss << "| " << m._21 << " " << m._22 << " |" << std::endl;
    return ss.str();
}

Matrix<3u, 3u>::Matrix(float f)
    : _11(f), _12(f), _13(f),  _21(f), _22(f), _23(f), _31(f), _32(f), _33(f)
{
}

Matrix<3u, 3u>::Matrix(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
    : _11(m11), _12(m12), _13(m13), _21(m21), _22(m22), _23(m23), _31(m31), _32(m32), _33(m33)
{
}

Matrix<2, 2> submatrix(const Matrix<3, 3>& m, size_t i, size_t j)
{
    if (i == 0 && j == 0)
    {
        return Matrix<2, 2>(m._22, m._23, m._32, m._33);
    }
    if (i == 0 && j == 1)
    {
        return Matrix<2, 2>(m._21, m._23, m._31, m._33);
    }
    if (i == 0 && j == 2)
    {
        return Matrix<2, 2>(m._21, m._22, m._31, m._32);
    }
    if (i == 1 && j == 0)
    {
        return Matrix<2, 2>(m._12, m._13, m._32, m._33);
    }
    if (i == 1 && j == 1)
    {
        return Matrix<2, 2>(m._11, m._13, m._31, m._33);
    }
    if (i == 1 && j == 2)
    {
        return Matrix<2, 2>(m._11, m._12, m._31, m._32);
    }
    if (i == 2 && j == 0)
    {
        return Matrix<2, 2>(m._12, m._13, m._22, m._23);
    }
    if (i == 2 && j == 1)
    {
        return Matrix<2, 2>(m._11, m._13, m._21, m._23);
    }
    if (i == 2 && j == 2)
    {
        return Matrix<2, 2>(m._11, m._12, m._21, m._22);
    }

    return Matrix<2, 2>();
}

float minor(const Matrix<3, 3>& m, size_t i, size_t j)
{
    return determinant(submatrix(m, i, j));
}

float cofactor(const Matrix<3, 3>& m, size_t i, size_t j)
{
    if((i + j) % 2 == 0)
        return determinant(submatrix(m, i, j));
    return -determinant(submatrix(m, i, j));
}

float determinant(const Matrix<3, 3>& m)
{
    return m._11 * cofactor(m, 0, 0) + m._12 * cofactor(m, 0, 1) + m._13 * cofactor(m, 0, 2);
}

bool operator==(const Matrix<3, 3>& lhs, const Matrix<3, 3>& rhs)
{
    if (!areEqual(lhs._11, rhs._11) || !areEqual(lhs._12, rhs._12) || !areEqual(lhs._13, rhs._13))
        return false;
    if (!areEqual(lhs._21, rhs._21) || !areEqual(lhs._22, rhs._22) || !areEqual(lhs._23, rhs._23))
        return false;
    if (!areEqual(lhs._31, rhs._31) || !areEqual(lhs._32, rhs._32) || !areEqual(lhs._33, rhs._33))
        return false;

    return true;
}

Matrix<3, 3> operator*(const Matrix<3, 3>& a, const Matrix<3, 3>& b)
{
    return Matrix<3, 3>(a._11 * b._11 + a._12 * b._21 + a._13 * b._31, a._11 * b._12 + a._12 * b._22 + a._13 * b._32, a._11 * b._13 + a._12 * b._23 + a._13 * b._33, a._21 * b._11 + a._22 * b._21 + a._23 * b._31, a._21 * b._12 + a._22 * b._22 + a._23 * b._32, a._21 * b._13 + a._22 * b._23 + a._23 * b._33, a._31 * b._11 + a._32 * b._21 + a._33 * b._31, a._31 * b._12 + a._32 * b._22 + a._33 * b._32, a._31 * b._13 + a._32 * b._23 + a._33 * b._33);
}

std::wstring ToString(const Matrix<3, 3>& m)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(5);
    ss << "| " << m._11 << " " << m._12 << " " << m._13 << " |" << std::endl;
    ss << "| " << m._21 << " " << m._22 << " " << m._23 << " |" << std::endl;
    ss << "| " << m._31 << " " << m._32 << " " << m._33 << " |" << std::endl;
    return ss.str();
}

Matrix<4u, 4u>::Matrix(float f)
    : _11(f), _12(f), _13(f), _14(f), _21(f), _22(f), _23(f), _24(f), _31(f), _32(f), _33(f), _34(f), _41(f), _42(f), _43(f), _44(f)
{
}

Matrix<4u, 4u>::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
    : _11(m11), _12(m12), _13(m13), _14(m14), _21(m21), _22(m22), _23(m23), _24(m24), _31(m31), _32(m32), _33(m33), _34(m34), _41(m41), _42(m42), _43(m43), _44(m44)
{
}

bool Matrix<4, 4>::isInvertible() const
{
    return determinant(*this) != 0;
}

Matrix<4, 4>& Matrix<4u, 4u>::operator=(const Matrix<4, 4>& other)
{
    _11 = other._11;
    _12 = other._12;
    _13 = other._13;
    _14 = other._14;
    _21 = other._21;
    _22 = other._22;
    _23 = other._23;
    _24 = other._24;
    _31 = other._31;
    _32 = other._32;
    _33 = other._33;
    _34 = other._34;
    _41 = other._41;
    _42 = other._42;
    _43 = other._43;
    _44 = other._44;

    return *this;
}

Matrix<4, 4>& Matrix<4u, 4u>::operator=(Matrix<4, 4>&& other)
{
    _11 = std::move(other._11);
    _12 = std::move(other._12);
    _13 = std::move(other._13);
    _14 = std::move(other._14);
    _21 = std::move(other._21);
    _22 = std::move(other._22);
    _23 = std::move(other._23);
    _24 = std::move(other._24);
    _31 = std::move(other._31);
    _32 = std::move(other._32);
    _33 = std::move(other._33);
    _34 = std::move(other._34);
    _41 = std::move(other._41);
    _42 = std::move(other._42);
    _43 = std::move(other._43);
    _44 = std::move(other._44);
    return *this;
}

Matrix<4, 4> Matrix<4u, 4u>::identity()
{
    return Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

Matrix<4, 4> transpose(const Matrix<4, 4>& m)
{
    return Matrix<4, 4>(m._11, m._21, m._31, m._41, m._12, m._22, m._32, m._42, m._13, m._23, m._33, m._43, m._14, m._24, m._34, m._44);
}

Matrix<3, 3> submatrix(const Matrix<4, 4>& m, size_t i, size_t j)
{
    if (i == 0 && j == 0)
    {
        return Matrix<3, 3>(m._22, m._23, m._24, m._32, m._33, m._34, m._42, m._43, m._44);
    }
    if (i == 0 && j == 1)
    {
        return Matrix<3, 3>(m._21, m._23, m._24, m._31, m._33, m._34, m._41, m._43, m._44);
    }
    if (i == 0 && j == 2)
    {
        return Matrix<3, 3>(m._21, m._22, m._24, m._31, m._32, m._34, m._41, m._42, m._44);
    }
    if (i == 0 && j == 3)
    {
        return Matrix<3, 3>(m._21, m._22, m._23, m._31, m._32, m._33, m._41, m._42, m._43);
    }
    if (i == 1 && j == 0)
    {
        return Matrix<3, 3>(m._12, m._13, m._14, m._32, m._33, m._34, m._42, m._43, m._44);
    }
    if (i == 1 && j == 1)
    {
        return Matrix<3, 3>(m._11, m._13, m._14, m._31, m._33, m._34, m._41, m._43, m._44);
    }
    if (i == 1 && j == 2)
    {
        return Matrix<3, 3>(m._11, m._12, m._14, m._31, m._32, m._34, m._41, m._42, m._44);
    }
    if (i == 1 && j == 3)
    {
        return Matrix<3, 3>(m._11, m._12, m._13, m._31, m._32, m._33, m._41, m._42, m._43);
    }
    if (i == 2 && j == 0)
    {
        return Matrix<3, 3>(m._12, m._13, m._14, m._22, m._23, m._24, m._42, m._43, m._44);
    }
    if (i == 2 && j == 1)
    {
        return Matrix<3, 3>(m._11, m._13, m._14, m._21, m._23, m._24, m._41, m._43, m._44);
    }
    if (i == 2 && j == 2)
    {
        return Matrix<3, 3>(m._11, m._12, m._14, m._21, m._22, m._24, m._41, m._42, m._44);
    }
    if (i == 2 && j == 3)
    {
        return Matrix<3, 3>(m._11, m._12, m._13, m._21, m._22, m._23, m._41, m._42, m._43);
    }
    if (i == 3 && j == 0)
    {
        return Matrix<3, 3>(m._12, m._13, m._14, m._22, m._23, m._24, m._32, m._33, m._34);
    }
    if (i == 3 && j == 1)
    {
        return Matrix<3, 3>(m._11, m._13, m._14, m._21, m._23, m._24, m._31, m._33, m._34);
    }
    if (i == 3 && j == 2)
    {
        return Matrix<3, 3>(m._11, m._12, m._14, m._21, m._22, m._24, m._31, m._32, m._34);
    }
    if (i == 3 && j == 3)
    {
        return Matrix<3, 3>(m._11, m._12, m._13, m._21, m._22, m._23, m._31, m._32, m._33);
    }

    return Matrix<3, 3>();
}

float cofactor(const Matrix<4, 4>& m, size_t i, size_t j)
{
    if ((i + j) % 2 == 0)
        return determinant(submatrix(m, i, j));
    return -determinant(submatrix(m, i, j));
}

float determinant(const Matrix<4, 4>& m)
{
    return m._11 * cofactor(m, 0, 0) + m._12 * cofactor(m, 0, 1) + m._13 * cofactor(m, 0, 2) + m._14 * cofactor(m, 0, 3);
}

Matrix<4, 4> inverse(const Matrix<4, 4>& m)
{
    auto cof = Matrix<4, 4>(cofactor(m, 0, 0), cofactor(m, 0, 1), cofactor(m, 0, 2), cofactor(m, 0, 3), cofactor(m, 1, 0), cofactor(m, 1, 1), cofactor(m, 1, 2), cofactor(m, 1, 3), cofactor(m, 2, 0), cofactor(m, 2, 1), cofactor(m, 2, 2), cofactor(m, 2, 3), cofactor(m, 3, 0), cofactor(m, 3, 1), cofactor(m, 3, 2), cofactor(m, 3, 3));
    auto cofT = transpose(cof);
    auto det = determinant(m);
    return cofT * (1.f / det);
}

bool operator==(const Matrix<4, 4>& lhs, const Matrix<4, 4>& rhs)
{
    if (!areEqual(lhs._11, rhs._11) || !areEqual(lhs._12, rhs._12) || !areEqual(lhs._13, rhs._13) || !areEqual(lhs._14, rhs._14))
        return false;
    if (!areEqual(lhs._21, rhs._21) || !areEqual(lhs._22, rhs._22) || !areEqual(lhs._23, rhs._23) || !areEqual(lhs._24, rhs._24))
        return false;
    if (!areEqual(lhs._31, rhs._31) || !areEqual(lhs._32, rhs._32) || !areEqual(lhs._33, rhs._33) || !areEqual(lhs._34, rhs._34))
        return false;
    if (!areEqual(lhs._41, rhs._41) || !areEqual(lhs._42, rhs._42) || !areEqual(lhs._43, rhs._43) || !areEqual(lhs._44, rhs._44))
        return false;

    return true;
}

Matrix<4, 4> operator*(const Matrix<4, 4>& a, const Matrix<4, 4>& b)
{
    return Matrix<4, 4>(a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41, a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42, a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43, a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44, a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41, a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42, a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43, a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44, a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41, a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42, a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43, a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44, a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41, a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42, a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43, a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44);
}

Tuple operator*(const Matrix<4, 4>& m, const Tuple& v)
{
    return Tuple(m._11 * v.x + m._12 * v.y + m._13 * v.z + m._14 * v.w,
        m._21 * v.x + m._22 * v.y + m._23 * v.z + m._24 * v.w,
        m._31 * v.x + m._32 * v.y + m._33 * v.z + m._34 * v.w,
        m._41 * v.x + m._42 * v.y + m._43 * v.z + m._44 * v.w);
}

Matrix<4, 4> operator*(const Matrix<4, 4>& m, const float f)
{
    return Matrix<4, 4>(m._11 * f, m._12 * f, m._13 * f, m._14 * f, m._21 * f, m._22 * f, m._23 * f, m._24 * f, m._31 * f, m._32 * f, m._33 * f, m._34 * f, m._41 * f, m._42 * f, m._43 * f, m._44 * f);
}

std::wstring ToString(const Matrix<4, 4>& m)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(5);
    ss << "| " << m._11 << " " << m._12 << " " << m._13 << " " << m._14 << " |" << std::endl;
    ss << "| " << m._21 << " " << m._22 << " " << m._23 << " " << m._24 << " |" << std::endl;
    ss << "| " << m._31 << " " << m._32 << " " << m._33 << " " << m._34 << " |" << std::endl;
    ss << "| " << m._41 << " " << m._42 << " " << m._43 << " " << m._44 << " |" << std::endl;
    return ss.str();
}
