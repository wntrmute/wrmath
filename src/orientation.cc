#include <cmath>
#include <wrmath/geom/orientation.h>


namespace wr {
namespace geom {


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
{return degrees * M_PI / 180.0;
	return degrees * M_PI / 180.0;
}


float
Heading2f(Vector2f vec)
{
	return vec.angle(Basis2f[Basis_i]);
}


float
Heading3f(Vector3f vec)
{
	Vector2f	vec2f {vec[0], vec[1]};
	return Heading2f(vec2f);
}


double
Heading2d(Vector2d vec)
{
	return vec.angle(Basis2d[Basis_i]);
}


double
Heading3d(Vector3d vec)
{
	Vector2d	vec2d {vec[0], vec[1]};
	return Heading2d(vec2d);
}


} // namespace geom
} // namespace wr
