#include <iomanip>
#include <iostream>


float f(const float x);
float df(const float x);

int main(int argc, char* argv[])
{
	float E = 0.00001f;
	float x0 = -8.f;

	std::cout << std::setprecision(15) << std::fixed;

	float f_x0{};
	float f_x0_prim{};
	float x1{};

	while (true)
	{
		//calculate the tangent of f(x)
		f_x0 = f(x0);

		std::cout << "f(" << x0 << ") = " << f_x0 << std::endl;

		if(std::fabs(f_x0) < E)
		{
			break;
		}

		f_x0_prim = df(x0);
		x1 = x0;
		x0 -= f_x0 / f_x0_prim;


		if(std::fabs(x1 - x0) < E)
		{
			break;
		}
	}

	std::cin.get();
	return EXIT_SUCCESS;
}

float f(const float x)
{
	return std::exp(-1.f * std::atan(x)) - x;
}

float df(const float x)
{
	return -1.f * (std::exp(-1.f * std::atan(x)) / (std::powf(x, 2.f) + 1.f)) - 1.f;
}