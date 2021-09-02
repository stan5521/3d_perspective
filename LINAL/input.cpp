#include "input.h"
#include "viewer.h"
#include <SDL_events.h>
#include "events.h"

void input::handleEvents()
{
	SDL_Event event;
	std::vector<std::string> key_ups;
	std::vector<std::string> key_down;
	while (SDL_PollEvent(&event))
	{
		if( event.type == SDL_QUIT)
		{
			viewer::running = false;
		}
		if (event.type == SDL_KEYUP)
		{
			key_ups.emplace_back(std::string(SDL_GetKeyName(event.key.keysym.sym)));
		}
		if (event.type == SDL_KEYDOWN)
		{
			key_down.emplace_back(std::string(SDL_GetKeyName(event.key.keysym.sym)));
		}
	}
	
	if(!key_ups.empty())
	{
		// call all event listeners with the keys that have been pressed up
		on_key_up.call(key_ups);
	}

	if (!key_down.empty())
	{
		// call all event listeners with the keys that have been pressed down
		on_key_down.call(key_down);
	}
}