#pragma once
#include "object_3d.h"
#include "world.h"

class spaceship : public object_3d
{
public:
	spaceship(vector4 start_position, world& parent);
	std::vector<vector4> points();
	std::vector<line3d> lines();
	void update() override;
	void accelerate(double speed);
	void key_down(const std::vector<std::string>& input);
	void shoot() const;
private:
	world& parent;
	double movement_speed {0};
	double max_speed{ 2 };
};

