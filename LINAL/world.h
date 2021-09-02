#pragma once
#include "Events.h"
#include "object_3d.h"

class world
{
public:
	world();
	std::vector<std::unique_ptr<object_3d>> objects;
	void update();
};

