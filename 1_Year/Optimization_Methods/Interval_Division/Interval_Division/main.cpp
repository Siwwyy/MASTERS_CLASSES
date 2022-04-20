#include <iomanip>
#include <iostream>
#include <fstream>

float f(const float x);

int main(int argc, char* argv[])
{
	const float E = 1e-06f;
	float a = 0.f;
	float b = 3.f;
	float x1 = 0.f;

	std::ofstream myfile;
	myfile.open("wynik.txt");

	std::cout << std::setprecision(15) << std::fixed;
	std::size_t iter = 0;
	while (std::fabs(a - b) > E)
	{
		x1 = (a + b) / 2.f;
		std::cout << "Iteracja: " << iter << " | x: " << x1 << " | f = " << f(x1) << '\n';
		myfile << "Iteracja: " << iter << " | x: " << x1 << " | f = " << f(x1) << '\n';

		if (std::fabs(f(x1)) <= E) //L1 Norm, jesli wartosc funkcji jest mniejsza niz Epsilon, wtedy zakoncz dzialanie
		{
			break;
		}
		if(f(x1) * f(a) < 0.f) //Warunek pierwszy
		{
			b = x1;
		}
		else if(f(x1) * f(b) < 0.f) //Warunek drugi
		{
			a = x1;
		}

		iter++;
	}
	std::cout << "\nf(" << x1 << ") = " << f(x1) << '\n';
	myfile << "\nf(" << x1 << ") = " << f(x1) << '\n';

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