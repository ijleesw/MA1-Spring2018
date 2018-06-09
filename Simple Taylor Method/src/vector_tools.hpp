#ifndef VECTOR_TOOLS_HPP_
#define VECTOR_TOOLS_HPP_

#include <algorithm>
#include <functional>
#include <vector>


/*****************************************************
 *
 *  Function prototypes & static variables
 *
 *****************************************************/

/*
std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs);
std::vector<T> operator-(const std::vector<T>& lhs, const std::vector<T>& rhs);
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs);
std::vector<T> operator*(const std::vector<T>& lhs, const T& rhs);
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v);
*/

static const char* delimiter = ", "; // used in operator<<


/*****************************************************
 *
 *  Function definitions
 *
 *****************************************************/

/*
 * operator+ - componentwise addition of two vectors
 */
template <typename T>
std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    assert(lhs.size() == rhs.size());

    std::vector<T> res;
    res.reserve(lhs.size());

    std::transform(lhs.begin(), lhs.end(), rhs.begin(), std::back_inserter(res), std::plus<T>());
    return res;
}


/*
 * operator- - componentwise subtraction of two vectors
 */
template <typename T>
std::vector<T> operator-(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    assert(lhs.size() == rhs.size());

    std::vector<T> res;
    res.reserve(lhs.size());

    std::transform(lhs.begin(), lhs.end(), rhs.begin(), std::back_inserter(res), std::minus<T>());
    return res;
}


/*
 * operator* - componentwise multiplication of two vectors
 */
template <typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    assert(lhs.size() == rhs.size());

    std::vector<T> res;
    res.reserve(lhs.size());

    std::transform(lhs.begin(), lhs.end(), rhs.begin(), std::back_inserter(res), std::multiplies<T>());
    return res;
}


/*
 * operator* - multiplication between vector<T> and T
 */
template <typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const T& rhs)
{
    std::vector<T> res;
    res.reserve(lhs.size());

    std::transform(lhs.begin(), lhs.end(), std::back_inserter(res), std::bind1st(std::multiplies<T>(), rhs));
    return res;
}


/*
 * operator<< - operator overloading for vector
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
	auto iter = v.begin();
	if (iter != v.end()) { out << *iter; iter++; }
	for (; iter != v.end(); iter++) out << delimiter << *iter;
	return out;
}


#endif /* VECTOR_TOOLS_HPP_ */