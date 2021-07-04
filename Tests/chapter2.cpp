#include "pch.h"
#include "CppUnitTest.h"
#include "../RaytracerChallenge/color.h"
#include "../RaytracerChallenge/math.h"
#include "../RaytracerChallenge/canvas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Chapter2Color)
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
			Assert::IsTrue(areEqual(Color(1.6, 0.7, 1.0), c1 + c2));
		}

		TEST_METHOD(TestSubtract)
		{
			auto c1 = Color(0.9, 0.6, 0.75);
			auto c2 = Color(0.7, 0.1, 0.25);
			Assert::IsTrue(areEqual(Color(0.2, 0.5, 0.5), c1 - c2));
		}

		TEST_METHOD(TestMultiplyScalar)
		{
			auto c = Color(0.2, 0.3, 0.4);
			Assert::IsTrue(areEqual(Color(0.4, 0.6, 0.8), c * 2));
		}

		TEST_METHOD(TestMultiply)
		{
			auto c1 = Color(1, 0.2, 0.4);
			auto c2 = Color(0.9, 1, 0.1);
			Assert::IsTrue(areEqual(Color(0.9, 0.2, 0.04), c1 * c2));
		}
	};

	TEST_CLASS(Chapter2Canvas)
	{
	public:
		TEST_METHOD(TestCanvasConstructor)
		{
			auto c = Canvas(10, 20);

			Assert::AreEqual(10ull, c.width);
			Assert::AreEqual(20ull, c.height);
		}

		TEST_METHOD(TestCanvasWrite)
		{
			auto c = Canvas(10, 20);
			auto red = Color(1, 0, 0);

			c.writePixel(2, 3, red);

			Assert::IsTrue(areEqual(c.at(2, 3), red));
		}

		TEST_METHOD(TestCanvasPpmHeader)
		{
			auto c = Canvas(5, 3);

			std::string ref = "P3\n"
				"5 3\n"
				"255\n";

			std::string ppm = c.getPPM();

			int off = 0;
			for (int i = 0; i < 3; i++)
				off = ppm.find('\n', off + 1);

			Assert::AreEqual(ref, ppm.substr(0, off + 1));
		}

		TEST_METHOD(TestCanvasPpmData)
		{
			auto c = Canvas(5, 3);
			auto c1 = Color(1.5, 0, 0);
			auto c2 = Color(0, 0.5, 0);
			auto c3 = Color(-0.5, 0, 1);

			c.writePixel(0, 0, c1);
			c.writePixel(2, 1, c2);
			c.writePixel(4, 2, c3);

			std::string ref = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
				"0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
				"0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n";

			std::string ppm = c.getPPM();

			int off = 0;
			for (int i = 0; i < 3; i++)
				off = ppm.find('\n', off + 1);

			Assert::AreEqual(ref, ppm.substr(off + 1));
		}

		TEST_METHOD(TestCanvasPpmLineBreak)
		{
			auto c = Canvas(10, 2);
			auto c1 = Color(1, 0.8, 0.6);

			for (int y = 0; y < 2; y++)
				for (int x = 0; x < 10; x++)
					c.writePixel(x, y, c1);

			std::string ref = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
				"153 255 204 153 255 204 153 255 204 153 255 204 153\n"
				"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
				"153 255 204 153 255 204 153 255 204 153 255 204 153 \n";

			std::string ppm = c.getPPM();

			int off = 0;
			for (int i = 0; i < 3; i++)
				off = ppm.find('\n', off + 1);

			Assert::AreEqual(ref, ppm.substr(off + 1));
		}

		TEST_METHOD(TestCanvasPpmNewLineEnd)
		{
			auto c = Canvas(5, 3);

			std::string ref = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 \n"
				"153 255 204 153 255 204 153 255 204 153 255 204 153 \n"
				"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 \n"
				"153 255 204 153 255 204 153 255 204 153 255 204 153 \n";

			std::string ppm = c.getPPM();

			Assert::IsTrue(ppm.ends_with("\n"));
		}
	};
}