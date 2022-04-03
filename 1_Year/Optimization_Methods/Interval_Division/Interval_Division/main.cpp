#include <iostream>

float f(const float x);

int main(int argc, char* argv[])
{



	//while (true)
	//{
	//	const float c = a + (b - a / 2.f);

	//	if (std::abs(b - a) <= E)
	//	{
	//		std::cout << "X place zero: [ " << a << "," << b << " ]" << '\n';
	//		break;
	//	}
	//	//interval 1
	//	if ((f(a) > 0.0f && f(c) < 0.f) || (f(a) < 0.f && f(c) > 0.f))
	//	{
	//		b = c;
	//	}
	//	//interval 2
	//	else if ((f(c) > 0.0f && f(b) < 0.f) || (f(c) < 0.f && f(b) > 0.f))
	//	{
	//		a = c;
	//	}
	//	else
	//	{
	//		std::cout << "Given function does not have a place zero on X axis\n";
	//	}
	//}


	float E = 0.00001f;
	float x1 = -5.f;
	float x2 = 10.f;
	float a = -10.f;
	float b = 20.f;
	const float c{};
	const float T = 0.001f;

	while (true)
	{
		std::cout << a << ' ' << b << '\n';
		if (f(x2) > f(x1))
		{
			b = x2;
			x2 = x1;
			x1 = a + (1.f - T) * (b - a);
		}
		else if (f(x2) <= f(x1))
		{
			a = x1;
			x1 = x2;
			x2 = b + (1.f - T) * (b - a);
		}

		if (std::abs(b - a) <= E)
		{
			std::cout << "X place zero: [ " << a << "," << b << " ]" << '\n';
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