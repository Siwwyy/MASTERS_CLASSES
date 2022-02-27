#include <iomanip>
#include <iostream>


float f(const float x);

int main(int argc, char* argv[])
{
	float E = 0.00001f;
	float x1 = -8.f;
	float x2 = 8.f;

	std::cout << std::setprecision(15) << std::fixed;

	float y_x1 = f(x1);
	float y_x2 = f(x2);

	while (true)
	{
		//calculate a secant of f(x)
		const float x3 = ((y_x1 * x2) - (y_x2 * x1)) / (y_x1 - y_x2);
		const float y_x3 = f(x3);

		std::cout << "f(" << x3 << ") = " << y_x2 << std::endl;

		if(std::fabs(y_x3) < E)
		{
			break;
		}

		x1 = x2;
		x2 = x3;

		y_x1 = y_x2;
		y_x2 = y_x3;
	}

	std::cin.get();
	return EXIT_SUCCESS;
}

float f(const float x)
{
	return std::exp(-1.f * std::atan(x)) - x;
}