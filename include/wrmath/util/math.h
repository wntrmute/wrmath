#ifndef __WRMATH_UTIL_MATH_H
#define __WRMATH_UTIL_MATH_H


namespace wr {
namespace util {


const double Epsilon_double = 0.0001;
const float  Epsilon_float = 0.0001;


static void
DefaultEpsilon(double &epsilon)
{
	epsilon = Epsilon_double;
}


static void
DefaultEpsilon(float &epsilon)
{
	epsilon = Epsilon_float;
}


template <typename T>
static T
WithinTolerance(T a, T b, T epsilon)
{
	return std::abs(a - b) < epsilon;
}


} // namespace util
} // namespace wr


#endif // __WRMATH_UTIL_MATH_H
