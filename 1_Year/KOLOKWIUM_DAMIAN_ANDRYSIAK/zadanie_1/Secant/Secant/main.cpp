#include <fstream>
#include <iomanip>
#include <iostream>


float f(const float x);

float f2(const float x, const float alpha)
{
	return std::cosh(x) - std::log10f(alpha * std::sqrtf(x));
}

int main(int argc, char* argv[])
{
	float E = 1e-06f;
	const float alpha = 19.f;
	float x1 = 0.3f;
	float x2 = 2.f;

	float y_x1 = f2(x1, alpha);
	float y_x2 = f2(x2, alpha);

	std::ofstream myfile;
	myfile.open("wynik.txt");

	std::cout << std::setprecision(15) << std::fixed;
	std::size_t iter = 0;
	myfile << "| Warunek stopu a) |\n";
	while (true)
	{
		//calculate a secant of f(x)
		const float x3 = ((y_x1 * x2) - (y_x2 * x1)) / (y_x1 - y_x2);
		const float y_x3 = f2(x3, alpha);
		if (std::fabs(y_x1 - y_x2) <= E)
		{
			break;
		}

		//std::cout << "f(" << x3 << ") = " << y_x2 << std::endl;

		std::cout << "Iteracja: " << iter << " | x: " << x3 << " | f = " << y_x2 << '\n';
		myfile << "Iteracja: " << iter << " | x: " << x3 << " | f = " << y_x2 << '\n';

		x1 = x2;
		x2 = x3;

		y_x1 = y_x2;
		y_x2 = y_x3;
		iter++;
	}
	std::cout << "\nf(" << x2 << ") = " << y_x2 << std::endl;
	myfile << "\nf(" << x2 << ") = " << y_x2 << std::endl;



	E = 1e-08f;
	x1 = 0.3f;
	x2 = 2.f;
	y_x1 = f2(x1, alpha);
	y_x2 = f2(x2, alpha);

	iter = 0;
	myfile << "\n| Warunek stopu b) |\n";
	while (true)
	{
		//calculate a secant of f(x)
		const float x3 = ((y_x1 * x2) - (y_x2 * x1)) / (y_x1 - y_x2);
		const float y_x3 = f2(x3, alpha);
		if (std::fabs(y_x3) <= E)
		{
			break;
		}

		//std::cout << "f(" << x3 << ") = " << y_x2 << std::endl;

		std::cout << "Iteracja: " << iter << " | x: " << x3 << " | f = " << y_x2 << '\n';
		myfile << "Iteracja: " << iter << " | x: " << x3 << " | f = " << y_x2 << '\n';

		x1 = x2;
		x2 = x3;

		y_x1 = y_x2;
		y_x2 = y_x3;

		iter++;
	}
	std::cout << "\nf(" << x2 << ") = " << y_x2 << std::endl;
	myfile << "\nf(" << x2 << ") = " << y_x2 << std::endl;

	myfile.close();
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