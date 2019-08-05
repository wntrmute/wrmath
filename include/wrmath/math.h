#ifndef __WRMATH_UTIL_MATH_H
#define __WRMATH_UTIL_MATH_H


#include <cmath>


namespace wr {
namespace math {


/**
 * Convert radians to degrees.
 * @param rads the angle in radians
 * @return the angle in degrees.
 */
float	RadiansToDegreesF(float rads);

/**
 * Convert radians to degrees.
 * @param rads the angle in radians
 * @return the angle in degrees.
 */
double	RadiansToDegreesD(double rads);

/**
 * Convert degrees to radians.
 * @param degrees the angle in degrees
 * @return the angle in radians.
 */
float	DegreesToRadiansF(float degrees);

/**
 * Convert degrees to radians.
 * @param degrees the angle in degrees
 * @return the angle in radians.
 */
double	DegreesToRadiansD(double degrees);


/**
 * Get the default epsilon value.
 * @param epsilon The variable to store the epsilon value in.
 */
void	DefaultEpsilon(double &epsilon);

/**
 * Get the default epsilon value.
 * @param epsilon The variable to store the epsilon value in.
 */
void	DefaultEpsilon(float &epsilon);


/**
 * Return whether the two values of type T are equal to within some tolerance.
 * @tparam T The type of value
 * @param a A value of type T used as the left-hand side of an equality check.
 * @param b A value of type T used as the right-hand side of an equality check.
 * @param epsilon The tolerance value.
 * @return Whether the two values are "close enough" to be considered equal.
 */
template <typename T>
static T
WithinTolerance(T a, T b, T epsilon)
{
	return std::abs(a - b) < epsilon;
}


} // namespace math
} // namespace wr


#endif // __WRMATH_UTIL_MATH_H
