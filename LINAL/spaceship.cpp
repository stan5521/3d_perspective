#include "spaceship.h"
#include "bullet.h"
#include "viewer.h"
#include "SDL.h"
#include "world.h"

spaceship::spaceship(vector4 start_position, world& world) : object_3d(lines(), points(), start_position), parent(world)
{
	// register to the key_down event
	viewer::input.on_key_down += [this](const std::vector<std::string>& keys) {key_down(keys); };
}

std::vector<vector4> spaceship::points()
{
	std::vector<vector4> points;

	points.emplace_back(0,0,0);
	points.emplace_back(0,8,0);
	points.emplace_back(8,8,0);
	points.emplace_back(8,0,0);

	points.emplace_back(0,0,20);
	points.emplace_back(8,8,20);
	points.emplace_back(0,0,20);
	points.emplace_back(8,0,20);

	return points;
}

std::vector<line3d> spaceship::lines()
{
	std::vector<line3d> lines;

	//square 1
	lines.push_back({ {0,0,0},{0,8,0} });
	lines.push_back({ {0,8,0},{8,8,0} });
	lines.push_back({ {0,0,0},{8,0,0} });
	lines.push_back({ {8,0,0},{8,8,0} });

	//wing right
	lines.push_back({ {0,0,20},{-12,4,20} });
	lines.push_back({ {0,8,20},{-12,4,20} });
	lines.push_back({ {0,4,0},{-12,4,20} });

	//wing left
	lines.push_back({ {8,0,20},{20,4,20} });
	lines.push_back({ {8,8,20},{20,4,20} });
	lines.push_back({ {8,4,0},{20,4,20} });

	//square 2
	lines.push_back({ {0,0,20},{0,8,20} });
	lines.push_back({ {0,8,20},{8,8,20} });
	lines.push_back({ {0,0,20},{8,0,20} });
	lines.push_back({ {8,0,20},{8,8,20} });

	// lines between square
	lines.push_back({ {0,0,0},{0,0,20} });
	lines.push_back({ {8,8,0},{8,8,20} });
	lines.push_back({ {0,8,0},{0,8,20} });
	lines.push_back({ {8,0,0},{8,0,20} });

	return lines;
}

void spaceship::update()
{
	const auto* const key_state = SDL_GetKeyboardState(NULL);

	if (key_state[SDL_SCANCODE_LSHIFT])
	{
		accelerate(-0.005);
	}
	
	if (key_state[SDL_SCANCODE_LCTRL])
	{
		accelerate(0.005);
	}
	
	if (key_state[SDL_SCANCODE_W])
	{
		rotate(1, axis::X_AXIS);
	}

	if (key_state[SDL_SCANCODE_Q])
	{
		rotate(-1, axis::Z_AXIS);
	}

	if (key_state[SDL_SCANCODE_S])
	{
		rotate(-1, axis::X_AXIS);
	}

	if (key_state[SDL_SCANCODE_E])
	{
		rotate(1, axis::Z_AXIS);
	}

	if (key_state[SDL_SCANCODE_A])
	{
		rotate(1, axis::Y_AXIS);
	}

	if (key_state[SDL_SCANCODE_D])
	{
		rotate(-1, axis::Y_AXIS);
	}
	// move spaceship forward in the z direction which is forward for this object
	position.transform(matrix::translation( z_axis * movement_speed));
}

void spaceship::accelerate(double speed)
{
	movement_speed += speed;
}

void spaceship::key_down(const std::vector<std::string>& input)
{
	for (const auto& key : input)
	{
		if(key == "Space")
		{
			shoot();
		}
		if (key == "Z")
		{
			movement_speed = 0;
		}
	}
}

void spaceship::shoot() const
{
	// create bullet on the position of the tip of the spaceship
	auto ptr = std::make_unique<bullet>(position + z_axis * -10);

	// set the rotation of the bullet
	ptr->x_axis = x_axis;
	ptr->y_axis = y_axis;
	ptr->z_axis = z_axis;

	//add movement speed of the spaceship
	ptr->movement_speed += -movement_speed;

	//push to world
	parent.objects.push_back(std::move(ptr));
}
