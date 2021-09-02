#pragma once
#include "vector4.h"

class camera
{
public:
	camera();

	void move_forward();
	void move_backward();
	void move_left();
	void move_right();
	void move_up();
	void move_down();

	matrix get_projection_matrix() const;
	matrix get_camera_matrix() const;
	matrix get_transformation_matrix() const;

	double near{ 0.1 };
	double far{ 600.0 };

private:
	double field_of_view{ 100.0 };
	double scale;
	double movement_speed{ 2 };

	vector4 position;
	vector4 look_at;
	vector4 direction;
	vector4 eye;
	vector4 right;
	vector4 up;
};
