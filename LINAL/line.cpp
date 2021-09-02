#include "line.h"
#include <SDL_render.h>
#include <string>
#include "Point.h"
#include "viewer.h"

void line::draw()
{
	// draw a 2d line from one point to another
	if (radius == 0)
	{
		return;
	}

	const color clr = viewer::get_draw_color();
	viewer::set_draw_color(this->draw_color);

	const auto xDiff = to.x - from.x;
	const auto yDiff = to.y - from.y;

	const auto total = std::abs(xDiff) + std::abs(yDiff);
	const auto xPercentage = std::abs(xDiff) / total;

	std::string direction;

	if (xPercentage > 0.5)
	{
		direction = "horizontal";
	}
	else
	{
		direction = "vertical";
	}

	for (int i = 0; i < radius / 2; i++)
	{
		addThickness(direction, i + 1, false);
	}

	for (int i = radius / 2 + 1; i < radius; i++)
	{
		auto index = i - radius / 2;
		addThickness(direction, index, true);
	}

	SDL_RenderDrawLine(viewer::renderer, from.x, from.y, to.x, to.y);
	viewer::set_draw_color(clr);
}

void line::addThickness(std::string& direction, int distance, bool isUpperPart) const
{
	// add thickness to a single line
	point newFrom{ from.x , from.y };
	point newTo{ to.x, to.y };
	const auto increment = isUpperPart ? -1 : 1;

	if (direction == "horizontal")
	{
		newFrom.y = from.y + increment * distance;
		newTo.y = to.y + increment * distance;
	}
	else
	{
		newFrom.x = from.x + increment * distance;
		newTo.x = to.x + increment * distance;
	}
	SDL_RenderDrawLine(viewer::renderer, newFrom.x, newFrom.y, newTo.x, newTo.y);
}
