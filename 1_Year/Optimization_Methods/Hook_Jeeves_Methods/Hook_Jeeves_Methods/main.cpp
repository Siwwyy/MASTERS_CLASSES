
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

	const float E;
	std::vector<Point<float, nDim>> points;
	std::function<float(Point<float, nDim>)> function;
};

int main(int argc, char* argv[])
{
	Hook_Jeeves_Method<3> D;
	D.run();

	Hook_Jeeves_Method<4> D1;
	D1.run();

	std::cin.get();
	return EXIT_SUCCESS;
}




template <typename T>
T function_3D(Point<T, 3> cords)
{
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(1);
	const T b = n * static_cast<T>(2);
	return std::powf(a - cords[0], 2) + b * std::powf(cords[1] - std::powf(cords[0], 2), 2) + //k==1
		std::powf(a - cords[1], 2) + b * std::powf(cords[2] - std::powf(cords[1], 2), 2); //k==2
}

template <typename T>
T function_4D(Point<T, 4> cords)
{
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(1);
	const T b = n;
	return std::powf(a - cords[0], 2) + b * std::powf(cords[1] - std::powf(cords[0], 2), 2) + //k==1
		std::powf(a - cords[1], 2) + b * std::powf(cords[2] - std::powf(cords[1], 2), 2) + //k==2
		std::powf(a - cords[2], 2) + b * std::powf(cords[3] - std::powf(cords[2], 2), 2);//k==3
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
	points.resize(nDim);
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
	constexpr float beta = 0.2f;
	float delta = 0.5f;

	std::vector<Point<float, nDim>> di{};
	for (std::size_t i = 0; i < nDim; ++i)
	{
		Point<float, nDim> temp;
		temp[i] = 1.f;
		di.emplace_back(std::move(temp));
	}

	auto x0 = points[0];
	auto xb0 = x0;
	auto xb = x0;
	auto xb_prev = x0;
	std::size_t j = 0ull;
	while (true)
	{
		Point<float, nDim> zi{};
		float f0 = function(x0);
		for (std::size_t i = 0; i < nDim; ++i)
		{
			//2
			zi = x0 + (di[i] * delta);
			float f = function(zi);
			//3
			if (f < f0)
			{
				f0 = f;
				continue; //follow the loop, //6
			}
			//4
			zi = x0 - (di[i] * delta * 2.f);
			f = function(zi);
			//5
			if (f < f0)
			{
				f0 = f;
				//follow the loop, //6
			}
		}
		//7
		if (f0 < function(xb0))
		{
			xb_prev = xb;
			xb = zi;
			//8, working cycle
			auto new_base_point = xb * 2.f - xb0;
			xb0 = xb;
			x0 = new_base_point;
		}
		else
		{
			//a
			if (delta < E)
			{
				std::cout << "END\n";
				std::cout << x0 << '\n';
				std::cout << function(x0) << '\n';
				std::cout << '\n';
				break;
			}
			//b
			delta = beta * delta;
			x0 = xb_prev;
			xb0 = x0;
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
		points[i] = std::move(temp_point);
	}
}