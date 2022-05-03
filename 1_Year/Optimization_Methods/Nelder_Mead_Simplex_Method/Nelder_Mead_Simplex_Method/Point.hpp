#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED


#include <iostream>
#include <array>
#include <cassert>


template <typename T, std::size_t nDim, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Point
{
public:
	Point();
	Point(std::initializer_list<T> elems);
	Point(const T* ptr_begin, const T* ptr_end);
	~Point() = default;

	Point(const Point& Object) = default;
	Point& operator=(const Point& Object) = default;

	Point(Point&& Object) noexcept;
	Point& operator=(Point&& Object) noexcept;

	bool operator==(const Point& rhs) const noexcept;
	[[nodiscard]] T& operator[](std::size_t index);
	[[nodiscard]] const T& operator[](std::size_t index) const;
	[[nodiscard]] Point<T, nDim> operator+(const T value);
	[[nodiscard]] Point<T, nDim>& operator+=(const T value);
	[[nodiscard]] Point<T, nDim> operator*(const T value);
	[[nodiscard]] Point<T, nDim>& operator*=(const T value);
	[[nodiscard]] Point<T, nDim> operator/(const T denominator);
	[[nodiscard]] Point<T, nDim>& operator/=(const T denominator);

	[[nodiscard]] Point<T, nDim> operator+(const Point<T, nDim>& rhs);
	[[nodiscard]] Point<T, nDim>& operator+=(const Point<T, nDim>& rhs);
	[[nodiscard]] Point<T, nDim> operator*(const Point<T, nDim>& rhs);
	[[nodiscard]] Point<T, nDim>& operator*=(const Point<T, nDim>& rhs);
	[[nodiscard]] Point<T, nDim> operator/(const Point<T, nDim>& denominator);
	[[nodiscard]] Point<T, nDim>& operator/=(const Point<T, nDim>& denominator);

	auto get_dim() const;
	Point<T, nDim - 1> get_shrink_dim() const;

	template <typename T, std::size_t nDim, typename T0>
	friend std::ostream& operator<<(std::ostream& lhs, const Point<T, nDim, T0>& rhs);

	[[noreturn]] void _Xran() const
	{
		std::_Xout_of_range("invalid Point<T, nDim> subscript");
	}

private:
	std::array<T, nDim> Coordinates;
};

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>::Point() :
	Coordinates({})
{ }

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>::Point(std::initializer_list<T> elems)
{
	for (std::size_t i = 0; i < elems.size(); ++i)
	{
		Coordinates[i] = *(elems.begin() + i);
	}
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>::Point(const T* ptr_begin, const T* ptr_end)
{
	for (std::size_t i = 0; i < nDim; ++i)
	{
		Coordinates[i] = *(ptr_begin + i);
	}
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>::Point(Point&& Object) noexcept
	:
	Coordinates(std::move(Object.Coordinates))
{
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>& Point<T, nDim, T0>::operator=(Point&& Object) noexcept
{
	if (this != &Object)
	{
		Coordinates = std::move(Object.Coordinates);
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
bool Point<T, nDim, T0>::operator==(const Point& rhs) const noexcept
{
	if (Coordinates == rhs.Coordinates)
	{
		return true;
	}
	return false;
}

template <typename T, std::size_t nDim, typename T0>
T& Point<T, nDim, T0>::operator[](const std::size_t index)
{
	return const_cast<T&>(std::as_const(*this)[index]);
}

template <typename T, std::size_t nDim, typename T0>
const T& Point<T, nDim, T0>::operator[](const std::size_t index) const
{
	return Coordinates.at(index);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim> Point<T, nDim, T0>::operator+(const T value)
{
	return Point<T, nDim>::operator+=(value);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim>& Point<T, nDim, T0>::operator+=(const T value)
{
	for (std::size_t i = 0; i < Coordinates.size(); ++i)
	{
		Coordinates[i] = Coordinates[i] + value;
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim> Point<T, nDim, T0>::operator*(const T value)
{
	return Point<T, nDim>::operator*=(value);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim>& Point<T, nDim, T0>::operator*=(const T value)
{
	for (std::size_t i = 0; i < Coordinates.size(); ++i)
	{
		Coordinates[i] = Coordinates[i] * value;
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim> Point<T, nDim, T0>::operator/(const T denominator)
{
	return Point<T, nDim>::operator/=(denominator);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim>& Point<T, nDim, T0>::operator/=(const T denominator)
{
	for (std::size_t i = 0; i < Coordinates.size(); ++i)
	{
		Coordinates[i] = Coordinates[i] / denominator;
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim> Point<T, nDim, T0>::operator+(const Point<T, nDim>& rhs)
{
	return Point<T, nDim>::operator+=(rhs);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim>& Point<T, nDim, T0>::operator+=(const Point<T, nDim>& rhs)
{
	assert(get_dim() <= rhs.get_dim(), "Dimension of this and rhs has to be <=");
	for (std::size_t i = 0; i < Coordinates.size(); ++i)
	{
		Coordinates[i] = Coordinates[i] + rhs[i];
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim> Point<T, nDim, T0>::operator*(const Point<T, nDim>& rhs)
{
	return Point<T, nDim>::operator*=(rhs);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim>& Point<T, nDim, T0>::operator*=(const Point<T, nDim>& rhs)
{
	assert(get_dim() <= rhs.get_dim(), "Dimension of this and rhs has to be <=");
	for (std::size_t i = 0; i < Coordinates.size(); ++i)
	{
		Coordinates[i] = Coordinates[i] * rhs[i];
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim> Point<T, nDim, T0>::operator/(const Point<T, nDim>& denominator)
{
	return Point<T, nDim>::operator/=(denominator);
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim>& Point<T, nDim, T0>::operator/=(const Point<T, nDim>& denominator)
{
	assert(get_dim() <= denominator.get_dim(), "Dimension of this and denominator has to be <=");
	for (std::size_t i = 0; i < Coordinates.size(); ++i)
	{
		Coordinates[i] = Coordinates[i] / denominator[i];
	}
	return *this;
}

template <typename T, std::size_t nDim, typename T0>
auto Point<T, nDim, T0>::get_dim() const
{
	return Coordinates.size();
}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim - 1> Point<T, nDim, T0>::get_shrink_dim() const
{
	static_assert(nDim > 1, "You cant get point from R^0!, nDim should be > 1");
	return Point<T, nDim - 1>(&Coordinates[0], &Coordinates[Coordinates.size() - 2]);
}

template <typename T, std::size_t nDim, typename T0>
std::ostream& operator<<(std::ostream& lhs, const Point<T, nDim, T0>& rhs)
{
	auto distance = [&](const T& elem)
	{
		const std::size_t diff = (&elem - rhs.Coordinates._Unchecked_begin());
		return diff;
	};

	lhs << "[ ";
	for (const auto& elem : rhs.Coordinates)
	{
		if (distance(elem) != (rhs.Coordinates.size() - 1))
		{
			lhs << elem << " , ";
		}
		else
		{
			lhs << elem;
		}
	}
	lhs << " ]";
	return lhs;
}

#endif /* VECTOR_HPP_INCLUDED */