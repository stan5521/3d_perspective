#include "simple_cube.h"
#include <iostream>

simple_cube::simple_cube(vector4 start_position) : object_3d(lines(),points(), start_position)
{

}

std::vector<vector4> simple_cube::points()
{
	std::vector<vector4> points;

	points.emplace_back(10,10,10);
	points.emplace_back(10,10,0);
	points.emplace_back(10,0,10);
	points.emplace_back(10,0,0);

	points.emplace_back(0,10,10);
	points.emplace_back(0,10,0);
	points.emplace_back(0,0,10);
	points.emplace_back(0,0,0);

	return points;
}

std::vector<line3d> simple_cube::lines()
{
	std::vector<line3d> lines;
	//square 1
	lines.push_back({ {0,0,0},{0,10,0} });
	lines.push_back({ {0,10,0},{10,10,0} });
	lines.push_back({ {0,0,0},{10,0,0} });
	lines.push_back({ {10,0,0},{10,10,0} });

	//square 2
	lines.push_back({ {0,0,10},{0,10,10} });
	lines.push_back({ {0,10,10},{10,10,10} });
	lines.push_back({ {0,0,10},{10,0,10} });
	lines.push_back({ {10,0,10},{10,10,10} });

	// lines between square
	lines.push_back({ {0,0,0},{0,0,10} });
	lines.push_back({ {10,10,0},{10,10,10} });
	lines.push_back({ {0,10,0},{0,10,10} });
	lines.push_back({ {10,0,0},{10,0,10} });

	return lines;
}

void simple_cube::update()
{
	updateDelay++;

	// waiting a bit because we do not use deltaTime
	if (updateDelay % 4 == 0)
	{

		if (increasing_scale && scale_counter < 200)
		{
			object_scale = scale_increase;
			scale_counter++;
			if (scale_counter == 200)
			{
				increasing_scale = false;
			}
		}
		else if (!increasing_scale && scale_counter > 0)
		{
			object_scale = scale_decrease;
			scale_counter--;
			if (scale_counter == 0)
			{
				increasing_scale = true;
			}
		}

		const auto scale = matrix::scale(object_scale, object_scale, object_scale);
		for (auto& point : object_3d::points)
		{
			point.transform(scale);
		}

		for (auto& point : object_3d::lines)
		{
			point.point1.transform(scale);
			point.point2.transform(scale);
		}
	}
}
