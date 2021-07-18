#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/pattern.h"
#include "../RaytracerChallenge/material.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	const Color black = Color(0, 0, 0);
	const Color white = Color(1, 1, 1);

	TEST_CLASS(Chapter10Patterns)
	{
	public:

		TEST_METHOD(TestCreateStripePattern)
		{
			auto pattern = StripePattern(white, black);

			Assert::AreEqual(white, pattern.a);
			Assert::AreEqual(black, pattern.b);
		}

		TEST_METHOD(TestStripePatternConstantInY)
		{
			auto pattern = StripePattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 1, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 2, 0)));
		}

		TEST_METHOD(TestStripePatternConstantInZ)
		{
			auto pattern = StripePattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 1)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 2)));
		}

		TEST_METHOD(TestStripePatternAlternatesInX)
		{
			auto pattern = StripePattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0.9, 0, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(1, 0, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(-0.1, 0, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(-1, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(-1.1, 0, 0)));
		}

		TEST_METHOD(TestLightingWithPattern)
		{
			auto m = Material();
			auto pattern = StripePattern(white, black);
			m.pattern = &pattern;
			m.ambient = 1;
			m.diffuse = 0;
			m.specular = 0;
			auto eyev = Tuple::vector(0, 0, -1);
			auto normalv = Tuple::vector(0, 0, -1);
			auto light = PointLight(Tuple::point(0, 0, -10), white);

			auto c1 = m.lighting(light, Tuple::point(0.9, 0, 0), eyev, normalv, false);
			auto c2 = m.lighting(light, Tuple::point(1.1, 0, 0), eyev, normalv, false);

			Assert::AreEqual(white, c1);
			Assert::AreEqual(black, c2);
		}
	};
}