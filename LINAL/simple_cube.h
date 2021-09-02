#pragma once
#include "object_3d.h"

class simple_cube : public object_3d
{
public:
	simple_cube(vector4 start_position);
	std::vector<vector4> points();
	std::vector<line3d> lines();
	void update() override;

private:
	double object_scale{ 1 };
	double scale_increase{ 1.0010 };
	double scale_decrease{ 0.9990 };

	int scale_counter{ 0 };
	bool increasing_scale{ true };
	int updateDelay{ 0 };
};

