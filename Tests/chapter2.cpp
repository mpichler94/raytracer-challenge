#include "pch.h"
#include "CppUnitTest.h"
#include "../RaytracerChallenge/color.h"
#include "../RaytracerChallenge/math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter2)
	{
	public:

		TEST_METHOD(TestColorTuple)
		{
			auto c = Color(-0.5, 0.4, 1.7);

			Assert::IsTrue(areEqual(-0.5, c.r));
			Assert::IsTrue(areEqual(0.4, c.g));
			Assert::IsTrue(areEqual(1.7, c.b));
		}

		TEST_METHOD(TestAdd)
		{
			auto c1 = Color(0.9, 0.6, 0.75);
			auto c2 = Color(0.7, 0.1, 0.25);
			Assert::AreEqual(Color(1.6, 0.7, 1.0), c1 + c2);
		}

		TEST_METHOD(TestSubtract)
		{
			auto c1 = Color(0.9, 0.6, 0.75);
			auto c2 = Color(0.7, 0.1, 0.25);
			Assert::AreEqual(Color(0.2, 0.5, 0.5), c1 - c2);
		}

		TEST_METHOD(TestMultiply)
		{
			auto c = Color(0.2, 0.3, 0.4);
			Assert::AreEqual(Color(0.4, 0.6, 0.8), c * 2);
		}
	};
}