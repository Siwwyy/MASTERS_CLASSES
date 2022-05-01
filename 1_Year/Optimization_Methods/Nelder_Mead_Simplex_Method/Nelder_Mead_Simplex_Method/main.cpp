#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>

#include "Point.hpp"

template<typename T>
T function_2D(const T x1, const T x2);

template<typename T>
T function_3D(const T x1, const T x2, const T x3);

template<std::size_t nDim>
class Nelder_Mead_Method
{
public:
	Nelder_Mead_Method();
	Nelder_Mead_Method(const Nelder_Mead_Method& Object) = default;
	~Nelder_Mead_Method() = default;


	void run();

private:

	template<std::size_t dot_dim>
	float dot_product(const Point<float, dot_dim>& p1, const Point<float, dot_dim>& p2) const;
	float cross_product2D(const Point<float, 2>& p1, const Point<float, 2>& p2) const;
	Point<float, 3> cross_product3D(const Point<float, 3>& p1, const Point<float, 3>& p2) const;

	void sort_simplex();
	float create_centroid();
	void generate_points();

	std::vector<Point<float, nDim>> Simplex;
	std::vector<float> y;
	const float E;
	std::function<float(float, float)> function;
};



template<std::size_t nDim>
Nelder_Mead_Method<nDim>::Nelder_Mead_Method() :
	Simplex({}),
	y({}),
	E(1e-6f),
	function(function_2D<float>)
{
	Simplex.reserve(nDim + 1); //If Simplex is R^n, then we will use n+1 points
	y.reserve(nDim + 1); //If Simplex is R^n, then we will use n+1 points
	generate_points();
}

//template <std::size_t nDim>
//float Nelder_Mead_Method<nDim>::dot_product(const Point<float, nDim>& p1, const Point<float, nDim>& p2) const
//{
//	float result{};
//	for (std::size_t i = 0; i < nDim; ++i)
//	{
//		result += p1[i] * p2[i];
//	}
//	return result;
//}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::run()
{
	while (true)
	{
		sort_simplex();
		auto centroid = create_centroid();

	}
}


template <std::size_t nDim>
template <std::size_t dot_dim>
float Nelder_Mead_Method<nDim>::dot_product(const Point<float, dot_dim>& p1, const Point<float, dot_dim>& p2) const
{
	float result{};
	for (std::size_t i = 0; i < dot_dim; ++i)
	{
		result += p1[i] * p2[i];
	}
	return result;
}

//template <std::size_t nDim = 2>
//float Nelder_Mead_Method<2>::cross_product2D(const Point<float, 2>& p1, const Point<float, 2>& p2) const
//{
//	//static_assert(nDim == 2, "For CrossProduct 2D, you have to use method for 2D case, result is a Z comp");
//	return p1[0] * p2[1] - p1[1] * p2[0];
//}
//
//template <std::size_t nDim = 3>
//Point<float, 3> Nelder_Mead_Method<3>::cross_product3D(const Point<float, 3>& p1, const Point<float, 3>& p2) const
//{
//	//static_assert(nDim == 3, "For CrossProduct 3D, you have to use method for 3D case, result is a vector");
//	float x_comp = (p1[1] * p2[2] - p1[2] * p2[1]);
//	float y_comp = (p1[2] * p2[0] - p1[0] * p2[2]);
//	float z_comp = (p1[0] * p2[1] - p1[1] * p2[0]);
//	return Point<float, 3>(x_comp, y_comp, z_comp);
//}
template <std::size_t nDim>
float Nelder_Mead_Method<nDim>::cross_product2D(const Point<float, 2>& p1, const Point<float, 2>& p2) const
{
	return p1[0] * p2[1] - p1[1] * p2[0];
}

