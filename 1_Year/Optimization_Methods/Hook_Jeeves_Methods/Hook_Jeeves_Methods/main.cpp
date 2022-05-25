
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
	points.resize(nDim);
	//points.reserve(nDim);
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
	//float delta = 0.5f;
	//constexpr float beta = 0.2f;

	//std::vector<Point<float, nDim>> move_turn{};
	//for (std::size_t i = 0; i < nDim; ++i)
	//{
	//	Point<float, nDim> temp;
	//	temp[i] = 1.f;
	//	move_turn.emplace_back(std::move(temp));
	//}

	//auto& x0 = points[0];
	//auto z1 = x0;
	//auto& x_b0 = points[0];
	//auto f0 = function(x0); //f(x0)
	//auto fb0 = function(x0); //f(x0)

	//std::size_t j = 0;
	//while (true)
	//{
	//	for (std::size_t i = 1; i < move_turn.size(); ++i)
	//	{
	//		//2
	//		points[i] = points[i - 1] + move_turn[i] * delta;
	//		auto f = function(z1);
	//		//3
	//		if (f < f0)
	//		{
	//			f0 = f;
	//			continue;//6
	//		}
	//		//4
	//		z1 = points[i - 1] - move_turn[i] * 2.f * delta;
	//		f = function(z1);
	//		//5
	//		if (f < f0)
	//		{
	//			f0 = f;
	//		}
	//		//6
	//	}
	//	//7
	//	if (f0 < function(x0))
	//	{
	//		auto x_b = z1;
	//		//8, working cycle
	//		x0 = x_b + (x_b - x_b0);
	//		x_b0 = x_b;
	//		++j;
	//	}
	//	else if (std::fabs(f0 - function(x0)) < 0.f + 0.1f) //f0 == function(x0) 
	//	{
	//		//a
	//		if (delta < E)
	//		{
	//			std::cout << function(x0) << '\n';
	//			std::cout << "END\n";
	//			break;
	//		}
	//		//b
	//		z1 = points[j];
	//		delta = delta * beta;
	//	}

	//	std::cout << function(x0) << '\n';
	//	std::cin.get();
	//}


	//std::vector<Point<float, nDim>> move_turn{};
	//for (std::size_t i = 0; i < nDim; ++i)
	//{
	//	Point<float, nDim> temp;
	//	temp[i] = 1.f;
	//	move_turn.emplace_back(std::move(temp));
	//}

	//Point<float, nDim> x0({ 1.f });

	//float lambda = 0.5f;
	//constexpr float beta = 0.2f;

	//auto x_b0 = x0;
	//while (true)
	//{
	//	float f_0 = function(x0);
	//	float f_b0 = f_0;
	//	Point<float, nDim> xn{};
	//	for (std::size_t i = 0; i < nDim; ++i)
	//	{
	//		//1
	//		auto x1 = x0 + move_turn[i] * lambda;
	//		xn = x1;
	//		float f_t = function(x1);
	//		//2
	//		if (f_t < f_0)
	//		{
	//			f_0 = f_t;
	//			break; //6 i++
	//		}
	//		//3
	//		x1 = x0 - move_turn[i] * lambda;
	//		xn = x1;
	//		f_t = function(x1);
	//		//4
	//		if (f_t < f_0)
	//		{
	//			f_0 = f_t;
	//		}
	//	}
	//	//7
	//	if (f_0 < f_b0)
	//	{
	//		auto xb = xn;
	//		float f_b = f_0;

	//		//working cycle
	//		x0 = xb + (xb - x_b0);
	//		f_0 = function(x0);
	//		x_b0 = xb;
	//		f_b0 = f_b;
	//	}
	//	//else if (std::fabs(f_0 - function(x0)) < 0.f + 0.1f) //f0 == function(x0)
	//	else
	//	{
	//		//9
	//		if (lambda < E)
	//		{
	//			std::cout << "x_b0: " << x_b0 << '\n';
	//			std::cout << "F: " << f_b0 << '\n';
	//			std::cout << "END\n";
	//			break;
	//		}
	//		//8
	//		x0 = x_b0;
	//		lambda = beta * lambda;
	//	}
	//	std::cout << "F: " << f_b0 << '\n';
	//	//std::cin.get();
	//}




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
				break; //6
			}
			//4
			zi = x0 - (di[i] * delta * 2.f);
			f = function(zi);
			//5
			if (f < f0)
			{
				f0 = f;
				break; //6
			}
		}
		//7
		if (f0 < function(x0))
		{
			auto xb = zi;
			//8, working cycle
			x0 = xb + (xb - xb0);
			xb0 = xb;
			j++;
		}
		else if (std::fabs(f0 - function(x0)) < 0.f + 0.1f) //if f0 == function(x0)
		{
			//a
			if (delta < E)
			{
				//std::cout << zi << '\n';
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "END\n";
				break;
			}
			//b
			generate_points();
			x0 = points[0];
			delta = beta * delta;
		}
		//std::cout << "F: " << f0 << '\n';
		//std::cin.get();
	}
	std::cout << "F: " << function(xb0) << '\n';
	std::cout << "Xb0: " << xb0 << '\n';
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