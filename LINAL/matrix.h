#pragma once
#include <vector>
class vector4;

class matrix
{
public:
	void print();
	
	matrix() = default;
	matrix(const std::vector<std::vector<double>>& graph);
	matrix(int rows, int cols, double default_value = 0);

	std::vector<double>& operator[](int row);

	matrix operator+(matrix& other) const;
	matrix operator-(matrix& other) const;
	matrix operator*(matrix& other) const;
	bool operator==(matrix& other) const;
	bool operator!=(matrix& other) const;

	int rows() const;
	int cols();
	static matrix translation(double x, double y, double z);
	static matrix translation(vector4 vec);
	static matrix scale(double x, double y, double z);
	static matrix rotation_x(double deg);
	static matrix rotation_y(double deg);
	static matrix rotation_z(double deg);
private:
	std::vector<std::vector<double>> graph{};
};
