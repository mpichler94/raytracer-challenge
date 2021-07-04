#include "pch.h"
#include "CppUnitTest.h"
#include "../RaytracerChallenge/tuple.h"
#include "../RaytracerChallenge/math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter1Tuple)
	{
	public:

		TEST_METHOD(TestIsPoint)
		{
			auto point = Tuple(4.3f, -4.2f, 3.1f, 1.0f);

			Assert::AreEqual(4.3f, point.x);
			Assert::AreEqual(-4.2f, point.y);
			Assert::AreEqual(3.1f, point.z);
			Assert::AreEqual(1.0f, point.w);
			Assert::IsTrue(point.isPoint());
		}
		TEST_METHOD(TestIsVector)
		{
			auto vector = Tuple(4.3f, -4.2f, 3.1f, 0.0f);

			Assert::AreEqual(4.3f, vector.x);
			Assert::AreEqual(-4.2f, vector.y);
			Assert::AreEqual(3.1f, vector.z);
			Assert::AreEqual(0.0f, vector.w);
			Assert::IsTrue(vector.isVector());
		}

		TEST_METHOD(TestPointFactory)
		{
			auto point = Tuple::point(4.3f, -4.2f, 3.1f);

			auto ref = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
			Assert::AreEqual(ref, point);
		}

		TEST_METHOD(TestVectorFactory)
		{
			auto vector = Tuple::vector(4.3f, -4.2f, 3.1f);

			auto ref = Tuple(4.3f, -4.2f, 3.1f, 0.0f);

			Assert::AreEqual(ref, vector);
		}

		TEST_METHOD(TestAdd)
		{
			auto a1 = Tuple(3, -2, 5, 1);
			auto a2 = Tuple(-2, 3, 1, 0);

			auto ref = Tuple(1, 1, 6, 1);

			Assert::AreEqual(ref, a1 + a2);
		}

		TEST_METHOD(TestSubract)
		{
			auto a1 = Tuple::point(3, 2, 1);
			auto a2 = Tuple::point(5, 6, 7);

			auto ref = Tuple::vector(-2, -4, -6);

			Assert::AreEqual(ref, a1 - a2);
		}

		TEST_METHOD(TestSubractVectorFromPoint)
		{
			auto a1 = Tuple::point(3, 2, 1);
			auto a2 = Tuple::vector(5, 6, 7);

			auto ref = Tuple::point(-2, -4, -6);

			Assert::AreEqual(ref, a1 - a2);
		}

		TEST_METHOD(TestSubractVectorFromVector)
		{
			auto a1 = Tuple::vector(3, 2, 1);
			auto a2 = Tuple::vector(5, 6, 7);

			auto ref = Tuple::vector(-2, -4, -6);

			Assert::AreEqual(ref, a1 - a2);
		}

		TEST_METHOD(TestSubractFromZero)
		{
			auto zero = Tuple::vector(0, 0, 0);
			auto v = Tuple::vector(1, -2, 3);

			auto ref = Tuple::vector(-1, 2, -3);

			Assert::AreEqual(ref, zero - v);
		}

		TEST_METHOD(TestNegate)
		{
			auto v = Tuple(1, -2, 3, -4);

			auto ref = Tuple(-1, 2, -3, 4);

			Assert::AreEqual(ref, -v);
		}

		TEST_METHOD(TestMultiply)
		{
			auto v = Tuple(1, -2, 3, -4);

			auto ref = Tuple(3.5, -7, 10.5, -14);

			Assert::AreEqual(ref, v * 3.5);
		}

		TEST_METHOD(TestMultiplyFraction)
		{
			auto v = Tuple(1, -2, 3, -4);

			auto ref = Tuple(0.5, -1, 1.5, -2);

			Assert::AreEqual(ref, v * 0.5);
		}

		TEST_METHOD(TestDivide)
		{
			auto v = Tuple(1, -2, 3, -4);

			auto ref = Tuple(0.5, -1, 1.5, -2);

			Assert::AreEqual(ref, v / 2);
		}

		TEST_METHOD(TestMagX)
		{
			auto v = Tuple::vector(1, 0, 0);

			Assert::AreEqual(1.f, length(v));
		}

		TEST_METHOD(TestMagY)
		{
			auto v = Tuple::vector(0, 1, 0);

			Assert::AreEqual(1.f, length(v));
		}

		TEST_METHOD(TestMagZ)
		{
			auto v = Tuple::vector(0, 0, 1);

			Assert::AreEqual(1.f, length(v));
		}

		TEST_METHOD(TestMagPos)
		{
			auto v = Tuple::vector(1, 2, 3);

			Assert::AreEqual(sqrtf(14), length(v));
		}

		TEST_METHOD(TestMagNeg)
		{
			auto v = Tuple::vector(1, 2, 3);

			Assert::AreEqual(sqrtf(14), length(v));
		}

		TEST_METHOD(TestNormalize)
		{
			auto v = Tuple::vector(4, 0, 0);

			Assert::AreEqual(Tuple::vector(1, 0, 0), normalize(v));

			v.normalize();
			Assert::AreEqual(Tuple::vector(1, 0, 0), v);
		}

		TEST_METHOD(TestNormalize2)
		{
			auto v = Tuple::vector(1, 2, 3);

			Assert::IsTrue(areEqual(Tuple::vector(0.26726f, 0.53452f, 0.80178f), normalize(v)));

			v.normalize();
			Assert::IsTrue(areEqual(Tuple::vector(0.26726f, 0.53452f, 0.80178f), v));
		}

		TEST_METHOD(TestNormalizeMag)
		{
			auto v = Tuple::vector(1, 2, 3);
			auto norm = normalize(v);

			Assert::IsTrue(areEqual(1.f, length(norm)));
		}

		TEST_METHOD(TestDot)
		{
			auto a = Tuple::vector(1, 2, 3);
			auto b = Tuple::vector(2, 3, 4);

			Assert::IsTrue(areEqual(20, dot(a, b)));
		}

		TEST_METHOD(TestCross)
		{
			auto a = Tuple::vector(1, 2, 3);
			auto b = Tuple::vector(2, 3, 4);

			Assert::AreEqual(Tuple::vector(-1, 2, -1), cross(a, b));
			Assert::AreEqual(Tuple::vector(1, -2, 1), cross(b, a));
		}
	};
}
