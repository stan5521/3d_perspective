#include "world.h"
#include "simple_cube.h"
#include "spaceship.h"
#include "viewer.h"

world::world()
{
	auto cube1 = std::make_unique<simple_cube>(vector4{ 0,0,0 });
	cube1->apply_matrix(matrix::scale(0.1, 0.1, 0.1));
	objects.push_back(std::move(cube1));
	objects.push_back(std::make_unique<simple_cube>(vector4{ 20,20,-50 }));
	objects.push_back(std::make_unique<simple_cube>(vector4{ 0,20,-30 }));
	objects.push_back(std::make_unique<simple_cube>(vector4{ 60,0,-20 }));
	objects.push_back(std::make_unique<simple_cube>(vector4{ 40,10,-10 }));
	objects.push_back(std::make_unique<simple_cube>(vector4{ -180,40,-400 }));
	objects.push_back(std::make_unique<spaceship>(vector4{ 40,40,-20 }, *this));
}

void world::update()
{
	for (auto& obj : objects)
	{
		obj->update();
	}
}