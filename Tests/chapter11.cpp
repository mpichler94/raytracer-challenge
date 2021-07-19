#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/material.h"
#include "../RaytracerChallenge/shape.h"
#include "../RaytracerChallenge/ray.h"
#include "../RaytracerChallenge/intersection.h"
#include "../RaytracerChallenge/world.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Tests
{
	const Color black = Color(0, 0, 0);
	const Color white = Color(1, 1, 1);

	TEST_CLASS(Chapter11Reflection)
	{
	public:

		TEST_METHOD(TestReflectivity)
		{
			auto m = Material();

			Assert::AreEqual(0.f, m.reflective);
		}

		TEST_METHOD(TestPrecomputeReflectionVector)
		{
			auto shape = Plane();
			auto r = Ray(Tuple::point(0, 1, -1), Tuple::vector(0, -sqrtHalf, sqrtHalf));
			auto i = Intersection(sqrtTwo, &shape);

			auto comps = i.prepare(r);

			Assert::AreEqual(Tuple::vector(0, sqrtHalf, sqrtHalf), comps.reflectv);
		}

		TEST_METHOD(TestReflectForNonreflective)
		{
			auto w = World::Default();
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
			auto shape = w.getObject(1);
			shape->material.ambient = 1;
			auto i = Intersection(1, shape);

			auto comps = i.prepare(r);
			auto color = comps.reflectedColor(w, 5);

			Assert::AreEqual(Color(0, 0, 0), color);
		}

		TEST_METHOD(TestReflectForReflective)
		{
			auto w = World::Default();
			auto shape = Plane();
			shape.material.reflective = 0.5;
			shape.transform = translation(0, -1, 0);
			w.addObject(&shape);
			auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtHalf, sqrtHalf));
			auto i = Intersection(sqrtTwo, &shape);

			auto comps = i.prepare(r);
			auto color = comps.reflectedColor(w, 5);

			Assert::AreEqual(Color(0.19035, 0.23793, 0.14276), color);
		}

		TEST_METHOD(TestShadeHit)
		{
			auto w = World::Default();
			auto shape = Plane();
			shape.material.reflective = 0.5;
			shape.transform = translation(0, -1, 0);
			w.addObject(&shape);
			auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtHalf, sqrtHalf));
			auto i = Intersection(sqrtTwo, &shape);

			auto comps = i.prepare(r);
			auto color = comps.shade(w, 5);

			Assert::AreEqual(Color(0.87677, 0.92436, 0.82918), color);
		}

		TEST_METHOD(TestMutuallyReflective)
		{
			auto w = World();
			w.light = PointLight(Tuple::point(0, 0, 0), white);
			auto lower = Plane();
			lower.material.reflective = 1;
			lower.transform = translation(0, -1, 0);
			w.addObject(&lower);
			auto upper = Plane();
			upper.material.reflective = 1;
			upper.transform = translation(0, 1, 0);
			w.addObject(&upper);
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));

			Assert::AreEqual(Color(20.9), w.colorAt(r, 10));
		}

		TEST_METHOD(TestMaxRecursiveDepth)
		{
			auto w = World::Default();
			auto shape = Plane();
			shape.material.reflective = 0.5;
			shape.transform = translation(0, -1, 0);
			w.addObject(&shape);
			auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtHalf, sqrtHalf));
			auto i = Intersection(sqrtTwo, &shape);

			auto comps = i.prepare(r);
			auto color = comps.reflectedColor(w, 0);

			Assert::AreEqual(Color(0, 0, 0), color);
		}
	};
}