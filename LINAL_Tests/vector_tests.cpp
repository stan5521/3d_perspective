#include "pch.h"
#include "CppUnitTest.h"
#include "vector4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace vector_tests
{
	TEST_CLASS(vector_tests)
	{
	public:

		TEST_METHOD(VectorCreate)
		{
			double x = 5;
			double y = 4;
			double z = 3;
			vector4 vector{ x,y,z };

			Assert::AreEqual(x, vector.x);
			Assert::AreEqual(y, vector.y);
			Assert::AreEqual(z, vector.z);
		}

		TEST_METHOD(MatrixMulitplyVector)
		{
			vector4 vector{ 3,6,2 };

			matrix m{ {
				{2,0,0,0},
				{0,2,0,0},
				{0,0,2,0},
				{0,0,0,2},
			} };
			
			vector.transform(m);

			Assert::AreEqual(6.0, vector.x);
			Assert::AreEqual(12.0, vector.y);
			Assert::AreEqual(4.0, vector.z);
		}

		TEST_METHOD(CrossProduct)
		{
			vector4 vector{ 3,6,2 };

			auto result = vector.cross({ 3,3,3 });


			Assert::AreEqual(12.0, result.x);
			Assert::AreEqual(-3.0, result.y);
			Assert::AreEqual(-9.0, result.z);
		}

		TEST_METHOD(DotProduct)
		{
			vector4 vector{ 3,6,2 };

			auto result = vector.dot({ 3,3,3 });
			
			Assert::AreEqual(33.0, result);
		}
	};
}
