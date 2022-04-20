#include <iomanip>
#include <iostream>


float f(const float x);

int main(int argc, char* argv[])
{
	const float E = 1e-06f;
	float x1 = 1.f;
	float x2 = 2.f;


	float y_x1 = f(x1);
	float y_x2 = f(x2);

	std::cout << std::setprecision(15) << std::fixed;
	std::size_t iter = 0;
	while (true)
	{
		//calculate a secant of f(x)
		const float x3 = ((y_x1 * x2) - (y_x2 * x1)) / (y_x1 - y_x2);
		const float y_x3 = f(x3);

		//std::cout << "f(" << x3 << ") = " << y_x2 << std::endl;

		std::cout << "Iteracja: " << iter << " | x: " << x3 << " | f = " << y_x2 << '\n';

		if(std::fabs(y_x3) <= E)
		{
			break;
		}

		x1 = x2;
		x2 = x3;

		y_x1 = y_x2;
		y_x2 = y_x3;

		iter++;
	}
	std::cout << "\nf(" << x2 << ") = " << y_x2 << std::endl;
	std::cin.get();
	return EXIT_SUCCESS;
}

float f(const float x)
{
	//return std::exp(-1.f * std::atan(x)) - x;
	//return std::log(x) - sqrt(x);
	//return 2 * sinf(x) - std::log(x);
	//return std::powf(x, 2.f);
	return std::atan(std::log(std::powf(x, 3.f) + 1.f) - 3.f);
}