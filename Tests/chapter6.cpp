#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/ray.h"
#include "../RaytracerChallenge/primitive.h"
#include "../RaytracerChallenge/intersection.h"
#include "../RaytracerChallenge/color.h"
#include "../RaytracerChallenge/light.h"
#include "../RaytracerChallenge/material.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter6Normals)
	{
	public:

		TEST_METHOD(TestSphereNormalX)
		{
			auto s = Sphere();

			auto n = s.normal(Tuple::point(1, 0, 0));

			Assert::AreEqual(Tuple::vector(1, 0, 0), n);
		}

		TEST_METHOD(TestSphereNormalY)
		{
			auto s = Sphere();

			auto n = s.normal(Tuple::point(0, 1, 0));

			Assert::AreEqual(Tuple::vector(0, 1, 0), n);
		}

		TEST_METHOD(TestSphereNormalZ)
		{
			auto s = Sphere();

			auto n = s.normal(Tuple::point(0, 0, 1));

			Assert::AreEqual(Tuple::vector(0, 0, 1), n);
		}

		TEST_METHOD(TestSphereNormal)
		{
			auto s = Sphere();

			auto n = s.normal(Tuple::point(sqrtf(3) / 3, sqrtf(3) / 3, sqrtf(3) / 3));

			Assert::AreEqual(n, normalize(n));
		}

		TEST_METHOD(TestTranslatedSphereNormal)
		{
			auto s = Sphere();
			s.transform = translation(0, 1, 0);

			auto n = s.normal(Tuple::point(0, 1.70711, -0.70711));

			Assert::AreEqual(Tuple::vector(0, 0.70711, -0.70711), n);
		}

		TEST_METHOD(TestTransformedSphereNormal)
		{
			auto s = Sphere();
			auto m = scaling(1, 0.5, 1) * rotationZ(pi / 5.f);
			s.transform = m;

			auto n = s.normal(Tuple::point(0, sqrtHalf, -sqrtHalf));

			Assert::AreEqual(Tuple::vector(0, 0.97014, -0.24254), n);
		}
	};

	TEST_CLASS(Chapter6Reflection)
	{
	public:
		TEST_METHOD(TestReflect45Deg)
		{
			auto v = Tuple::vector(1, -1, 0);
			auto n = Tuple::vector(0, 1, 0);

			auto r = reflect(v, n);

			Assert::AreEqual(Tuple::vector(1, 1, 0), r);
		}

		TEST_METHOD(TestReflectSlated)
		{
			auto v = Tuple::vector(0, -1, 0);
			auto n = Tuple::vector(sqrtHalf, sqrtHalf, 0);

			auto r = reflect(v, n);

			Assert::AreEqual(Tuple::vector(1, 0, 0), r);
		}
	};

	TEST_CLASS(Chapter6Materials)
	{
	public:

		TEST_METHOD(TestDefaultMaterial)
		{
			auto m = Material();

			Assert::AreEqual(Color(1, 1, 1), m.color);
			Assert::IsTrue(areEqual(0.1f, m.ambient));
			Assert::IsTrue(areEqual(0.9f, m.diffuse));
			Assert::IsTrue(areEqual(0.9f, m.specular));
			Assert::IsTrue(areEqual(200.f, m.shininess));
		}

		TEST_METHOD(TestShapeDefaultMaterial)
		{
			auto s = Sphere();

			auto m = s.material;

			Assert::AreEqual(Material(), m);
		}

		TEST_METHOD(TestShapeAssignMaterial)
		{
			auto s = Sphere();
			auto m = Material();
			m.ambient = 1.f;

			s.material = m;

			Assert::AreEqual(m, s.material);
		}

	};

	TEST_CLASS(Chapter6LightAndShading)
	{
	public:

		TEST_METHOD(TestPointLight)
		{
			auto intensity = Color(1, 1, 1);
			auto position = Tuple::point(0, 0, 0);

			auto light = PointLight(position, intensity);

			Assert::AreEqual(position, light.position);
			Assert::AreEqual(intensity, light.intensity);
		}

		TEST_METHOD(TestLighting)
		{
			auto m = Material();
			auto position = Tuple::point(0, 0, 0);
			auto eyev = Tuple::vector(0, 0, -1);
			auto normalv = Tuple::vector(0, 0, -1);
			auto light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));

			auto result = m.lighting(light, position, eyev, normalv);

			Assert::AreEqual(Color(1.9, 1.9, 1.9), result);
		}

		TEST_METHOD(TestLightingEyeOffset)
		{
			auto m = Material();
			auto position = Tuple::point(0, 0, 0);
			auto eyev = Tuple::vector(0, sqrtHalf, -sqrtHalf);
			auto normalv = Tuple::vector(0, 0, -1);
			auto light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));

			auto result = m.lighting(light, position, eyev, normalv);

			Assert::AreEqual(Color(1.0, 1.0, 1.0), result);
		}

		TEST_METHOD(TestLightingLightOffset)
		{
			auto m = Material();
			auto position = Tuple::point(0, 0, 0);
			auto eyev = Tuple::vector(0, 0, -1);
			auto normalv = Tuple::vector(0, 0, -1);
			auto light = PointLight(Tuple::point(0, 10, -10), Color(1, 1, 1));

			auto result = m.lighting(light, position, eyev, normalv);

			Assert::AreEqual(Color(0.7364, 0.7364, 0.7364), result);
		}

	};


}