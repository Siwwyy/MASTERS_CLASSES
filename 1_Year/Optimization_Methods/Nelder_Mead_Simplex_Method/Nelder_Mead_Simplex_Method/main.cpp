#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>

#include "Point.hpp"

template <typename T>
T function_2D(Point<T, 2> cords);

template <typename T>
T function_3D(Point<T, 3> cords);


template <std::size_t nDim>
class Nelder_Mead_Method
{
public:

	Nelder_Mead_Method();
	Nelder_Mead_Method(const Nelder_Mead_Method& Object) = default;
	~Nelder_Mead_Method() = default;

	void print_simplex() const;
	void run();

private:

	template <std::size_t dot_dim>
	float dot_product(const Point<float, dot_dim>& p1, const Point<float, dot_dim>& p2) const;
	float cross_product2D(const Point<float, 2>& p1, const Point<float, 2>& p2) const;
	Point<float, 3> cross_product3D(const Point<float, 3>& p1, const Point<float, 3>& p2) const;

	float criterion() const;
	void sort_simplex();
	void generate_points();
	void shrink();
	Point<float, nDim> create_centroid() const;
	Point<float, nDim> reflection(const Point<float, nDim>& x0, const Point<float, nDim>& x_n_plus1) const;
	Point<float, nDim> expansion(const Point<float, nDim>& x_r, const Point<float, nDim>& x0) const;
	Point<float, nDim> contraction(const Point<float, nDim>& x_n_plus1, const Point<float, nDim>& x0) const;

	std::function<float(Point<float, nDim>)> function;
	std::vector<Point<float, nDim>> simplex;
	const float E;
};



int main(int argc, char* argv[])
{
	Nelder_Mead_Method<3> D;
	D.run();

	std::cin.get();
	return EXIT_SUCCESS;
}




template <typename T>
T function_2D(Point<T, 2> cords)
{
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(2);
	const T b = n + static_cast<T>(5);
	return std::pow<T>(a - cords[0], 2) + b * std::pow<T>(cords[1] - std::pow<T>(cords[0], 2), 2);
}


template <typename T>
T function_3D(Point<T, 3> cords)
{
	const T n = static_cast<T>(1);
	const T a = static_cast<T>(2);
	const T b = n * static_cast<T>(3);
	return std::pow<T>(a - cords[0], 2) + b * std::pow<T>(cords[1] - std::pow<T>(cords[0], 2), 2) + //k==1
		std::pow<T>(a - cords[1], 2) + b * std::pow<T>(cords[2] - std::pow<T>(cords[1], 2), 2); //k==2
}



/*
 *
 * Nelder-Mead class methods implementations
 *
 */



