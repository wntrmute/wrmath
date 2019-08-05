#ifndef __WRMATH_QUATERNION_H
#define __WRMATH_QUATERNION_H


#include <cassert>
#include <cmath>
#include <initializer_list>
#include <wrmath/geom/vector.h>
#include <wrmath/math.h>


namespace wr {
namespace geom {


template <typename T>
class Quaternion {
public:
	// The default constructor returns the identity quaternion.
	Quaternion() : v(Vector<T, 3>()), w(1.0)
	{
		wr::math::DefaultEpsilon(this->eps);
	};


	Quaternion(Vector<T, 3> axis, T angle) : v(axis), w(angle)
	{
		wr::math::DefaultEpsilon(this->eps);
	};


	Quaternion
	operator+(const Quaternion<T> &other) const
	{
		return Quaternion(this->v + other.v, (this->w + other.w) % this->maxRotation);
	}


	Quaternion
	operator-(const Quaternion<T> &other) const
	{
	    return Quaternion(this->v - other.v, (this->w - other.w) % this->maxRotation);
	}


	Quaternion
	operator*(const Quaternion<T> &other) const
	{
		T		angle = (this->w * other.w) -
					(this->v * other.v);
		Vector<T, 3>	axis = (other.v * this->w) +
				       (this->v * other.w) +
				       (this->v.cross(other.v));
		return Quaternion(axis, angle);
	}


	bool
	operator==(const Quaternion<T> &other) const
	{
		return (this->v == other.v) &&
		       (wr::math::WithinTolerance(this->w, other.w, this->eps));
	}


	bool
	operator!=(const Quaternion<T> &other) const
	{
		return !(*this == other);
	}

private:
	static constexpr T	maxRotation = 4 * M_PI;

	Vector<T, 3>	v; // axis of rotation
	T		w; // angle of rotation
	T		eps;
};


typedef Quaternion<float>	Quaternionf;
typedef Quaternion<double>	Quaterniond;


} // namespace geom
} // namespace wr


#endif // WRMATH_QUATERNION_H
