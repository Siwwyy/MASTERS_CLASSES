#include <fstream>
#include <iomanip>
#include <iostream>


float f(const float x);
float df(const float x);

float f2(const float x, const float alpha)
{
	return std::cosh(x) - std::log10f(alpha * std::sqrtf(x));
}

float d_f2(const float x, const float alpha)
{
	return std::sinhf(x) - (19.f * std::sqrtf(x)) / (2.f * std::sqrtf(x) * 19.f * std::sqrtf(x));
}

int main(int argc, char* argv[])
{
	const float E = 1e-06f;
	const float alpha = 19.f;
	float x0 = 0.3f;

	float f_x0{};
	float f_x0_prim{};
	float x1{};


	std::ofstream myfile;
	myfile.open("wynik.txt");

	std::cout << std::setprecision(15) << std::fixed;
	std::size_t iter = 0;
	while (true)
	{
		//calculate the tangent of f(x)
		f_x0 = f2(x0, alpha);

		//std::cout << "f(" << x0 << ") = " << f_x0 << std::endl;

		std::cout << "Iteracja: " << iter << " | x: " << x0 << " | f = " << f_x0 << '\n';
		myfile << "Iteracja: " << iter << " | x: " << x0 << " | f = " << f_x0 << '\n';

		if(std::fabs(f_x0) < E)
		{
			break;
		}

		f_x0_prim = d_f2(x0, alpha);
		x1 = x0;
		x0 -= f_x0 / f_x0_prim;


		if(std::fabs(x1 - x0) < E)
		{
			break;
		}

		iter++;

	}

	std::cout << "f(" << x0 << ") = " << f_x0 << std::endl;
	myfile << "f(" << x0 << ") = " << f_x0 << std::endl;
	myfile.close();

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