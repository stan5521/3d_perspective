#include "object_3d.h"
#include "axis.h"

void object_3d::rotate(double deg, axis axis)
{
	vector4 target;

	// determine the vector where the rotation will be used on
	switch (axis)
	{
	case axis::X_AXIS:
		target = x_axis;
		break;
	case axis::Y_AXIS:
		target = y_axis;
		break;
	case axis::Z_AXIS:
		target = z_axis;
		break;
	}

	auto& x = target.x;
	auto& y = target.y;
	auto& z = target.z;

	target.normalize();

	//1. Draai 𝑘 om de y - as naar het xy - vlak(z = 0)

	const auto sqr = sqrt(x * x + z * z);
	matrix m1;

	if (sqr > 0)
	{

		const auto cos_t1 = x / sqr;
		const auto sin_t1 = z / sqr;

		m1 = { {
			{cos_t1,0,sin_t1,0},
			{0,1,0,0},
			{-sin_t1,0,cos_t1,0},
			{0,0,0,1}
		} };
	}
	else
	{
		m1 = { {
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1}
		} };
	}

	//2. Draai 𝑘 om de z - as naar de x - as(z = 0 en y = 0)
	const auto cos_t2 = sqrt(x * x + z * z) / sqrt(x * x + y * y + z * z);
	const auto sin_t2 = y / sqrt(x * x + y * y + z * z);

	matrix m2{ {
		{cos_t2,sin_t2,0,0},
		{-sin_t2,cos_t2,0,0},
		{0,0,1,0},
		{0,0,0,1}
	} };

	//3. Voer de rotatie uit over de hoek 𝛼 om de x - as
	matrix m3 = matrix::rotation_x(deg);

	//4. Draai 𝑘 om de z - as terug, tegengesteld aan stap 2
	matrix m4{ {
		{cos_t2,-sin_t2,0,0},
		{sin_t2,cos_t2,0,0},
		{0,0,1,0},
		{0,0,0,1}
	} };

	//5. Draai 𝑘 om de y - as terug, tegengesteld aan stap 1
	matrix m5;
	if (sqr > 0)
	{

		const auto cos_t1 = x / sqr;
		const auto sin_t1 = z / sqr;

		m5 = { {
			{cos_t1,0,-sin_t1,0},
			{0,1,0,0},
			{sin_t1,0,cos_t1,0},
			{0,0,0,1}
		} };
	}
	else
	{
		m5 = { {
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1}
		} };
	}

	apply_matrix(m5 * m4 * m3 * m2 * m1);
}

void object_3d::apply_matrix(matrix m)
{
	// apply matrix to all points and lines
	for (auto& point : points)
	{
		point.transform(m);
	}
	
	for(auto& line : lines)
	{
		line.point1.transform(m);
		line.point2.transform(m);
	}

	// also transform the axis so they stay up to date
	x_axis.transform(m);
	y_axis.transform(m);
	z_axis.transform(m);
}


vector4 object_3d::get_center()
{
	// get the average vector of all the vectors combined
	double x{ 0 };
	double y{ 0 };
	double z{ 0 };

	for (auto& point : points)
	{
		x += point.x;
		y += point.y;
		z += point.z;
	}

	return { x / points.size(),y / points.size(),z / points.size() };
}

void object_3d::center_lines()
{
	// position all the lines around the center
	lines.push_back({ get_center(), get_center() + vector4{0.01, 0.01, 0.01} });
	
	for (auto& line : lines)
	{
		line.point1 = line.point1 - get_center();
		line.point2 = line.point2 - get_center();
	}	
}
