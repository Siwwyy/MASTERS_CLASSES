#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED


#include <iostream>
#include <array>


template<typename T, std::size_t nDim, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Point
{
public:
	Point() = delete;
	//template<typename ... Elems>
	//Point(Elems && ... elems);
	Point(std::initializer_list<T> elems);
	//Point(typename std::array<T, nDim>::iterator begin, typename std::array<T, nDim>::iterator end);
	Point(const T* ptr_begin, const T* ptr_end);
	~Point() = default;

	Point(const Point& Object) = default;
	Point& operator=(const Point& Object) = delete;

	Point(Point&& Object) noexcept;
	Point& operator=(Point&& Object) noexcept;

	bool operator==(const Point& rhs) const noexcept;
	[[nodiscard]] T& operator[](const std::size_t index);
	[[nodiscard]] const T& operator[](const std::size_t index) const;
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

//template <typename T, std::size_t nDim, typename T0>
//template <typename ... Elems>
//Point<T, nDim, T0>::Point(Elems&&... elems) :
//	Coordinates{ std::forward<Elems>(elems)... }
//{
//	constexpr std::size_t elems_amount = sizeof...(Elems);
//	static_assert(nDim == elems_amount, "Number of elements in constructor have to be equal to dimension of this point e.g 2D Point should has {1,2} etc.");
//}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>::Point(std::initializer_list<T> elems)
{
	//std::copy_n(elems.begin(), nDim, this->Coordinates);
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

//template <typename T, std::size_t nDim, typename T0>
//Point<T, nDim, T0>::Point(typename std::array<T, nDim>::iterator begin, typename std::array<T, nDim>::iterator end)
//{
//	std::copy_n(begin, nDim, this->Coordinates);
//}

template <typename T, std::size_t nDim, typename T0>
Point<T, nDim, T0>::Point(Point&& Object) noexcept
	:
	Coordinates(std::move(Object.Coordinates))
{ }

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
inline std::ostream& operator<<(std::ostream& lhs, const Point<T, nDim, T0>& rhs)
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


//template <typename T, std::size_t nDim, typename T0>
//template <typename ... Elems>
//Point<T, nDim, T0>::Point(Elems&&... elems) :
//	Coordinates{ std::forward<Elems>(elems)... }
//{
//	constexpr std::size_t elems_amount = sizeof...(Elems);
//	static_assert(nDim == elems_amount, "Number of elements in constructor have to be equal to dimension of this point e.g 2D Point should has {1,2} etc.");
//
//
//}
//
//template <typename T, std::size_t nDim, typename T0>
//Point<T, nDim, T0>::Point(Point&& Object) noexcept
//	:
//	Coordinates(std::move(Object.Coordinates))
//{ }
//
//template <typename T, std::size_t nDim, typename T0>
//Point<T, nDim, T0>& Point<T, nDim, T0>::operator=(Point&& Object) noexcept
//{
//	if (this != &Object)
//	{
//		Coordinates = std::move(Object.Coordinates);
//	}
//	return *this;
//}
//
//template <typename T, std::size_t nDim, typename T0>
//bool Point<T, nDim, T0>::operator==(const Point& rhs) const noexcept
//{
//	if (Coordinates == rhs.Coordinates)
//	{
//		return true;
//	}
//	return false;
//}
//
///*
//* @param Index must be between 0 and Point dimension - 1 e.g. 2D Point -> Indexes 0 and 1, 3D Point -> Indexes 0, 1, 2 and so forth
//*/
//template <typename T, std::size_t nDim, typename T0>
//T& Point<T, nDim, T0>::operator[](const std::size_t index)
//{
//	return Coordinates.at(index);
//}
//
///*
//* @param Index must be between 0 and Point dimension - 1 e.g. 2D Point -> Indexes 0 and 1, 3D Point -> Indexes 0, 1, 2 and so forth
//*/
//template <typename T, std::size_t nDim, typename T0>
//const T& Point<T, nDim, T0>::operator[](const std::size_t index) const
//{
//	if (Coordinates.size() <= index)
//	{
//		std::_Xout_of_range("invalid list<T> subscript");
//	}
//	return Coordinates.at(index);
//}

//template <typename T, std::size_t nDim, typename T0>
//decltype(auto) Point<T, nDim, T0>::operator[](const std::size_t& index) const
//{
//	return Coordinates.at(index);
//}

//template <typename T, std::size_t nDim, typename T0>
//decltype(auto) Point<T, nDim, T0>::operator[](const std::size_t& index) const
//{

//	return *this;
//}

/*
* @param Index must be between 0 and Point dimension - 1 e.g. 2D Point -> Indexes 0 and 1, 3D Point -> Indexes 0, 1, 2 and so forth
*/
//template <typename T, std::size_t nDim, typename T0>
//T& Point<T, nDim, T0>::operator[](const std::size_t& index) const
//{
//	//static_assert(!(index >= 0 && index < nDim), "Index must be between 0 and Point dimension - 1 e.g. 2D Point -> Indexes 0 and 1, 3D Point -> Indexes 0, 1, 2 and so forth");
//	//if (index >= 0 && index < nDim)
//	//{
//	//	return Coordinates[index];
//	//}
//	//return Coordinates[0];

//	return Coordinates.at(index);
//}


#endif /* VECTOR_HPP_INCLUDED */