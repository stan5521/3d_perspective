#pragma once
#include <xstring>
#include "Point.h"
#include "Color.h"

class line
{
public:
	line(point from, point to, int radius, color color) : from(from), to(to), radius(radius), draw_color(color) { }
	point from;
	point to;
	int radius;
	color draw_color;
	void draw();
	void addThickness(std::string& direction, int distance, bool isUpperPart) const;
};