template <std::size_t nDim>
Point<float, 3> Nelder_Mead_Method<nDim>::cross_product3D(const Point<float, 3>& p1, const Point<float, 3>& p2) const
{
	float x_comp = (p1[1] * p2[2] - p1[2] * p2[1]);
	float y_comp = (p1[2] * p2[0] - p1[0] * p2[2]);
	float z_comp = (p1[0] * p2[1] - p1[1] * p2[0]);
	return Point<float, 3>({ x_comp, y_comp, z_comp });
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::sort_simplex()
{
	//for (int i = 0; i < size; i++)
	//{
	//	for (int j = 0; j < size - 1; j++)
	//	{
	//		if (tab[j] > tab[j + 1])
	//			swap(tab[j], tab[j + 1]);

	//	}
	//}

	for (std::size_t i = 0; i < Simplex.size(); ++i)
	{
		for (std::size_t j = 0; j < Simplex.size(); ++j)
		{
			if (y[i] < y[i + 1])
			{
				std::swap(Simplex[i], Simplex[i + 1]);
			}
		}
	}
}

template <std::size_t nDim>
float Nelder_Mead_Method<nDim>::create_centroid()
{
	float centroid_value{};

	for (std::size_t i = 0; i < nDim - 1; ++i)
	{
		for (std::size_t j = 0; j < nDim - 1; ++j)
		{
			centroid_value += Simplex[i][j];
		}
	}

	return centroid_value / static_cast<float> ((nDim - 1) * 2);
}

template<std::size_t nDim>
void Nelder_Mead_Method<nDim>::generate_points()
{
	if constexpr (nDim == 2)
	{
		//Init points in amount: nDim + 1
		//Point<float, 3> p1({ 0.f, 0.f, 0.f });
		//Point<float, 3> p2({ 2.f, 0.f, 0.f });
		//Point<float, 3> p3({ 1.f, 1.f, 0.f });

		Point<float, 3> p1({ 0.f, 0.f, 0.f });
		Point<float, 3> p2({ 2.f, 0.f, 0.f });
		Point<float, 3> p3({ 1.f, 1.f, 0.f });

		if (dot_product(p3, cross_product3D(p1, p2)) == 0.f)
		{
			std::cout << "Error, Your vectors are in one hyperplane!\n";
			//exit(0);
		}

		Simplex.push_back(p1.get_shrink_dim());
		Simplex.push_back(p2.get_shrink_dim());
		Simplex.push_back(p3.get_shrink_dim());

		//y.push_back()

		////Init points in amount: nDim + 1
		//Point<float, nDim + 1> p1(0.f, 0.f, 0.f);
		//Point<float, nDim + 1> p2(1.f, 0.f, 0.f);
		//Point<float, nDim + 1> p3(0.f, 1.f, 0.f);

		//if (dot_product(p1, cross_product3D(p2, p3)) == 0.f)
		//{
		//	std::cout << "Error, Your vectors are in one hyperplane!\n";
		//	//exit(0);
		//}

		//Simplex.push_back(std::move(p1));
		//Simplex.push_back(std::move(p2));
		//Simplex.push_back(std::move(p3));
	}
	else if constexpr (nDim == 3)
	{

	}
	else
	{
		static_assert(nDim == 2 || nDim == 3, "Currently implemented for nDim == 2 and 3");
	}
}


int main(int argc, char* argv[])
{
	//const Point<float, 3> p(2.f, 3.f);

	Nelder_Mead_Method<2> D;
	D.run();
	//

//Point<float, 3> p({ 2.f, 3.f, 1.f });


//auto d = p.get_shrink_dim();
//auto c = d.get_shrink_dim();
////auto a = c.get_shrink_dim();


//std::cout << p << '\n';
//std::cout << d << '\n';
//std::cout << c << '\n';
////std::cout << a << '\n';

	std::cin.get();
	return EXIT_SUCCESS;
}

template <typename T>
T function_2D(const T x1, const T x2)
{
	//static_assert(std::is_same_v<T, U>, "Function arguments have to have the same data types");
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(2);
	const T b = n + static_cast<T>(5);
	return std::pow<T>(a - x1, 2) + b * std::pow<T>(x2 - std::pow<T>(x1, 2), 2);
}

template <typename T>
T function_3D(const T x1, const T x2, const T x3)
{
	//static_assert(std::is_same_v<T, U, Z>, "Function arguments have to have the same data types");
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(2);
	const T b = n * static_cast<T>(3);
	return std::pow<T>(a - x1, 2) + b * std::pow<T>(x2 - std::pow<T>(x1, 2), 2) + //k==1
		std::pow<T>(a - x2, 2) + b * std::pow<T>(x3 - std::pow<T>(x2, 2), 2);  //k==2
}