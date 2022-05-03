#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>

#include "Point.hpp"

template <typename T>
T function_2D(T x1, T x2);

template <typename T>
T function_3D(T x1, T x2, T x3);

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

	void run_2D();
	void run_3D();

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

	std::function<float(float, float)> function;
	std::vector<Point<float, nDim>> simplex;
	const float E;
};


template <std::size_t nDim>
Nelder_Mead_Method<nDim>::Nelder_Mead_Method() :
	function(function_2D<float>),
	simplex({}),
	E(1e-6f)
{
	simplex.reserve(nDim + 1); //If Simplex is R^n, then we will use n+1 points
	//generate_points();
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

	if(nDim == 2)
	{
		run_2D();
	}
	else
	{
		run_3D();
	}

	print_simplex();
	std::cout << "END\n";
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::run_2D()
{
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
		if (function(x_r[0], x_r[1]) < function(x_1[0], x_1[1])) //No. 3
		{
			auto x_e = expansion(x_r, x0);
			if (function(x_e[0], x_e[1]) < function(x_1[0], x_1[1]))
			{
				x_n_plus1 = x_e;
			}
			else
			{
				x_n_plus1 = x_r;
			}
		}
		else if (function(x_n[0], x_n[1]) >= function(x_r[0], x_r[1]) && function(x_r[0], x_r[1]) >= function(x_1[0], x_1[1])) //No. 4
		{
			x_n_plus1 = x_r;
		}
		else if (function(x_n_plus1[0], x_n_plus1[1]) > function(x_r[0], x_r[1]) && function(x_r[0], x_r[1]) > function(x_n[0], x_n[1])) //No. 5
		{
			auto x_c = contraction(x_n_plus1, x0);
			if (function(x_c[0], x_c[1]) < function(x_n_plus1[0], x_n_plus1[1]))
			{
				x_n_plus1 = x_c;
			}
			else
			{
				shrink();
			}
		}
		else if (function(x_r[0], x_r[1]) > function(x_n_plus1[0], x_n_plus1[1])) //No. 6
		{
			auto x_c = contraction(x_n_plus1, x0);
			if (function(x_c[0], x_c[1]) < function(x_n_plus1[0], x_n_plus1[1]))
			{
				x_n_plus1 = x_c;
			}
			else
			{
				shrink();
			}
		}
		print_simplex();
		std::cout << '\n';
	}
}

template <std::size_t nDim>
void Nelder_Mead_Method<nDim>::run_3D()
{
	//while (criterion() > E) //No. 7 -> Criterion
	//{
	//	sort_simplex();

	//	auto x0 = create_centroid();
	//	auto& x_1 = simplex[0];
	//	auto& x_n = *(simplex.end() - 2);
	//	auto& x_n_plus1 = *(simplex.end() - 1);

	//	//auto x_r = reflection(x0, x_n_plus1);
	//	//auto x_c = contraction(x_n_plus1, x0);
	//	//auto x_e = expansion(x_r, x0);

	//	auto x_r = reflection(x0, x_n_plus1);
	//	if (function(x_r[0], x_r[1], x_r[2]) < function(x_1[0], x_1[1], x_1[2])) //No. 3
	//	{
	//		auto x_e = expansion(x_r, x0);
	//		if (function(x_e[0], x_e[1], x_e[2], x_e[2]) < function(x_1[0], x_1[1], x_1[2]))
	//		{
	//			x_n_plus1 = x_e;
	//		}
	//		else
	//		{
	//			x_n_plus1 = x_r;
	//		}
	//	}
	//	else if (function(x_n[0], x_n[1], x_n[2]) >= function(x_r[0], x_r[1], x_r[2]) && function(x_r[0], x_r[1], x_r[2]) >= function(x_1[0], x_1[1], x_1[2])) //No. 4
	//	{
	//		x_n_plus1 = x_r;
	//	}
	//	else if (function(x_n_plus1[0], x_n_plus1[1], x_n_plus1[2]) > function(x_r[0], x_r[1], x_r[2]) && function(x_r[0], x_r[1], x_r[2]) > function(x_n[0], x_n[1], x_n[2])) //No. 5
	//	{
	//		auto x_c = contraction(x_n_plus1, x0);
	//		if (function(x_c[0], x_c[1], x_c[2]) < function(x_n_plus1[0], x_n_plus1[1], x_n_plus1[2]))
	//		{
	//			x_n_plus1 = x_c;
	//		}
	//		else
	//		{
	//			shrink();
	//		}
	//	}
	//	else if (function(x_r[0], x_r[1], x_r[2]) > function(x_n_plus1[0], x_n_plus1[1], x_n_plus1[2])) //No. 6
	//	{
	//		auto x_c = contraction(x_n_plus1, x0);
	//		if (function(x_c[0], x_c[1], x_c[2]) < function(x_n_plus1[0], x_n_plus1[1], x_n_plus1[2]))
	//		{
	//			x_n_plus1 = x_c;
	//		}
	//		else
	//		{
	//			shrink();
	//		}
	//	}
	//}
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
		result += std::powf(function(simplex[i][0], simplex[i][1]) - function(x0[0], x0[1]), 2.f);
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
			if (function(simplex[j][0], simplex[j][1]) < function(simplex[j + 1][0], simplex[j + 1][1]))
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
		const Point<float, 3> p1({ 2.f, 3.f, 5.f });
		const Point<float, 3> p2({ 3.f, 3.f, 5.f });
		const Point<float, 3> p3({ 4.f, 4.f, 5.f });

		if (dot_product(p3, cross_product3D(p1, p2)) == 0.f)
		{
			std::cout << "Error, Your vectors are in one hyperplane!\n";
		}

		simplex.push_back(p1.get_shrink_dim());
		simplex.push_back(p2.get_shrink_dim());
		simplex.push_back(p3.get_shrink_dim());

		//y.push_back(function(simplex[0][0], simplex[0][1]));
		//y.push_back(function(simplex[1][0], simplex[1][1]));
		//y.push_back(function(simplex[2][0], simplex[2][1]));
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

		//y.push_back(function(simplex[0][0], simplex[0][1], simplex[0][2]));
		//y.push_back(function(simplex[1][0], simplex[1][1], simplex[1][2]));
		//y.push_back(function(simplex[2][0], simplex[2][1], simplex[2][2]));
		//y.push_back(function(simplex[3][0], simplex[3][1], simplex[3][2]));
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
		std::pow<T>(a - x2, 2) + b * std::pow<T>(x3 - std::pow<T>(x2, 2), 2); //k==2
}
