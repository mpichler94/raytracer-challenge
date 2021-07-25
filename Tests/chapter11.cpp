#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/material.h"
#include "../RaytracerChallenge/shape.h"
#include "../RaytracerChallenge/ray.h"
#include "../RaytracerChallenge/intersection.h"
#include "../RaytracerChallenge/world.h"
#include "../RaytracerChallenge/pattern.h"


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

	TEST_CLASS(Chapter11Refraction)
	{
	public:

		TEST_METHOD(TestTransparencyAndRefractionIndex)
		{
			auto m = Material();

			Assert::AreEqual(0.f, m.transparency);
			Assert::AreEqual(1.f, m.refractiveIndex);
		}

		TEST_METHOD(TestGlassSphere)
		{
			auto s = Sphere::glass();

			Assert::AreEqual(1.f, s.material.transparency);
			Assert::AreEqual(1.5f, s.material.refractiveIndex);
		}

		float n1[6] = { 1.0, 1.5, 2.0, 2.5, 2.5, 1.5 };
		float n2[6] = { 1.5, 2.0, 2.5, 2.5, 1.5, 1.0 };

		void refractiveIntersectionOutline(int i)
		{
			auto a = Sphere::glass();
			a.transform = scaling(2, 2, 2);
			a.material.refractiveIndex = 1.5;
			auto b = Sphere::glass();
			b.transform = translation(0, 0, -0.25f);
			b.material.refractiveIndex = 2.f;
			auto c = Sphere::glass();
			c.transform = translation(0, 0, 0.25);
			c.material.refractiveIndex = 2.5;
			auto r = Ray(Tuple::point(0, 0, -4), Tuple::vector(0, 0, 1));
			auto xs = Intersections{ Intersection(2, &a), Intersection(2.75, &b), Intersection(3.25, &c), Intersection(4.75, &b), Intersection(5.25, &c), Intersection(6, &a) };

			auto comps = xs[i].prepare(r, xs);

			Assert::AreEqual(n1[i], comps.n1);
			Assert::AreEqual(n2[i], comps.n2);
		}

		TEST_METHOD(TestFindN1AndN2At0)
		{
			refractiveIntersectionOutline(0);
		}

		TEST_METHOD(TestFindN1AndN2At1)
		{
			refractiveIntersectionOutline(1);
		}

		TEST_METHOD(TestFindN1AndN2At2)
		{
			refractiveIntersectionOutline(2);
		}

		TEST_METHOD(TestFindN1AndN2At3)
		{
			refractiveIntersectionOutline(3);
		}

		TEST_METHOD(TestFindN1AndN2At4)
		{
			refractiveIntersectionOutline(4);
		}

		TEST_METHOD(TestFindN1AndN2At5)
		{
			refractiveIntersectionOutline(5);
		}

		TEST_METHOD(TestUnderPoint)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto shape = Sphere::glass();
			shape.transform = translation(0, 0, 1);
			auto i = Intersection(5, &shape);
			auto xs = Intersections{ i };

			auto comps = i.prepare(r, xs);

			Assert::IsTrue(EPSILON / 2 < comps.underPoint.z);
			Assert::IsTrue(comps.point.z < comps.underPoint.z);
		}

		TEST_METHOD(TestRefractedColorOpaque)
		{
			auto w = World::Default();
			auto shape = w.getObject(0);
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto xs = Intersections{ Intersection(4, shape), Intersection(6, shape) };

			auto comps = xs[0].prepare(r, xs);
			auto c = comps.refractedColor(w, 5);

			Assert::AreEqual(Color(0, 0, 0), c);
		}

		TEST_METHOD(TestRefractedColorAtMaxDepth)
		{
			auto w = World::Default();
			auto shape = w.getObject(0);
			shape->material.transparency = 1.0;
			shape->material.refractiveIndex = 1.5;
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto xs = Intersections{ Intersection(4, shape), Intersection(6, shape) };

			auto comps = xs[0].prepare(r, xs);
			auto c = comps.refractedColor(w, 0);

			Assert::AreEqual(Color(0, 0, 0), c);
		}

		TEST_METHOD(TestRefractedColorUnderTotalInternalReflection)
		{
			auto w = World::Default();
			auto shape = w.getObject(0);
			shape->material.transparency = 1.0;
			shape->material.refractiveIndex = 1.5;
			auto r = Ray(Tuple::point(0, 0, sqrtHalf), Tuple::vector(0, 1, 0));
			auto xs = Intersections{ Intersection(-sqrtHalf, shape), Intersection(sqrtHalf, shape) };

			auto comps = xs[1].prepare(r, xs);
			auto c = comps.refractedColor(w, 5);

			Assert::AreEqual(Color(0, 0, 0), c);
		}

		TEST_METHOD(TestRefractedColor)
		{
			auto w = World::Default();
			auto a = w.getObject(0);
			a->material.ambient = 1.0;
			auto pattern = TestPattern();
			a->material.pattern = &pattern;
			auto b = w.getObject(1);
			b->material.transparency = 1.0;
			b->material.refractiveIndex = 1.5;
			auto r = Ray(Tuple::point(0, 0, 0.1), Tuple::vector(0, 1, 0));
			auto xs = Intersections{ Intersection(-0.9899, a), Intersection(-0.4899, b), Intersection(0.4899, b), Intersection(0.9899, a) };

			auto comps = xs[2].prepare(r, xs);
			auto c = comps.refractedColor(w, 5);

			Assert::AreEqual(Color(0, 0.99878, 0.04724), c);
		}

		TEST_METHOD(TestShadeHit)
		{
			auto w = World::Default();
			auto floor = Plane();
			floor.transform = translation(0, -1, 0);
			floor.material.transparency = 0.5;
			floor.material.refractiveIndex = 1.5;
			w.addObject(&floor);
			auto ball = Sphere();
			ball.material.color = Color(1, 0, 0);
			ball.material.ambient = 0.5;
			ball.transform = translation(0, -3.5, -0.5);
			w.addObject(&ball);
			auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtHalf, sqrtHalf));
			auto xs = Intersections{ Intersection(sqrtTwo, &floor) };

			auto comps = xs[0].prepare(r, xs);
			auto c = comps.shade(w, 5);

			Assert::AreEqual(Color(0.93642, 0.68642, 0.68642), c);
		}

		TEST_METHOD(TestChlickTIR)
		{
			auto shape = Sphere::glass();
			auto r = Ray(Tuple::point(0, 0, sqrtHalf), Tuple::vector(0, 1, 0));
			auto xs = Intersections{ Intersection(-sqrtHalf, &shape), Intersection(sqrtHalf, &shape) };

			auto comps = xs[1].prepare(r, xs);
			auto reflectance = comps.schlick();

			Assert::AreEqual(1.0f, reflectance);
		}

		TEST_METHOD(TestChlickPerpendicular)
		{
			auto shape = Sphere::glass();
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
			auto xs = Intersections{ Intersection(-1, &shape), Intersection(1, &shape) };

			auto comps = xs[1].prepare(r, xs);
			auto reflectance = comps.schlick();

			Assert::IsTrue(areEqual(0.04f, reflectance));
		}

		TEST_METHOD(TestChlickSmallAngleN2GreaterN1)
		{
			auto shape = Sphere::glass();
			auto r = Ray(Tuple::point(0, 0.99, -2), Tuple::vector(0, 0, 1));
			auto xs = Intersections{ Intersection(1.8589, &shape) };

			auto comps = xs[0].prepare(r, xs);
			auto reflectance = comps.schlick();

			Assert::IsTrue(areEqual(0.48873f, reflectance));
		}

		TEST_METHOD(TestShadeHitReflectiveTransparent)
		{
			auto w = World::Default();
			auto r = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrtHalf, sqrtHalf));
			auto floor = Plane();
			floor.transform = translation(0, -1, 0);
			floor.material.reflective = 0.5;
			floor.material.transparency = 0.5;
			floor.material.refractiveIndex = 1.5;
			w.addObject(&floor);
			auto ball = Sphere();
			ball.material.color = Color(1, 0, 0);
			ball.material.ambient = 0.5;
			ball.transform = translation(0, -3.5, -0.5);
			w.addObject(&ball);
			auto xs = Intersections{ Intersection(sqrtTwo, &floor) };

			auto comps = xs[0].prepare(r, xs);
			auto c = comps.shade(w, 5);

			Assert::AreEqual(Color(0.93391, 0.69643, 0.69243), c);
		}
	};
}