template <std::size_t nDim>
Nelder_Mead_Method<nDim>::Nelder_Mead_Method() :
	simplex({}),
	E(1e-06f)
{
	simplex.reserve(nDim + 1); //If Simplex is R^n, then we will use n+1 points
	if constexpr (nDim == 2)
	{
		function = function_2D<float>;
	}
	else
	{
		function = function_3D<float>;
	}
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::print_simplex() const
{
	for (std::size_t i = 0; i < simplex.size(); ++i)
	{
		std::cout << simplex[i] << '\n';
	}
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::run()
{
	generate_points(); //Create Simplex

	while (criterion() > E) //No. 7 -> Criterion
	{
		sort_simplex();

		auto x0 = create_centroid();
		auto& x_1 = simplex[0];
		auto& x_n = *(simplex.end() - 2);
		auto& x_n_plus1 = *(simplex.end() - 1);

		//auto x_r = reflection(x0, x_n_plus1);
		//auto x_c = contraction(x_n_plus1, x0);
		//auto x_e = expansion(x_r, x0);

		auto x_r = reflection(x0, x_n_plus1);
		if (function(x_r) < function(x_1)) //No. 3
		{
			auto x_e = expansion(x_r, x0);
			if (function(x_e) < function(x_1))
			{
				x_n_plus1 = x_e;
			}
			else
			{
				x_n_plus1 = x_r;
			}
		}
		else if (function(x_n) >= function(x_r) && function(x_r) >= function(x_1)) //No. 4
		{
			x_n_plus1 = x_r;
		}
		else if (function(x_n_plus1) > function(x_r) && function(x_r) > function(x_n)) //No. 5
		{
			auto x_c = contraction(x_n_plus1, x0);
			if (function(x_c) < function(x_n_plus1))
			{
				x_n_plus1 = x_c;
			}
			else
			{
				shrink();
			}
		}
		else if (function(x_r) > function(x_n_plus1)) //No. 6
		{
			auto x_c = contraction(x_n_plus1, x0);
			if (function(x_c) < function(x_n_plus1))
			{
				x_n_plus1 = x_c;
			}
			else
			{
				shrink();
			}
		}
		//print_simplex();
		//std::cout << '\n';
	}
	print_simplex();

	std::cout << '\n';
	std::cout << function(simplex[0]);
	std::cout << "\nEND\n";
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
float Nelder_Mead_Method<nDim>::criterion() const
{
	float result{};
	auto x0 = create_centroid();
	for (std::size_t i = 0; i < simplex.size(); ++i)
	{
		result += std::powf(function(simplex[i]) - function(x0), 2.f);
	}

	return std::sqrtf(result / static_cast<float>(simplex.size()));
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::sort_simplex()
{
	for (std::size_t i = 0; i < simplex.size(); ++i)
	{
		for (std::size_t j = 0; j < simplex.size() - 1; ++j)
		{
			if (function(simplex[j]) < function(simplex[j + 1]))
			{
				std::swap(simplex[j], simplex[j + 1]);
			}
		}
	}
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::generate_points()
{
	if constexpr (nDim == 2)
	{
		const Point<float, 3> p1({ 0.f, 0.f, 0.f });
		const Point<float, 3> p2({ 1.f, 0.f, 0.f });
		const Point<float, 3> p3({ 1.f, 1.f, 0.f });

		if (dot_product(p3, cross_product3D(p1, p2)) == 0.f)
		{
			std::cout << "Error, Your vectors are in one hyperplane!\n";
		}

		simplex.push_back(p1.get_shrink_dim());
		simplex.push_back(p2.get_shrink_dim());
		simplex.push_back(p3.get_shrink_dim());
	}
	else if constexpr (nDim == 3)
	{
		Point<float, 3> p1({ 0.f, 0.f, 0.f });
		Point<float, 3> p2({ 1.f, 0.f, 0.f });
		Point<float, 3> p3({ 1.f, 1.f, 0.f });
		Point<float, 3> p4({ 0.5f, 0.5f, 2.f });

		if (dot_product(p3, cross_product3D(p1, p2)) == 0.f && dot_product(p4, cross_product3D(p2, p3)) == 0.f)
		{
			std::cout << "Error, Your vectors are in one hyperplane!\n";
		}

		simplex.push_back(std::move(p1));
		simplex.push_back(std::move(p2));
		simplex.push_back(std::move(p3));
		simplex.push_back(std::move(p4));
	}
	else
	{
		static_assert(nDim == 2 || nDim == 3, "Currently implemented for nDim == 2 and 3");
	}
}

template <std::size_t nDim>
Point<float, nDim> Nelder_Mead_Method<nDim>::create_centroid() const
{
	Point<float, nDim> x0{};

	for (std::size_t i = 0; i < simplex.size() - 1; ++i)
	{
		for (std::size_t j = 0; j < nDim; ++j)
		{
			x0[j] += simplex[i][j];
		}
	}

	return x0 / static_cast<float>(simplex.size() - 1);
}

template <std::size_t nDim>
Point<float, nDim> Nelder_Mead_Method<nDim>::reflection(const Point<float, nDim>& x0,
	const Point<float, nDim>& x_n_plus1) const
{
	constexpr float alpha = 0.5f;
	Point<float, nDim> x_r{};

	for (std::size_t i = 0; i < x_r.get_dim(); ++i)
	{
		x_r[i] = (1.f + alpha) * x0[i] - alpha * x_n_plus1[i];
	}

	return x_r;
}

template <std::size_t nDim>
Point<float, nDim> Nelder_Mead_Method<nDim>::expansion(const Point<float, nDim>& x_r,
	const Point<float, nDim>& x0) const
{
	constexpr float gamma = 2.f;
	Point<float, nDim> x_e{};

	for (std::size_t i = 0; i < x_e.get_dim(); ++i)
	{
		x_e[i] = gamma * x_r[i] + (1.f - gamma) * x0[i];
	}

	return x_e;
}

template <std::size_t nDim>
Point<float, nDim> Nelder_Mead_Method<nDim>::contraction(const Point<float, nDim>& x_n_plus1,
	const Point<float, nDim>& x0) const
{
	constexpr float beta = 0.5f;
	Point<float, nDim> x_c{};

	for (std::size_t i = 0; i < x_c.get_dim(); ++i)
	{
		x_c[i] = beta * x_n_plus1[i] + (1.f - beta) * x0[i];
	}

	return x_c;
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::shrink()
{
	constexpr float zeta = 0.5f;
	const auto x1 = simplex[0];
	auto shrinked_simplex = simplex;

	for (std::size_t i = 0; i < simplex.size(); ++i)
	{
		shrinked_simplex[i] = (shrinked_simplex[i] + x1) * zeta;
	}
	simplex = std::move(shrinked_simplex);
}