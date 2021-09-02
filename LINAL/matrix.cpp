#include "matrix.h"
#include <iostream>
#include "basic_math.h"
#include "vector4.h"

void matrix::print()
{
    for (auto& i : graph)
    {
        for (double k : i)
        {
            std::cout << k << " ";
        }
        std::cout << "\n";
    }
}

matrix::matrix(const std::vector<std::vector<double>>& graph)
{
    this->graph = graph;
}

matrix::matrix(int rows, int cols, double default_value)
{
    graph.resize(rows);

    for (auto& i : graph)
    {
	    i.resize(cols, default_value);
    }
}

std::vector<double>& matrix::operator[](int row)
{
    return graph[row];
}

matrix matrix::operator-(matrix& other) const
{
    matrix result;
	
    const auto result_width = other.graph[0].size();
    const auto result_height = graph.size();

    result.graph = std::vector<std::vector<double>>(result_height, std::vector<double>(result_width, 0));
    for (size_t i = 0; i < graph.size(); i++)
    {
        for (size_t k = 0; k < graph[i].size(); k++)
        {
            result.graph[i][k] = graph[i][k] - other.graph[i][k];
        }
    }
	
    return result;
}

matrix matrix::operator+(matrix& other) const
{
    matrix result;

    const auto result_width = other.graph[0].size();
    const auto result_height = graph.size();

    result.graph = std::vector<std::vector<double>>(result_height, std::vector<double>(result_width, 0));
	
    for (size_t i = 0; i < graph.size(); i++)
    {
        for (size_t k = 0; k < graph[i].size(); k++)
        {
            result.graph[i][k] = graph[i][k] + other.graph[i][k];
        }
    }

    return result;
}

matrix matrix::operator*(matrix& other) const
{
    matrix result;

    const auto result_width = other.graph[0].size();
    const auto result_height = graph.size();

    result.graph = std::vector<std::vector<double>>(result_height, std::vector<double>(result_width, 0));

    for (size_t x = 0; x < result_width; x++)
    {
        for (size_t y = 0; y < result_height; y++)
        {
            for (size_t i = 0; i < graph[y].size(); i++)
            {
                result.graph[y][x] += graph[y][i] * other.graph[i][x];
            }
        }
    }

    return result;
}

bool matrix::operator==(matrix& other) const
{
    return other.graph == graph;
}

bool matrix::operator!=(matrix& other) const
{
    return other.graph == graph;
}

int matrix::rows() const
{
    return graph.size();
}

int matrix::cols()
{
    return graph[0].size();
}

matrix matrix::translation(double x , double y, double z)
{
    return { {
       {1,0,0,x},
       {0,1,0,y},
       {0,0,1,z},
       {0,0,0,1},
    } };
}

matrix matrix::translation(vector4 vec)
{
    return { {
       {1,0,0,vec.x},
       {0,1,0,vec.y},
       {0,0,1,vec.z},
       {0,0,0,1},
   } };
}

matrix matrix::scale(double x, double y, double z)
{
    return { {
       {x,0,0,0},
       {0,y,0,0},
       {0,0,z,0},
       {0,0,0,1},
    } };
}

matrix matrix::rotation_x(double deg)
{
	const auto rad = basic_math::deg_to_rad(deg);
	
    return { {
       {1,0,0,0},
       {0,cos(rad),-sin(rad),0},
       {0,sin(rad),cos(rad),0},
       {0,0,0,1},
   } };
}

matrix matrix::rotation_y(double deg)
{
    const auto rad = basic_math::deg_to_rad(deg);

    return { {
       {cos(rad),0,sin(rad),0},
       {0,1,0,0},
       {-sin(rad),0,cos(rad),0},
       {0,0,0,1},
    } };
}

matrix matrix::rotation_z(double deg)
{
    const auto rad = basic_math::deg_to_rad(deg);

    return { {
       {cos(rad),-sin(rad),0,0},
       {sin(rad),cos(rad),0,0},
       {0,0,1,0},
       {0,0,0,1},
    } };
}
