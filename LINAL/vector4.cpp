#include "vector4.h"

vector4 vector4::cross(const vector4& other) const
{
	vector4 vector{};

	vector.x = y * other.z - z * other.y;
	vector.y = z * other.x - x * other.z;
	vector.z = x * other.y - y * other.x;

	return vector;
}

double vector4::dot(const vector4& other) const
{
	return  x * other.x + y * other.y + z * other.z;
}

void vector4::normalize()
{
	const auto length = sqrt(x * x + y * y + z * z);
	x /= length;
	y /= length;
	z /= length;
}

vector4 vector4::operator-(const vector4& other) const
{
	vector4 vector{};

	vector.x = x - other.x;
	vector.y = y - other.y;
	vector.z = z - other.z;
	
	return vector;
}

vector4 vector4::operator+(const vector4& other) const
{
	vector4 vector{};

	vector.x = x + other.x;
	vector.y = y + other.y;
	vector.z = z + other.z;

	return vector;
}

vector4 vector4::operator*(const double scalar) const
{
	vector4 vector{};

	vector.x = x * scalar;
	vector.y = y * scalar;
	vector.z = z * scalar;

	return vector;
}

void vector4::transform(matrix matrix)
{
	const auto transform_x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3] * w;
	const auto transform_y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3] * w;
	const auto transform_z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3] * w;
	const auto transform_w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3] * w;

	x = transform_x;
	y = transform_y;
	z = transform_z;
	w = transform_w;
}

vector4 vector4::transform_copy(matrix matrix) const
{
	vector4 result{};

	result.x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3] * w;
	result.y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3] * w;
	result.z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3] * w;
	result.w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3] * w;
	
	return result;
}
