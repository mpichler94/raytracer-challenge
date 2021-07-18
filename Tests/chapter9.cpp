#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/shape.h"
#include "../RaytracerChallenge/material.h"
#include "../RaytracerChallenge/ray.h"
#include "../RaytracerChallenge/intersection.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class TestShape : public Shape
{
public:
	mutable Ray transformedRay;

	TestShape() : transformedRay(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 0)) {}

	virtual bool operator==(const Shape& rhs) const override { return false; }

	virtual std::wstring toString() const { return std::wstring(); }

private:
	virtual Intersections intersectIntenal(const Ray& r) const override { transformedRay = r; return Intersections(); }
	virtual Tuple normalInternal(const Tuple& point) const override { return Tuple::vector(point.x, point.y, point.z); }

};

namespace Tests
{
	TEST_CLASS(Chapter9AbstractShape)
	{
	public:

		TEST_METHOD(TestDefaultTransformation)
		{
			auto s = TestShape();

			Assert::AreEqual(Matrix<4, 4>::identity(), s.transform);
		}

		TEST_METHOD(TestAssignTransformation)
		{
			auto s = TestShape();

			s.transform = translation(2, 3, 4);

			Assert::AreEqual(translation(2, 3, 4), s.transform);
		}

		TEST_METHOD(TestDefaultMaterial)
		{
			auto s = TestShape();

			auto m = s.material;

			Assert::AreEqual(Material(), m);
		}

		TEST_METHOD(TestAssignMaterial)
		{
			auto s = TestShape();
			auto m = Material();
			m.ambient = 1;

			s.material = m;

			Assert::AreEqual(m, s.material);
		}

		TEST_METHOD(TestIntersectScaled)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto s = TestShape();

			s.transform = scaling(2, 2, 2);
			auto xs = s.intersect(r);

			Assert::AreEqual(Tuple::point(0, 0, -2.5), s.transformedRay.origin);
			Assert::AreEqual(Tuple::vector(0, 0, 0.5), s.transformedRay.direction);
		}

		TEST_METHOD(TestIntersectTranslated)
		{
			auto r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
			auto s = TestShape();

			s.transform = translation(5, 0, 0);
			auto xs = s.intersect(r);

			Assert::AreEqual(Tuple::point(-5, 0, -5), s.transformedRay.origin);
			Assert::AreEqual(Tuple::vector(0, 0, 1), s.transformedRay.direction);
		}

		TEST_METHOD(TestNormalTranslated)
		{
			auto s = TestShape();

			s.transform = translation(0, 1, 0);
			auto n = s.normal(Tuple::point(0, 1.70711, -0.70711));

			Assert::AreEqual(Tuple::vector(0, 0.70711, -0.70711), n);
		}

		TEST_METHOD(TestNormalTransformed)
		{
			auto s = TestShape();

			s.transform = scaling(1, 0.5, 1) * rotationZ(pi/5);
			auto n = s.normal(Tuple::point(0, sqrtHalf, -sqrtHalf));

			Assert::AreEqual(Tuple::vector(0, 0.97014, -0.24254), n);
		}

	};

	TEST_CLASS(Chapter9Plane)
	{
	public:

		TEST_METHOD(TestNormal)
		{
			auto p = Plane();

			auto n1 = p.normal(Tuple::point(0, 0, 0));
			auto n2 = p.normal(Tuple::point(10, 0, -10));
			auto n3 = p.normal(Tuple::point(-5, 0, 150));

			Assert::AreEqual(Tuple::vector(0, 1, 0), n1);
			Assert::AreEqual(Tuple::vector(0, 1, 0), n2);
			Assert::AreEqual(Tuple::vector(0, 1, 0), n3);
		}

		TEST_METHOD(TestIntersectParallel)
		{
			auto p = Plane();
			auto r = Ray(Tuple::point(0, 10, 0), Tuple::vector(0, 0, 1));

			auto xs = p.intersect(r);

			Assert::AreEqual(0ull, xs.count());
		}

		TEST_METHOD(TestIntersectCoplanar)
		{
			auto p = Plane();
			auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));

			auto xs = p.intersect(r);

			Assert::AreEqual(0ull, xs.count());
		}

		TEST_METHOD(TestIntersectFromAbove)
		{
			auto p = Plane();
			auto r = Ray(Tuple::point(0, 1, 0), Tuple::vector(0, -1, 0));

			auto xs = p.intersect(r);

			Assert::AreEqual(1ull, xs.count());
			Assert::AreEqual(1.f, xs[0].t);
			Assert::AreEqual(static_cast<const Shape*>(&p), xs[0].primitive);
		}

		TEST_METHOD(TestIntersectFromBelow)
		{
			auto p = Plane();
			auto r = Ray(Tuple::point(0, -1, 0), Tuple::vector(0, 1, 0));

			auto xs = p.intersect(r);

			Assert::AreEqual(1ull, xs.count());
			Assert::AreEqual(1.f, xs[0].t);
			Assert::AreEqual(static_cast<const Shape*>(&p), xs[0].primitive);
		}
	};
}