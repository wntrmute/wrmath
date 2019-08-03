#ifndef __WRNAV_UTIL_MATH_H
#define __WRNAV_UTIL_MATH_H


namespace wr {
namespace util {


const double Epsilon_double = 0.0001;
const float  Epsilon_float = 0.0001;


void
DefaultEpsilon(double &epsilon)
{
	epsilon = Epsilon_double;
}


void
DefaultEpsilon(float &epsilon)
{
	epsilon = Epsilon_float;
}


template <typename T>
T
WithinTolerance(T a, T b, T epsilon)
{
	return std::abs(a - b) < epsilon;
}


} // namespace util
} // namespace wr


#endif // __WRNAV_UTIL_MATH_H
