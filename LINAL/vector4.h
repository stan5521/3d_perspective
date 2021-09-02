#pragma once
#include "matrix.h"

class vector4
{
public:
	double x {0};
	double y {0};
	double z {0};
	double w {1};
	
	vector4() = default;
	vector4(double x, double y, double z) : x{ x }, y{ y }, z{ z } {}

	vector4 cross(const vector4& other) const;
	double dot(const vector4& other) const;
	void normalize();

	vector4 operator-(const vector4& other) const;
	vector4 operator+(const vector4& other) const;
	vector4 operator*(double scalar) const;

	vector4 transform_copy(matrix matrix) const;
	void transform(matrix matrix);
};
