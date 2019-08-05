#ifndef __WRMATH_QUATERNION_H
#define __WRMATH_QUATERNION_H


#include <cassert>
#include <cmath>
#include <ostream>
#include <wrmath/geom/vector.h>
#include <wrmath/math.h>


namespace wr {
namespace geom {


template <typename T>
class Quaternion {
public:
	/**
	 * The default Quaternion constructor returns an identity quaternion.
	 */
	Quaternion() : v(Vector<T, 3>()), w(1.0)
	{
		wr::math::DefaultEpsilon(this->eps);
		this->w = std::fmod(this->w, this->maxRotation);
	};


	/**
	 * A Quaternion may be initialised with a Vector<T, 3> axis of rotation
	 * and an angle of rotation.
	 * @param _axis A three-dimensional vector of the same type as the Quaternion.
	 * @param _angle The angle of rotation about the axis of rotation.
	 */
	Quaternion(Vector<T, 3> _axis, T _angle) : v(_axis), w(_angle)
	{
		wr::math::DefaultEpsilon(this->eps);
		this->w = std::fmod(this->w, this->maxRotation);
	};


	/**
	 * Return the axis of rotation of this quaternion.
	 * @return The axis of rotation of this quaternion.
	 */
	Vector<T, 3>
	axis() const
	{
		return this->v;
	}


	/**
	 * Return the angle of rotation of this quaternion.
	 * @return the angle of rotation of this quaternion.
	 */
	T
	angle() const
	{
		return this->w;
	}


	/**
	 * Compute the norm of a quaternion. Treating the Quaternion as a
	 * Vector<T, 4>, it's the same as computing the magnitude.
	 * @return A non-negative real number.
	 */
	T
	norm()
	{
		T	n = 0;

		n += (this->v[0] * this->v[0]);
		n += (this->v[1] * this->v[1]);
		n += (this->v[2] * this->v[2]);
		n += (this->w * this->w);

		return std::sqrt(n);
	}


	Vector<T, 4>
	asVector()
	{
		return Vector<T, 4> {this->v[0], this->v[1], this->v[2], this->w};
	}


	/**
	 * Perform quaternion addition with another quaternion.
	 * @param other The quaternion to be added with this one.
	 * @return
	 */
	Quaternion
	operator+(const Quaternion<T> &other) const
	{
		return Quaternion(this->v + other.v, this->w + other.w);
	}


	Quaternion
	operator-(const Quaternion<T> &other) const
	{
	    return Quaternion(this->v - other.v, this->w - other.w);
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


	friend std::ostream&
	operator<<(std::ostream& outs, const Quaternion<T>& q)
	{
		outs << q.w << " + " << q.v;
		return outs;
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
