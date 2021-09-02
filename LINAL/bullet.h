#pragma once
#include "object_3d.h"

class bullet : public object_3d
{
public:
	bullet(const vector4& position) : object_3d(lines(), points(), position) {}
	std::vector<vector4> points();
	std::vector<line3d> lines();
	void update() override;
	double movement_speed {0.5};
};

