
#include <iostream>
#include <cstdlib>
#include <functional>
#include <random>
#include <vector>

#include "Point.hpp"


template <typename T>
T function_3D(Point<T, 3> cords);

template <typename T>
T function_4D(Point<T, 4> cords);


template <std::size_t nDim>
class Hook_Jeeves_Method
{
public:

	Hook_Jeeves_Method();
	Hook_Jeeves_Method(const Hook_Jeeves_Method& Object) = default;
	~Hook_Jeeves_Method() = default;

	void run();


private:

	void generate_points();

	void work_cycle(const Point<float, nDim>& x_b,
		Point<float, nDim>& x_b0,
		std::size_t& i,
		std::size_t& j);

	const float E;
	std::vector<Point<float, nDim>> points;
	std::function<float(Point<float, nDim>)> function;
};




int main(int argc, char* argv[])
{
	Hook_Jeeves_Method<3> D;
	D.run();

	std::cin.get();
	return EXIT_SUCCESS;
}




template <typename T>
T function_3D(Point<T, 3> cords)
{
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(1);
	const T b = n * static_cast<T>(2);
	return std::pow<T>(a - cords[0], 2) + b * std::pow<T>(cords[1] - std::pow<T>(cords[0], 2), 2) + //k==1
		std::pow<T>(a - cords[1], 2) + b * std::pow<T>(cords[2] - std::pow<T>(cords[1], 2), 2); //k==2
}

template <typename T>
T function_4D(Point<T, 4> cords)
{
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(1);
	const T b = n;
	return std::pow<T>(a - cords[0], 2) + b * std::pow<T>(cords[1] - std::pow<T>(cords[0], 2), 2) + //k==1
		std::pow<T>(a - cords[1], 2) + b * std::pow<T>(cords[2] - std::pow<T>(cords[1], 2), 2) + //k==2
		std::pow<T>(a - cords[2], 2) + b * std::pow<T>(cords[3] - std::pow<T>(cords[2], 2), 2);//k==3
}




/*
 *
 * Hook-Jeaves class methods implementations
 *
 */




template <std::size_t nDim>
Hook_Jeeves_Method<nDim>::Hook_Jeeves_Method() :
	E(1e-06f),
	points({})
{
	points.reserve(nDim);
	generate_points();


	if constexpr (nDim == 3)
	{
		function = function_3D<float>;
	}
	else
	{
		function = function_4D<float>;
	}
}

template <std::size_t nDim>
void Hook_Jeeves_Method<nDim>::run()
{
	float delta = 0.5f;
	constexpr float beta = 0.2f;


	std::vector<Point<float, nDim>> move_turn{};

	for (std::size_t i = 0; i < nDim; ++i)
	{
		Point<float, nDim> temp;
		temp[i] = 1.f;
		move_turn.emplace_back(std::move(temp));
	}

	auto& x0 = points[0];
	auto& x_b0 = points[0];
	auto f0 = function(points[0]); //f(x0)

	std::size_t j = 1;
	bool condition = true;
	while (condition)
	{
		std::cout << function(x_b0) << '\n';
		std::cin.get();
		for (std::size_t i = 1; i < nDim; ++i)
		{
			auto& d_i = move_turn[i];
			auto z1 = x0;

			//2)
			z1 = points[i - 1] + d_i * delta;
			//3)
			if (function(z1) < f0)
			{
				f0 = function(z1);
			}
			else
			{
				//4)
				z1 = points[i - 1] + d_i * 2.f * delta;
				//5)
				if (function(z1) < f0)
				{
					f0 = function(z1);
				}
				else
				{
					continue;
				}
			}
			//6
			if (i < nDim - 1)
			{
				continue; //i + 1
			}
			if (i == nDim - 1)
			{
				if (f0 < function(x0))
				{
					const auto x_b = z1;
					//work_cycle
					work_cycle(x_b, x_b0, i, j);
				}
				else if (std::abs(f0 - function(x0)) < 0.f + E)
				{
					//a
					if (delta < E)
					{
						std::cout << "END\n";
						std::cout << function(points[j - 1]) << '\n';
						condition = false;
						break;
					}
					//b
					delta = delta * beta;
				}
			}

			//std::cout << function(points[j - 2]) << '\n';
			//std::cin.get();
		}

	}

}

template <std::size_t nDim>
void Hook_Jeeves_Method<nDim>::generate_points()
{
	std::random_device rand_device;
	std::mt19937 generator(rand_device());
	const std::uniform_real_distribution<float> distribution(-1.f, 2.f);
	for (std::size_t i = 0; i < nDim; ++i)
	{
		Point<float, nDim> temp_point{};
		for (std::size_t j = 0; j < nDim; ++j)
		{
			temp_point[j] = distribution(generator);
		}
		points.push_back(std::move(temp_point));
	}
}

template <std::size_t nDim>
void Hook_Jeeves_Method<nDim>::work_cycle(const Point<float, nDim>& x_b, Point<float, nDim>& x_b0, std::size_t& i, std::size_t& j)
{
	for (; j < nDim; ++j)
	{
		points[j] = x_b + (x_b - x_b0);
	}
	x_b0 = x_b;
	j = j + 1;
	i = 1;
}