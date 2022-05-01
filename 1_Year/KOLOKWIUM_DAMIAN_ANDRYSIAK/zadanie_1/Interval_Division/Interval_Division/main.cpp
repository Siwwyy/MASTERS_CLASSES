#include <iomanip>
#include <iostream>
#include <fstream>

float f(const float x);

float f2(const float x, const float alpha)
{
	return std::cosh(x) - std::log10f(alpha * std::sqrtf(x));
}


int main(int argc, char* argv[])
{
	float E = 1e-06f;
	float a = 0.2f;
	float b = 0.6f;
	float x1 = 0.f;
	const float alpha = 19.f;


	std::ofstream myfile;
	myfile.open("wynik.txt");

	std::cout << std::setprecision(15) << std::fixed;
	std::size_t iter = 0;
	myfile << "| Warunek stopu a) |\n";
	while (true)
	{
		x1 = (a + b) / 2.f;
		std::cout << "Iteracja: " << iter << " | x: " << x1 << " | f = " << f2(x1, alpha) << " Alpha: " << alpha << '\n';
		myfile << "Iteracja: " << iter << " | x: " << x1 << " | f = " << f2(x1, alpha) << " Alpha: " << alpha << '\n';
		if (std::fabs(a - b) < E) //L1 Norm, jesli wartosc funkcji jest mniejsza niz Epsilon, wtedy zakoncz dzialanie
		{
			break;
		}

		if (f2(x1, alpha) * f2(a, alpha) < 0.f) //Warunek pierwszy
		{
			b = x1;
		}
		else  //Warunek drugi
		{
			a = x1;
		}
		iter++;
	}
	std::cout << "\nf(" << x1 << ") = " << f2(x1, alpha) << '\n';
	myfile << "\nf(" << x1 << ") = " << f2(x1, alpha) << '\n';


	myfile << "\n| Warunek stopu b) |\n";
	a = 0.2f;
	b = 0.6f;
	x1 = 0.f;
	E = 1e-08f;
	iter = 0;
	while (true)
	{
		x1 = (a + b) / 2.f;
		std::cout << "Iteracja: " << iter << " | x: " << x1 << " | f = " << f2(x1, alpha) << " Alpha: " << alpha << '\n';
		myfile << "Iteracja: " << iter << " | x: " << x1 << " | f = " << f2(x1, alpha) << " Alpha: " << alpha << '\n';
		if (std::fabs(f2(x1, alpha)) <= E) //L1 Norm, jesli wartosc funkcji jest mniejsza niz Epsilon, wtedy zakoncz dzialanie
		{
			break;
		}

		if (f2(x1, alpha) * f2(a, alpha) < 0.f) //Warunek pierwszy
		{
			b = x1;
		}
		else  //Warunek drugi
		{
			a = x1;
		}
		iter++;
	}
	std::cout << "\nf(" << x1 << ") = " << f2(x1, alpha) << '\n';
	myfile << "\nf(" << x1 << ") = " << f2(x1, alpha) << '\n';

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