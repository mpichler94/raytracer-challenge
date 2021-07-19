#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/world.h"
#include "../RaytracerChallenge/ray.h"
#include "../RaytracerChallenge/intersection.h"
#include "../RaytracerChallenge/camera.h"
#include "../RaytracerChallenge/shape.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter7World)
	{
	public:

		TEST_METHOD(TestCreateWorld)
		{
			auto w = World();

			Assert::AreEqual(0ull, w.getObjectCount());
			Assert::AreEqual(Color(), w.light.intensity);
			Assert::AreEqual(Tuple(), w.light.position);
		}

		TEST_METHOD(TestDefaultWorld)
		{
			auto light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
			auto s1 = Sphere();
			s1.material.color = Color(0.8, 1.0, 0.6);
			s1.material.diffuse = 0.7;
			s1.material.specular = 0.2;
			auto s2 = Sphere();
			s2.transform = scaling(0.5, 0.5, 0.5);

			auto w = World::Default();

			Assert::AreEqual(light, static_cast<PointLight&>(w.light));
			Assert::AreEqual(2ull, w.getObjectCount());
			//Assert::IsTrue(w.contains(s1));
			//Assert::IsTrue(w.contains(s1));
			w.dispose();
		}

		TEST_METHOD(TestIntersect)
		{
			auto w = World::Default();
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

			auto xs = w.intersect(r);

			Assert::AreEqual(4ull, xs.count());
			Assert::AreEqual(4.f, xs[0].t);
			Assert::AreEqual(4.5f, xs[1].t);
			Assert::AreEqual(5.5f, xs[2].t);
			Assert::AreEqual(6.f, xs[3].t);
		}

		TEST_METHOD(TestPrecomputeIntersectionState)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto shape = Sphere();
			auto i = Intersection(4, &shape);

			auto comps = i.prepare(r);

			Assert::AreEqual(i.t, comps.t);
			Assert::AreEqual(static_cast<const Sphere&>(*i.primitive), static_cast<const Sphere&>(*comps.object));
			Assert::AreEqual(Tuple::point(0, 0, -1), comps.point);
			Assert::AreEqual(Tuple::vector(0, 0, -1), comps.eyev);
			Assert::AreEqual(Tuple::vector(0, 0, -1), comps.normal);
		}

		TEST_METHOD(TestHitWhenIntersectionOutside)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto shape = Sphere();
			auto i = Intersection(4, &shape);

			auto comps = i.prepare(r);

			Assert::AreEqual(false, comps.inside);
			Assert::AreEqual(i.t, comps.t);
		}

		TEST_METHOD(TestHitWhenIntersectionInside)
		{
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
			auto shape = Sphere();
			auto i = Intersection(1, &shape);

			auto comps = i.prepare(r);

			Assert::AreEqual(Tuple::point(0, 0, 1), comps.point);
			Assert::AreEqual(Tuple::vector(0, 0, -1), comps.eyev);
			Assert::AreEqual(true, comps.inside);
			Assert::AreEqual(Tuple::vector(0, 0, -1), comps.normal);
		}

		TEST_METHOD(TestShadeIntersection)
		{
			auto w = World::Default();
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto shape = w.getObject(0);
			auto i = Intersection(4, shape);

			auto comps = i.prepare(r);
			auto c = comps.shade(w, 5);

			Assert::AreEqual(Color(0.38066, 0.47583, 0.2855), c);
		}

		TEST_METHOD(TestShadeIntersectionFromInside)
		{
			auto w = World::Default();
			w.light = PointLight(Tuple::point(0, 0.25, 0), Color(1, 1, 1));
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
			auto shape = w.getObject(1);
			auto i = Intersection(0.5, shape);

			auto comps = i.prepare(r);
			auto c = comps.shade(w, 5);

			Assert::AreEqual(Color(0.90495, 0.90495, 0.90495), c);
		}

		TEST_METHOD(TestColorWhenMiss)
		{
			auto w = World::Default();
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));

			auto c = w.colorAt(r, 5);

			Assert::AreEqual(Color(0, 0, 0), c);
		}

		TEST_METHOD(TestColorWhenHit)
		{
			auto w = World::Default();
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

			auto c = w.colorAt(r, 5);

			Assert::AreEqual(Color(0.38066, 0.47583, 0.2855), c);
		}

		TEST_METHOD(TestColorWhenIntersectionBehindRay)
		{
			auto w = World::Default();
			auto outer = w.getObject(0);
			outer->material.ambient = 1;
			auto inner = w.getObject(1);
			inner->material.ambient = 1;
			auto r = Ray(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));

			auto c = w.colorAt(r, 5);

			Assert::AreEqual(inner->material.color, c);
		}
	};

	TEST_CLASS(Chapter7ViewTransformation)
	{
	public:
		TEST_METHOD(TestDefaultViewTransformation)
		{
			auto from = Tuple::point(0, 0, 0);
			auto to = Tuple::point(0, 0, -1);
			auto up = Tuple::vector(0, 1, 0);

			auto t = viewTransform(from, to, up);

			Assert::AreEqual(Matrix<4, 4>::identity(), t);
		}

		TEST_METHOD(TestViewTransformPosZ)
		{
			auto from = Tuple::point(0, 0, 0);
			auto to = Tuple::point(0, 0, 1);
			auto up = Tuple::vector(0, 1, 0);

			auto t = viewTransform(from, to, up);

			Assert::AreEqual(scaling(-1, 1, -1), t);
		}

		TEST_METHOD(TestViewTransformMovesWorld)
		{
			auto from = Tuple::point(0, 0, 8);
			auto to = Tuple::point(0, 0, 0);
			auto up = Tuple::vector(0, 1, 0);

			auto t = viewTransform(from, to, up);

			Assert::AreEqual(translation(0, 0, -8), t);
		}

		TEST_METHOD(TestArbitraryViewTransform)
		{
			auto from = Tuple::point(1, 3, 2);
			auto to = Tuple::point(4, -2, 8);
			auto up = Tuple::vector(1, 1, 0);

			auto t = viewTransform(from, to, up);

			auto expected = Matrix<4, 4>(-0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857, 0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000);

			Assert::AreEqual(expected, t);
		}
	};

	TEST_CLASS(Chapter7Camera)
	{
	public:
		TEST_METHOD(TestConstructCamera)
		{
			auto hSize = 160;
			auto vSize = 120;
			auto fov = pi / 2;

			auto c = Camera(hSize, vSize, fov);

			Assert::AreEqual(160u, c.getWidth());
			Assert::AreEqual(120u, c.getHeight());
			Assert::AreEqual(pi / 2, c.getFov());
			Assert::AreEqual(Matrix<4, 4>::identity(), c.getTransform());
		}

		TEST_METHOD(TestPixelSizeHorizontal)
		{
			auto c = Camera(200, 125, pi / 2);

			Assert::AreEqual(0.01f, c.getPixelSize());
		}

		TEST_METHOD(TestPixelSizeVertical)
		{
			auto c = Camera(125, 200, pi / 2);

			Assert::AreEqual(0.01f, c.getPixelSize());
		}

		TEST_METHOD(TestRayThroughCenter)
		{
			auto c = Camera(201, 101, pi / 2);

			auto r = c.getRay(100, 50);

			Assert::AreEqual(Tuple::point(0, 0, 0), r.origin);
			Assert::AreEqual(Tuple::vector(0, 0, -1), r.direction);
		}

		TEST_METHOD(TestRayThroughCorner)
		{
			auto c = Camera(201, 101, pi / 2);

			auto r = c.getRay(0, 0);

			Assert::AreEqual(Tuple::point(0, 0, 0), r.origin);
			Assert::AreEqual(Tuple::vector(0.66519, 0.33259, -0.66851), r.direction);
		}

		TEST_METHOD(TestRayWhenCameraIsTransformed)
		{
			auto c = Camera(201, 101, pi / 2);
			c.setTransform(rotationY(pi / 4) * translation(0, -2, 5));

			auto r = c.getRay(100, 50);

			Assert::AreEqual(Tuple::point(0, 2, -5), r.origin);
			Assert::AreEqual(Tuple::vector(sqrtHalf, 0, -sqrtHalf), r.direction);
		}

		TEST_METHOD(TestWorldWithCamera)
		{
			auto w = World::Default();
			auto c = Camera(11, 11, pi / 2);
			auto from = Tuple::point(0, 0, -5);
			auto to = Tuple::point(0, 0, 0);
			auto up = Tuple::vector(0, 1, 0);
			c.setTransform(viewTransform(from, to, up));

			auto image = c.render(w);

			Assert::AreEqual(Color(0.38066, 0.47583, 0.2855), image.at(5, 5));
		}
	};
}