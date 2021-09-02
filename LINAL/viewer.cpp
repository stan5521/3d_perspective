#include "viewer.h"
#include <SDL.h>
#include "camera.h"
#include "line.h"
#include "line3d.h"

SDL_Renderer* viewer::renderer = nullptr;
SDL_Window* viewer::window = nullptr;
bool viewer::running = true;
color viewer::draw_color {0,0,0,255};
input viewer::input;

viewer::viewer()
{
	// init sdl window and renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	
    window = SDL_CreateWindow("LINAL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1024,
		1024,
		SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
	
	start_loop();
}

void viewer::start_loop()
{
	// loop for each frame
	while (running)
	{
		input.handleEvents();
		update();
		render();
	}
}

void viewer::update()
{
	world.update();
}

void viewer::render()
{
	SDL_RenderClear(renderer);

	// get camera matrix 
	const auto mat = cam.get_camera_matrix();

	for (auto& obj : world.objects)
	{
		for (auto& i : obj->lines)
		{
			// change local points to world coordinates
			draw_line(i.point1 + obj->position, i.point2 + obj->position, mat, color{ 255,255,0,255 });
		}

		draw_line(obj->position, obj->position + obj->x_axis, mat, color{ 255,0,0,255 });
		draw_line(obj->position, obj->position + obj->y_axis, mat, color{ 0,255,0,255 });
		draw_line(obj->position, obj->position + obj->z_axis, mat, color{ 0,0,255,255 });
	}

	SDL_RenderPresent(renderer);
}

void viewer::draw_line(vector4 p1, vector4 p2, matrix mat, color c) const
{
	// use the camera matrix on the to change the 3d point to 2d point on screen
	const vector4 begin = p1.transform_copy(mat);
	const vector4 end = p2.transform_copy(mat);

	// calculation to get the W limit values
	const auto w_value_f = cam.far * cam.near;
	const auto w_value_n = cam.near * cam.near;

	// If W value is between the near W value and the far W value
	if (begin.w > w_value_n && end.w > w_value_n && begin.w < w_value_f && end.w < w_value_f)
	{
		// Create line and draw it
		line l{
			{ 512 + (begin.x / begin.w) * 512 ,512 + (begin.y / begin.w) * 512},
			{ 512 + (end.x / end.w) * 512 ,512 + (end.y / end.w) * 512},
			1,c };
		l.draw();
	}
}

color viewer::get_draw_color()
{
	return draw_color;
}

void viewer::set_draw_color(color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
