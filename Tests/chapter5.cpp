#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/ray.h"
#include "../RaytracerChallenge/primitive.h"
#include "../RaytracerChallenge/intersection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter5RayShapeIntersection)
	{
	public:

		TEST_METHOD(TestCreateRay)
		{
			auto origin = Tuple::point(1, 2, 3);
			auto direction = Tuple::vector(4, 5, 6);
			auto r = Ray(origin, direction);

			Assert::AreEqual(origin, r.origin);
			Assert::AreEqual(direction, r.direction);
		}

		TEST_METHOD(TestRayPosition)
		{
			auto r = Ray(Tuple::point(2, 3, 4), Tuple::vector(1, 0, 0));

			Assert::AreEqual(Tuple::point(2, 3, 4), r.pos(0));
			Assert::AreEqual(Tuple::point(3, 3, 4), r.pos(1));
			Assert::AreEqual(Tuple::point(1, 3, 4), r.pos(-1));
			Assert::AreEqual(Tuple::point(4.5, 3, 4), r.pos(2.5));
		}

		TEST_METHOD(TestRaySphereIntersection)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			auto xs = s.intersect(r);
			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(4.0f, xs[0].t);
			Assert::AreEqual(6.0f, xs[1].t);
		}

		TEST_METHOD(TestRaySphereTangent)
		{
			auto r = Ray(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			auto xs = s.intersect(r);
			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(5.0f, xs[0].t);
			Assert::AreEqual(5.0f, xs[1].t);
		}

		TEST_METHOD(TestRaySphereMiss)
		{
			auto r = Ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			auto xs = s.intersect(r);
			Assert::AreEqual(0ull, xs.count());
		}

		TEST_METHOD(TestRayInsideSphere)
		{
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			auto xs = s.intersect(r);
			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(-1.0f, xs[0].t);
			Assert::AreEqual(1.0f, xs[1].t);
		}

		TEST_METHOD(TestRayBehindSphere)
		{
			auto r = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			auto xs = s.intersect(r);
			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(-6.0f, xs[0].t);
			Assert::AreEqual(-4.0f, xs[1].t);
		}

		TEST_METHOD(TestIntersection)
		{
			auto s = Sphere();
			auto i = Intersection(3.5, &s);

			Assert::AreEqual(3.5f, i.t);
			Assert::AreEqual((void*)&s, (void*)i.primitive);
			Assert::AreEqual(s, static_cast<const Sphere&>(*i.primitive));
		}

		TEST_METHOD(TestIntersections)
		{
			auto s = Sphere();
			auto i1 = Intersection(1, &s);
			auto i2 = Intersection(2, &s);
			auto xs = Intersections({ i1, i2 });

			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(1.f, xs[0].t);
			Assert::AreEqual(2.f, xs[1].t);
		}

		TEST_METHOD(TestIntersectionsPrimitive)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			auto xs = s.intersect(r);

			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(s, static_cast<const Sphere&>(*xs[0].primitive));
			Assert::AreEqual(s, static_cast<const Sphere&>(*xs[1].primitive));
		}

		TEST_METHOD(TestHitAllPositive)
		{
			auto s = Sphere();
			const auto i1 = Intersection(1, &s);
			auto i2 = Intersection(2, &s);
			auto xs = Intersections{ i2, i1 };

			auto i = xs.hit();
			Assert::AreEqual(i1, *i);
		}

		TEST_METHOD(TestHitSomeNegative)
		{
			auto s = Sphere();
			auto i1 = Intersection(-1, &s);
			const auto i2 = Intersection(1, &s);
			auto xs = Intersections{ i2, i1 };

			auto i = xs.hit();
			Assert::AreEqual(i2, *i);
		}

		TEST_METHOD(TestHitAllNegative)
		{
			auto s = Sphere();
			auto i1 = Intersection(-2, &s);
			auto i2 = Intersection(-1, &s);
			auto xs = Intersections{ i2, i1 };

			auto i = xs.hit();
			Assert::IsTrue(i == nullptr);
		}

		TEST_METHOD(TestHitLowestNonnegative)
		{
			auto s = Sphere();
			auto i1 = Intersection(5, &s);
			auto i2 = Intersection(7, &s);
			auto i3 = Intersection(-3, &s);
			const auto i4 = Intersection(2, &s);
			auto xs = Intersections{ i1, i2, i3, i4 };

			auto i = xs.hit();
			Assert::AreEqual(i4, *i);
		}

		TEST_METHOD(TestTranslateRay)
		{
			auto r = Ray(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
			auto m = translation(3, 4, 5);

			auto r2 = r.transform(m);

			Assert::AreEqual(Tuple::point(4, 6, 8), r2.origin);
			Assert::AreEqual(Tuple::vector(0, 1, 0), r2.direction);
		}

		TEST_METHOD(TestScaleRay)
		{
			auto r = Ray(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
			auto m = scaling(2, 3, 4);

			auto r2 = r.transform(m);

			Assert::AreEqual(Tuple::point(2, 6, 12), r2.origin);
			Assert::AreEqual(Tuple::vector(0, 3, 0), r2.direction);
		}

		TEST_METHOD(TestDefaultTransform)
		{
			auto s = Sphere();

			Assert::AreEqual(Matrix<4, 4>::identity(), s.transform);
		}

		TEST_METHOD(TestChangeTransform)
		{
			auto s = Sphere();
			auto t = translation(2, 3, 4);

			s.transform = t;

			Assert::AreEqual(t, s.transform);
		}

		TEST_METHOD(TestIntersectScaledRay)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto s = Sphere();

			s.transform = scaling(2, 2, 2);
			auto xs = s.intersect(r);

			Assert::AreEqual(2ull, xs.count());
			Assert::AreEqual(3.f, xs[0].t);
			Assert::AreEqual(7.f, xs[1].t);

		}
	};
}
