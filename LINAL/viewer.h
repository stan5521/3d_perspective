#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include "camera.h"
#include "color.h"
#include "input.h"
#include "world.h"

class viewer
{
public:
	viewer();
	void start_loop();
	void update();
	void render();
	void draw_line(vector4 p1, vector4 p2, matrix mat, color c) const;

	static color get_draw_color();
	static void set_draw_color(color color);
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static bool running;
	static input input;
	camera cam;
	world world;

private:
	static  color draw_color;
};
