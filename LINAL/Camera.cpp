#include "camera.h"
#include <SDL.h>
#include "viewer.h"

camera::camera()
{
	scale = near * tan(field_of_view / 180 * 0.5 * M_PI);

	// 50 units away
	eye = {0, 0,50};
	look_at = {0, 0, -1};
	// Standard up vector
	up = {0,1,0};

	// default up, right and direction calculation
	direction = eye - look_at;
	direction.normalize();

	// determine right vector perpendicular from direction
	right = up.cross(direction);
	right.normalize();

	// determine up vector perpendicular from right
	up = direction.cross(right);
	up.normalize();

	viewer::input.on_key_down += [this](const std::vector<std::string>& keys)
	{
		for (const auto& key : keys)
		{
			if (key == "Up")
			{
				move_forward();
			}
			if (key == "Down")
			{
				move_backward();
			}
			if (key == "Left")
			{
				move_left();
			}
			if (key == "Right")
			{
				move_right();
			}
			if (key == "PageDown")
			{
				move_up();
			}
			if (key == "PageUp")
			{
				move_down();
			}
		}
	};
}

void camera::move_forward()
{
	eye = eye - direction * movement_speed;
}

void camera::move_backward()
{
	eye = eye + direction * movement_speed;
}

void camera::move_left()
{
	eye = eye - right * movement_speed;
}

void camera::move_right()
{
	eye = eye + right * movement_speed;
}

void camera::move_up()
{
	eye = eye - up * movement_speed;
}

void camera::move_down()
{
	eye = eye + up * movement_speed;
}

matrix camera::get_projection_matrix() const
{
	// from presentation
	matrix m = {
		{
			{scale, 0, 0, 0},
			{0, scale, 0, 0},
			{0, 0, -far / (far - near), -1},
			{0, 0, -far * near / (far - near), 0}
		}
	};

	return m;
}

matrix camera::get_camera_matrix() const
{
	// from presentation
	auto m1 = get_projection_matrix();
	auto m2 = get_transformation_matrix();

	// naar de oorpsrong
	auto m3 = matrix::translation(-eye.x, -eye.y, -eye.z);

	return m1 * m2 * m3;	
}

matrix camera::get_transformation_matrix() const
{
	// from presentation
	return {
		{
			{right.x,right.y,right.z,0},
			{up.x,up.y,up.z,0},
			{direction.x,direction.y,direction.z,0},
			{0,0,0,1.0},
		}
	};
}
