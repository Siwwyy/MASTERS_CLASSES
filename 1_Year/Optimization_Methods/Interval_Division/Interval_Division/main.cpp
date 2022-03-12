#include <iostream>

float f(const float x);

int main(int argc, char* argv[])
{
	float E = 0.00001f;
	float a = -10.f;
	float b = -20.f;


	while (true)
	{
		const float c = a + (b - a / 2.f);

		if (b - a <= E)
		{
			std::cout << "X place zero: [ " << a << "," << b << " ]" << '\n';
			break;
		}
		//interval 1
		if ((f(a) > 0.0f && f(c) < 0.f) || (f(a) < 0.f && f(c) > 0.f))
		{
			b = c;
		}
		//interval 2
		else if ((f(c) > 0.0f && f(b) < 0.f) || (f(c) < 0.f && f(b) > 0.f))
		{
			a = c;
		}
		else
		{
			std::cout << "Given function does not have a place zero on X axis\n";
		}
	}

	std::cin.get();
	return EXIT_SUCCESS;
}

float f(const float x)
{
	return std::exp(-1.f * std::atan(x)) - x;
}