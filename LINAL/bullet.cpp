#include "bullet.h"

std::vector<vector4> bullet::points()
{
	auto points = {
		vector4{0,0,0},
		vector4{0,0.5,0},
		vector4{0.5,0.5,0},
		vector4{0.5,0,0},

		vector4{0,0,1.5},
		vector4{0,0.5,1.5},
		vector4{0.5,0.5,1.5},
		vector4{0.5,0,1.5},
	};

	return points;
}

std::vector<line3d> bullet::lines()
{
	auto lines = {
		line3d{{0,0,0},{0.5,0,0}},
		line3d{{0,0,0},{0,0.5,0}},
		line3d{{0.5,0.5,0},{0,0.5,0}},
		line3d{{0.5,0.5,0},{0.5,0,0}},

		line3d{{0,0,1.5},{0.5,0,1.5}},
		line3d{{0,0,1.5},{0,0.5,1.5}},
		line3d{{0.5,0.5,1.5},{0,0.5,1.5}},
		line3d{{0.5,0.5,1.5},{0.5,0,1.5}},

		line3d{{0,0,0},{0,0,1.5}},
		line3d{{0.5,0,0},{0.5,0,1.5}},
		line3d{{0,0.5,0},{0,0.5,1.5}},
		line3d{{0.5,0.5,0},{0.5,0.5,1.5}},
	};

	return lines;
}

void bullet::update()
{
	// move in the direction of the negative z axis which is forward for this object
	position.transform(matrix::translation(z_axis * -movement_speed));
}
