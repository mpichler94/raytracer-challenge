#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/pattern.h"
#include "../RaytracerChallenge/material.h"
#include "../RaytracerChallenge/shape.h"
#include "../RaytracerChallenge/light.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TestPattern : public Pattern
{
public:
	TestPattern() {}

	virtual Color colorAt(const Tuple& point) const override { return Color(point.x, point.y, point.z); }
};

namespace Tests
{
	const Color black = Color(0, 0, 0);
	const Color white = Color(1, 1, 1);

	TEST_CLASS(Chapter10StripePattern)
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
			auto s = Sphere();
			auto m = Material();
			auto pattern = StripePattern(white, black);
			m.pattern = &pattern;
			m.ambient = 1;
			m.diffuse = 0;
			m.specular = 0;
			auto eyev = Tuple::vector(0, 0, -1);
			auto normalv = Tuple::vector(0, 0, -1);
			auto light = PointLight(Tuple::point(0, 0, -10), white);

			auto c1 = m.lighting(s, light, Tuple::point(0.9, 0, 0), eyev, normalv, false);
			auto c2 = m.lighting(s, light, Tuple::point(1.1, 0, 0), eyev, normalv, false);

			Assert::AreEqual(white, c1);
			Assert::AreEqual(black, c2);
		}

		TEST_METHOD(TestStripesWithObjectTransformation)
		{
			auto object = Sphere();
			object.transform = scaling(2, 2, 2);
			auto pattern = StripePattern(white, black);

			auto c = pattern.colorAtShape(object, Tuple::point(1.5, 0, 0));

			Assert::AreEqual(white, c);
		}

		TEST_METHOD(TestStripesWithPatternTransformation)
		{
			auto object = Sphere();
			auto pattern = StripePattern(white, black);
			pattern.transform = scaling(2, 2, 2);

			auto c = pattern.colorAtShape(object, Tuple::point(1.5, 0, 0));

			Assert::AreEqual(white, c);
		}

		TEST_METHOD(TestStripesWithObjectAndPatternTransformation)
		{
			auto object = Sphere();
			object.transform = scaling(2, 2, 2);
			auto pattern = StripePattern(white, black);
			pattern.transform = translation(0.5, 0, 0);

			auto c = pattern.colorAtShape(object, Tuple::point(2.5, 0, 0));

			Assert::AreEqual(white, c);
		}
	};

	TEST_CLASS(Chapter10AbstractPattern)
	{
	public:
		TEST_METHOD(TestDefaultPatternTransformation)
		{
			auto pattern = TestPattern();

			Assert::AreEqual(Matrix<4, 4>::identity(), pattern.transform);
		}

		TEST_METHOD(TestAssignTransform)
		{
			auto pattern = TestPattern();
			pattern.transform = translation(1, 2, 3);

			Assert::AreEqual(translation(1, 2, 3), pattern.transform);
		}

		TEST_METHOD(TestPatternWithObjectTransformation)
		{
			auto shape = Sphere();
			shape.transform = scaling(2, 2, 2);
			auto pattern = TestPattern();

			auto c = pattern.colorAtShape(shape, Tuple::point(2, 3, 4));

			Assert::AreEqual(Color(1, 1.5, 2), c);
		}

		TEST_METHOD(TestPatternWithPatternTransformation)
		{
			auto shape = Sphere();
			auto pattern = TestPattern();
			pattern.transform = scaling(2, 2, 2);

			auto c = pattern.colorAtShape(shape, Tuple::point(2, 3, 4));

			Assert::AreEqual(Color(1, 1.5, 2), c);
		}

		TEST_METHOD(TestPatternWithObjectAndPatternTransformation)
		{
			auto shape = Sphere();
			shape.transform = scaling(2, 2, 2);
			auto pattern = TestPattern();
			pattern.transform = translation(0.5, 1, 1.5);

			auto c = pattern.colorAtShape(shape, Tuple::point(2.5, 3, 3.5));

			Assert::AreEqual(Color(0.75, 0.5, 0.25), c);
		}
	};

	TEST_CLASS(Chapter10MorePatterns)
	{
	public:
		TEST_METHOD(TestGradientInterpolation)
		{
			auto pattern = GradientPattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(Color(0.75, 0.75, 0.75), pattern.colorAt(Tuple::point(0.25, 0, 0)));
			Assert::AreEqual(Color(0.5, 0.5, 0.5), pattern.colorAt(Tuple::point(0.5, 0, 0)));
			Assert::AreEqual(Color(0.25, 0.25, 0.25), pattern.colorAt(Tuple::point(0.75, 0, 0)));
		}

		TEST_METHOD(TestRingPattern)
		{
			auto pattern = RingPattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(1, 0, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(0, 0, 1)));
			// 0.708 = just slightly more than sqrt(2)/2
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(0.708, 0, 0.708)));
		}

		TEST_METHOD(TestCheckersRepeatInX)
		{
			auto pattern = CheckersPattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0.99, 0, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(1.01, 0, 0)));
		}

		TEST_METHOD(TestCheckersRepeatInY)
		{
			auto pattern = CheckersPattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0.99, 0)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(0, 1.01, 0)));
		}

		TEST_METHOD(TestCheckersRepeatInZ)
		{
			auto pattern = CheckersPattern(white, black);

			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0)));
			Assert::AreEqual(white, pattern.colorAt(Tuple::point(0, 0, 0.99)));
			Assert::AreEqual(black, pattern.colorAt(Tuple::point(0, 0, 1.01)));
		}
	};
}