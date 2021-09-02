#include "basic_math.h"
#include <complex>

double basic_math::deg_to_rad(double degree)
{
	return  degree * (3.14159265358979323846264338327950288 / 180);
}

double basic_math::rad_to_deg(double rad)
{
	return rad * 180.0 / 3.14159265358979323846264338327950288;
}

double basic_math::pythagoras(double adj, double opp)
{
	return sqrt(pow(adj, 2) + pow(opp, 2));
}