#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/matrix.h"
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/tuple.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter4Transformations)
	{
	public:

		TEST_METHOD(TestTransformation)
		{
			auto transform = translation(5, -3, 2);

			auto p = Tuple::point(-3, 4, 5);

			Assert::AreEqual(Tuple::point(2, 1, 7), transform * p);
		}

		TEST_METHOD(TestInverseTransformation)
		{
			auto transform = translation(5, -3, 2);
			auto inv = inverse(transform);
			auto p = Tuple::point(-3, 4, 5);

			Assert::AreEqual(Tuple::point(-8, 7, 3), inv * p);
		}

		TEST_METHOD(TestTransformVector)
		{
			auto transform = translation(5, -3, 2);

			auto v = Tuple::vector(-3, 4, 5);

			Assert::AreEqual(v, transform * v);
		}

		TEST_METHOD(TestScalePoint)
		{
			auto transform = scaling(2, 3, 4);

			auto p = Tuple::point(-4, 6, 8);

			Assert::AreEqual(Tuple::point(-8, 18, 32), transform * p);
		}

		TEST_METHOD(TestScaleVector)
		{
			auto transform = scaling(2, 3, 4);

			auto v = Tuple::vector(-4, 6, 8);

			Assert::AreEqual(Tuple::vector(-8, 18, 32), transform * v);
		}

		TEST_METHOD(TestInverseScale)
		{
			auto transform = scaling(2, 3, 4);
			auto inv = inverse(transform);
			auto v = Tuple::vector(-4, 6, 8);

			Assert::AreEqual(Tuple::vector(-2, 2, 2), inv * v);
		}

		TEST_METHOD(TestReflect)
		{
			auto transform = scaling(-1, 1, 1);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(-2, 3, 4), transform * p);
		}

		TEST_METHOD(TestRotationX)
		{
			auto p = Tuple::point(0, 1, 0);

			auto halfQuarter = rotationX(pi / 4);
			auto fullQuarter = rotationX(pi / 2);


			Assert::AreEqual(Tuple::point(0, sqrtHalf, sqrtHalf), halfQuarter * p);
			Assert::AreEqual(Tuple::point(0, 0, 1), fullQuarter * p);
		}

		TEST_METHOD(TestNegativeRotationX)
		{
			auto p = Tuple::point(0, 1, 0);

			auto halfQuarter = rotationX(pi / 4);
			auto inv = inverse(halfQuarter);


			Assert::AreEqual(Tuple::point(0, sqrtHalf, -sqrtHalf), inv * p);
		}

		TEST_METHOD(TestRotationY)
		{
			auto p = Tuple::point(0, 0, 1);

			auto halfQuarter = rotationY(pi / 4);
			auto fullQuarter = rotationY(pi / 2);


			Assert::AreEqual(Tuple::point(sqrtHalf, 0, sqrtHalf), halfQuarter * p);
			Assert::AreEqual(Tuple::point(1, 0, 0), fullQuarter * p);
		}

		TEST_METHOD(TestRotationZ)
		{
			auto p = Tuple::point(0, 1, 0);

			auto halfQuarter = rotationZ(pi / 4);
			auto fullQuarter = rotationZ(pi / 2);


			Assert::AreEqual(Tuple::point(-sqrtHalf, sqrtHalf, 0), halfQuarter * p);
			Assert::AreEqual(Tuple::point(-1, 0, 0), fullQuarter * p);
		}

		TEST_METHOD(TestShearXinProportiontoY)
		{
			auto transform = shearing(1, 0, 0, 0, 0, 0);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(5, 3, 4), transform * p);
		}

		TEST_METHOD(TestShearXinProportiontoZ)
		{
			auto transform = shearing(0, 1, 0, 0, 0, 0);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(6, 3, 4), transform * p);
		}

		TEST_METHOD(TestShearYinProportiontoX)
		{
			auto transform = shearing(0, 0, 1, 0, 0, 0);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(2, 5, 4), transform * p);
		}

		TEST_METHOD(TestShearYinProportiontoZ)
		{
			auto transform = shearing(0, 0, 0, 1, 0, 0);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(2, 7, 4), transform * p);
		}

		TEST_METHOD(TestShearZinProportiontoX)
		{
			auto transform = shearing(0, 0, 0, 0, 1, 0);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(2, 3, 6), transform * p);
		}

		TEST_METHOD(TestShearZinProportiontoY)
		{
			auto transform = shearing(0, 0, 0, 0, 0, 1);

			auto p = Tuple::point(2, 3, 4);

			Assert::AreEqual(Tuple::point(2, 3, 7), transform * p);
		}

		TEST_METHOD(TestSequenceOfTransformations)
		{
			auto p = Tuple::point(1, 0, 1);
			auto a = rotationX(pi / 2);
			auto b = scaling(5, 5, 5);
			auto c = translation(10, 5, 7);

			auto p2 = a * p;
			Assert::AreEqual(Tuple::point(1, -1, 0), p2);

			auto p3 = b * p2;
			Assert::AreEqual(Tuple::point(5, -5, 0), p3);

			auto p4 = c * p3;
			Assert::AreEqual(Tuple::point(15, 0, 7), p4);
		}

		TEST_METHOD(TestChainingTransformations)
		{
			auto p = Tuple::point(1, 0, 1);
			auto a = rotationX(pi / 2);
			auto b = scaling(5, 5, 5);
			auto c = translation(10, 5, 7);

			auto t = c * b * a;

			Assert::AreEqual(Tuple::point(15, 0, 7), t * p);
		}

	};
}