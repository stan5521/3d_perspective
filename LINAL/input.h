#pragma once
#include <vector>
#include <string>
#include "Events.h"

class input
{
public:
	void handleEvents();
	event<std::vector<std::string>> on_key_up;
	event<std::vector<std::string>> on_key_down;
};
