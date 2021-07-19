#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/material.h"
#include "../RaytracerChallenge/world.h"
#include "../RaytracerChallenge/shape.h"
#include "../RaytracerChallenge/ray.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter8Shadows)
	{
	public:

		TEST_METHOD(TestSurfaceInShadow)
		{
			auto s = Sphere();
			auto m = Material();
			auto position = Tuple::point(0, 0, 0);

			auto eyev = Tuple::vector(0, 0, -1);
			auto normalv = Tuple::vector(0, 0, -1);
			auto light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));
			auto inShadow = true;

			auto result = m.lighting(s, light, position, eyev, normalv, inShadow);

			Assert::AreEqual(Color(0.1, 0.1, 0.1), result);
		}

		TEST_METHOD(TestNothingColinear)
		{
			auto w = World::Default();
			auto p = Tuple::point(0, 10, 0);

			Assert::AreEqual(false, w.isShadowed(p));
		}

		TEST_METHOD(TestObjectBetweenPointAndLight)
		{
			auto w = World::Default();
			auto p = Tuple::point(10, -10, 10);

			Assert::AreEqual(true, w.isShadowed(p));
		}

		TEST_METHOD(TestObjectBehindLight)
		{
			auto w = World::Default();
			auto p = Tuple::point(-20, 20, -20);

			Assert::AreEqual(false, w.isShadowed(p));
		}

		TEST_METHOD(TestObjectBehindPoint)
		{
			auto w = World::Default();
			auto p = Tuple::point(-2, 2, -2);

			Assert::AreEqual(false, w.isShadowed(p));
		}

		TEST_METHOD(TestShadeInShadow)
		{
			auto w = World();
			w.light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));

			auto s1 = Sphere();
			w.addObject(&s1);

			auto s2 = Sphere();
			s2.transform = translation(0, 0, 10);

			auto r = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
			auto i = Intersection(4, &s2);

			auto comps = i.prepare(r);
			auto c = comps.shade(w, 5);

			Assert::AreEqual(Color(0.1, 0.1, 0.1), c);
		}

		TEST_METHOD(TestHitOffsetPoint)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto shape = Sphere();
			shape.transform = translation(0, 0, 1);
			auto i = Intersection(5, &shape);

			auto comps = i.prepare(r);
			Assert::IsTrue(comps.overPoint.z < -EPSILON / 2);
			Assert::IsTrue(comps.point.z > comps.overPoint.z);
		}


	};
}