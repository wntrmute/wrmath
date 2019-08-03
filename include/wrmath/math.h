#ifndef __WRMATH_UTIL_MATH_H
#define __WRMATH_UTIL_MATH_H


#include <cmath>


namespace wr {
namespace math {


/**
 * Convert radians to degrees.
 * @param rads the angle in radians
 * @return the angle in degrees,
 */
float	RadiansToDegreesF(float rads);
double	RadiansToDegreesD(double rads);
float	DegreesToRadiansF(float degrees);
double	DegreesToRadiansD(double degrees);



const double Epsilon_double = 0.0001;
const float  Epsilon_float = 0.0001;


void	DefaultEpsilon(double &epsilon);
void	DefaultEpsilon(float &epsilon);

template <typename T>
static T
WithinTolerance(T a, T b, T epsilon)
{
	return std::abs(a - b) < epsilon;
}


} // namespace math
} // namespace wr


#endif // __WRMATH_UTIL_MATH_H
