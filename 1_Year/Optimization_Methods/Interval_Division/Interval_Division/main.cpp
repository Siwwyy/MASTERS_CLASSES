#include <iostream>

float f(const float x);

int main(int argc, char* argv[])
{
	float E = 0.00001f;
	float a = 0.f;
	float b = 1.5f;
	const float K = (std::sqrt(5.f) - 1.f) / 2.f;
	float x1 = b - (b - a) * K;
	float x2 = a + (b - a) * K;


	std::cout << "a: " << a << ", b: " << b << '\n';
	std::cout << "x1: " << x1 << ", x2: " << x2 << '\n';

	while (true)
	{
		if (f(x1) > f(x2))
		{
			a = x1;
			x1 = x2;
			x2 = a + (b - a) * K;
		}
		else if (f(x1) <= f(x2))
		{
			const float temp = x1;
			b = x2;
			x1 = b - (b - a) * K;
			x2 = temp;
		}

		if (std::fabs(b - a) <= E)
		{
			break;
		}
	}

	std::cout << '\n';
	std::cout << "a: " << a << ", b: " << b << '\n';
	std::cout << "x1: " << x1 << ", x2: " << x2 << '\n';
	std::cout << "F(" << x1 << ") = " << f(x1) << '\n';
	std::cin.get();
	return EXIT_SUCCESS;
}

float f(const float x)
{
	//return std::exp(-1.f * std::atan(x)) - x;
	//return std::log(x) - sqrt(x);
	return 2*sinf(x) - std::log(x);
	//return std::powf(x, 2.f);
}