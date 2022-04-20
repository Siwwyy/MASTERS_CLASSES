#include <fstream>
#include <iomanip>
#include <iostream>


float f(const float x, const float y);
float df_x(const float x, const float y);
float df_y(const float x, const float y);


int main(int argc, char* argv[])
{
	float x = 1.f;
	float y = 1.f;
	const float alpha = 0.001f;
	const float E = 1e-06f;

	std::ofstream myfile;
	myfile.open("wynik.txt");

	std::cout << std::setprecision(15) << std::fixed;
	std::size_t iter = 0;
	for (std::size_t i = 0; i < 10000; ++i)
	{

		std::cout << "Iteracja: " << iter << " | x1: " << x << " | x2: " << y << '\n';
		myfile << "Iteracja: " << iter << " | x1: " << x << " | x2: " << y << '\n';

		float temp_x = x;
		float temp_y = y;

		temp_x = temp_x - alpha * df_x(temp_x, temp_y);
		temp_y = temp_y - alpha * df_y(temp_x, temp_y);

		x = temp_x;
		y = temp_y;


		const float L1_norm = std::fabs(df_x(temp_x, temp_y)) + std::fabs(df_y(temp_x, temp_y));
		if (L1_norm <= E) //L1 Norm -> better sparsity
		{
			break;
		}

		//const float L2_norm = std::powf(std::fabs(df_x(temp_x, temp_y)), 2.f) + std::powf(std::fabs(df_y(temp_x, temp_y)), 2.f);
		//if (std::sqrt(L2_norm )<= E) //L2 Norm 
		//{
		//	break;
		//}
		iter++;
	}

	std::cout << "X: " << x << " | Y: " << y << '\n';
	std::cout << "\nf(" << x << ',' << y << ") = " << f(x,y) << std::endl;
	myfile << "X: " << x << " | Y: " << y << '\n';
	myfile << "\nf(" << x << ',' << y << ") = " << f(x, y) << std::endl;
	myfile.close();

	std::cin.get();
	return EXIT_SUCCESS;
}

float f(const float x, const float y)
{
	return (-1.f * std::powf(x, 2.f) - 3.f * y) * std::exp(-1.f * std::powf(x, 2.f) - std::powf(y, 2.f));
}

float df_x(const float x, const float y)
{
	return 2.f * std::exp(-1.f * std::powf(x, 2.f) - std::powf(y, 2.f)) * x * (-1.f + std::powf(x, 2.f) + 3.f * y);
}

float df_y(const float x, const float y)
{
	return std::exp(-1.f * std::powf(x, 2.f) - std::powf(y, 2.f)) * (-3.f + 2.f * std::powf(x, 2.f) * y + 6.f * std::powf(y, 2.f));
}