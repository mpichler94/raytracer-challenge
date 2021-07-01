#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/matrix.h"
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/tuple.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter3)
	{
	public:

		TEST_METHOD(TestMatrix4x4Constructor)
		{
			auto m = Matrix<4, 4>(1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5);

			Assert::IsTrue(areEqual(1, m._11));
			Assert::IsTrue(areEqual(4, m._14));
			Assert::IsTrue(areEqual(5.5, m._21));
			Assert::IsTrue(areEqual(7.5, m._23));
			Assert::IsTrue(areEqual(11, m._33));
			Assert::IsTrue(areEqual(13.5, m._41));
			Assert::IsTrue(areEqual(15.5, m._43));
		}

		TEST_METHOD(TestMatrix2x2Constructor)
		{
			auto m = Matrix<2, 2>(-3, 5, 1, -2);

			Assert::IsTrue(areEqual(-3, m._11));
			Assert::IsTrue(areEqual(5, m._12));
			Assert::IsTrue(areEqual(1, m._21));
			Assert::IsTrue(areEqual(-2, m._22));
		}

		TEST_METHOD(TestMatrix3x3Constructor)
		{
			auto m = Matrix<3, 3>(-3, 5, 0, 1, -2, -7, 0, 1, 1);

			Assert::IsTrue(areEqual(-3, m._11));
			Assert::IsTrue(areEqual(-2, m._22));
			Assert::IsTrue(areEqual(1, m._33));
		}

		TEST_METHOD(TestMatrixEqualityIdentical)
		{
			auto a = Matrix<4, 4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
			auto b = Matrix<4, 4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);

			Assert::AreEqual(a, b);
		}

		TEST_METHOD(TestMatrixEqualityDifferent)
		{
			auto a = Matrix<4, 4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
			auto b = Matrix<4, 4>(2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1);

			Assert::AreNotEqual(a, b);
		}

		TEST_METHOD(TestMatrixMultiplication)
		{
			auto a = Matrix<4, 4>(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
			auto b = Matrix<4, 4>(-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8);

			auto ref = Matrix<4, 4>(20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42);

			Assert::AreEqual(ref, a * b);
		}

		TEST_METHOD(TestMatrixTupleMultiplication)
		{
			auto a = Matrix<4, 4>(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1);
			auto b = Tuple(1, 2, 3, 1);

			auto ref = Tuple(18, 24, 33, 1);

			Assert::AreEqual(ref, a * b);
		}

		TEST_METHOD(TestMatrixIdentityMultiplication)
		{
			auto a = Matrix<4, 4>(0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32);
			auto b = Matrix<4, 4>::identity();

			Assert::AreEqual(a, a * b);
		}

		TEST_METHOD(TestMatrixTranspose)
		{
			auto a = Matrix<4, 4>(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8);
			auto ref = Matrix<4, 4>(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8);

			Assert::AreEqual(ref, transpose(a));
		}

		TEST_METHOD(TestMatrixTransposeIdentity)
		{
			auto a = Matrix<4, 4>::identity();
			auto ref = Matrix<4, 4>(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8);

			Assert::AreEqual(Matrix<4, 4>::identity(), transpose(a));
		}

		TEST_METHOD(TestMatrixDeterminant)
		{
			auto a = Matrix<2, 2>(1, 5, -3, 2);

			Assert::IsTrue(areEqual(17, determinant(a)));
		}

		TEST_METHOD(TestSubmatrix3x3)
		{
			auto a = Matrix<3, 3>(1, 5, 0, -3, 2, 7, 0, 6, -3);

			auto ref = Matrix<2, 2>(-3, 2, 0, 6);

			Assert::AreEqual(ref, submatrix(a, 0, 2));
		}

		TEST_METHOD(TestSubmatrix4x4)
		{
			auto a = Matrix<4, 4>(-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1);

			auto ref = Matrix<3, 3>(-6, 1, 6, -8, 8, 6, -7, -1, 1);

			Assert::AreEqual(ref, submatrix(a, 2, 1));
		}

		TEST_METHOD(TestMinor)
		{
			auto a = Matrix<3, 3>(3, 5, 0, 2, -1, -7, 6, -1, 5);
			auto b = submatrix(a, 1, 0);

			Assert::IsTrue(areEqual(25, determinant(b)));
			Assert::IsTrue(areEqual(25, minor(a, 1, 0)));
		}

		TEST_METHOD(TestCofactor)
		{
			auto a = Matrix<3, 3>(3, 5, 0, 2, -1, -7, 6, -1, 5);

			Assert::IsTrue(areEqual(-12, minor(a, 0, 0)));
			Assert::IsTrue(areEqual(-12, cofactor(a, 0, 0)));
			Assert::IsTrue(areEqual(25, minor(a, 1, 0)));
			Assert::IsTrue(areEqual(-25, cofactor(a, 1, 0)));
		}

		TEST_METHOD(TestDeterminant3x3)
		{
			auto a = Matrix<3, 3>(1, 2, 6, -5, 8, -4, 2, 6, 4);

			Assert::IsTrue(areEqual(56, cofactor(a, 0, 0)));
			Assert::IsTrue(areEqual(12, cofactor(a, 0, 1)));
			Assert::IsTrue(areEqual(-46, cofactor(a, 0, 2)));
			Assert::IsTrue(areEqual(-196, determinant(a)));
		}

		TEST_METHOD(TestDeterminant4x4)
		{
			auto a = Matrix<4, 4>(-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9);

			Assert::IsTrue(areEqual(690, cofactor(a, 0, 0)));
			Assert::IsTrue(areEqual(447, cofactor(a, 0, 1)));
			Assert::IsTrue(areEqual(210, cofactor(a, 0, 2)));
			Assert::IsTrue(areEqual(51, cofactor(a, 0, 3)));
			Assert::IsTrue(areEqual(-4071, determinant(a)));
		}

		TEST_METHOD(TestInvertible)
		{
			auto a = Matrix<4, 4>(6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6);

			Assert::IsTrue(areEqual(-2120, determinant(a)));
			Assert::IsTrue(a.isInvertible());
		}

		TEST_METHOD(TestNotInvertible)
		{
			auto a = Matrix<4, 4>(-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0);

			Assert::IsTrue(areEqual(0, determinant(a)));
			Assert::IsFalse(a.isInvertible());
		}

		TEST_METHOD(TestInverse)
		{
			auto a = Matrix<4, 4>(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);

			auto b = inverse(a);

			auto ref = Matrix<4, 4>(0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639);

			Assert::IsTrue(areEqual(532, determinant(a)));
			Assert::IsTrue(areEqual(-160, cofactor(a, 2, 3)));
			Assert::IsTrue(areEqual(-160.f / 532.f, b._43));
			Assert::IsTrue(areEqual(105, cofactor(a, 3, 2)));
			Assert::IsTrue(areEqual(105.f / 532.f, b._34));

			Assert::AreEqual(ref, b);
		}

		TEST_METHOD(TestInverse2)
		{
			auto a = Matrix<4, 4>(8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4);

			auto ref = Matrix<4, 4>(-0.15385, -0.15385, -0.28205, -0.53846,	-0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308);

			Assert::AreEqual(ref, inverse(a));
		}

		TEST_METHOD(TestInverse3)
		{
			auto a = Matrix<4, 4>(9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2);

			auto ref = Matrix<4, 4>(-0.04074, -0.07778, 0.14444, -0.22222, -0.07778, 0.03333, 0.36667, -0.33333, -0.02901, -0.14630, -0.10926, 0.12963, 0.17778, 0.06667, -0.26667, 0.33333);

			Assert::AreEqual(ref, inverse(a));
		}

		TEST_METHOD(TestInverseOfInverse)
		{
			auto a = Matrix<4, 4>(3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1);
			auto b = Matrix<4, 4>(8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5);

			auto c = a * b;

			Assert::AreEqual(a, c * inverse(b));
		}

		TEST_METHOD(PLAY)
		{
			std::wstring str1 = ToString(inverse(Matrix<4, 4>::identity()));

			auto a = Matrix<4, 4>(3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1);
			std::wstring str2 = ToString(a * inverse(a));

			Assert::AreEqual(inverse(transpose(a)), transpose(inverse(a)));

			auto b = Matrix<4, 4>::identity();
			auto t = Tuple(2, 3, 4, 5);
			b._12 = 1.5;
			std::wstring str3 = ToString(b * t);
		}

	};
}