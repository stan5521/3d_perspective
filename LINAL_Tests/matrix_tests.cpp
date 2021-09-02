#include "pch.h"
#include "CppUnitTest.h"
#include "matrix.cpp"
#include "vector4.cpp"
#include "basic_math.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace matrix_tests
{
	TEST_CLASS(matrix_tests)
	{
	public:
		TEST_METHOD(MatrixMultiplication)
		{
			matrix m1{
				{
					{1,2,1,4},
					{1,2,1,4},
					{1,2,1,4},
					{1,2,1,4},
			} };
			
			matrix m2{
				{
				{1,2,3,4},
				{5,6,7,8},
				{1,2,3,4},
				{5,6,7,8},
			} };

			auto result = m1 * m2;

			Assert::AreEqual(32.0, result[0][0]);
			Assert::AreEqual(40.0, result[1][1]);
			Assert::AreEqual(48.0, result[2][2]);
			Assert::AreEqual(56.0, result[3][3]);
		}

		TEST_METHOD(MatrixSubtraction)
		{
			matrix m1{
					{
						{20,20},
						{20,20},
				} };

			matrix m2{
				{
				{4,5},
				{2,3},
			} };

			auto result = m1 - m2;
			Assert::AreEqual(16.0, result[0][0]);
			Assert::AreEqual(15.0, result[0][1]);
			Assert::AreEqual(18.0, result[1][0]);
			Assert::AreEqual(17.0, result[1][1]);
		}

		TEST_METHOD(MatrixAddition)
		{
			matrix m1{
					{
						{20,20},
						{20,20},
				} };

			matrix m2{
				{
				{4,5},
				{2,3},
			} };

			auto result = m1 + m2;
			Assert::AreEqual(24.0, result[0][0]);
			Assert::AreEqual(25.0, result[0][1]);
			Assert::AreEqual(22.0, result[1][0]);
			Assert::AreEqual(23.0, result[1][1]);
		}

		TEST_METHOD(MatrixTranslation)
		{
			matrix matrix = matrix::translation(10, 50, 30);

			Assert::AreEqual(10.0, matrix[0][3]);
			Assert::AreEqual(50.0, matrix[1][3]);
			Assert::AreEqual(30.0, matrix[2][3]);
		}

		TEST_METHOD(MatrixTranslationWithVector)
		{
			vector4 vector{ 10,50,30 };
			matrix matrix = matrix::translation(vector);

			Assert::AreEqual(10.0, matrix[0][3]);
			Assert::AreEqual(50.0, matrix[1][3]);
			Assert::AreEqual(30.0, matrix[2][3]);
		}

		TEST_METHOD(MatrixScale)
		{
			vector4 vector{ 10,50,30 };
			const auto scale = matrix::scale(2, 2, 2);
		
			vector.transform(scale);

			Assert::AreEqual(20.0, vector.x);
			Assert::AreEqual(100.0, vector.y);
			Assert::AreEqual(60.0, vector.z);
		}
	};
}
