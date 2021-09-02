#pragma once
#include <utility>
#include <vector>
#include "axis.h"
#include "line3d.h"

class object_3d
{
public:
	virtual ~object_3d() = default;
	object_3d(std::vector<line3d> lines, std::vector<vector4> points, vector4 position) : position(position), lines(std::move(lines)), points(std::move(points)) { center_lines(); }
	vector4 position;
	vector4 x_axis {1,0,0};
	vector4 y_axis {0,1,0};
	vector4 z_axis {0,0,1};
	std::vector<line3d> lines;
	std::vector<vector4> points;
	virtual void update() = 0;
	void rotate(double deg, axis axis);
	void apply_matrix(matrix m);
	vector4 get_center();
	void center_lines();
};
