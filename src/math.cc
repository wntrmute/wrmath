#include <wrmath/math.h>


namespace wr {
namespace math {


float
RadiansToDegreesF(float rads)
{
	return rads * (180.0 / M_PI);
}


double
RadiansToDegreesD(double rads)
{
	return rads * (180.0 / M_PI);
}


float
DegreesToRadiansF(float degrees)
{
	return degrees * M_PI / 180.0;
}


double
DegreesToRadiansD(double degrees)
{
	return degrees * M_PI / 180.0;
}


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


} // namespace math
} // namespace wr

