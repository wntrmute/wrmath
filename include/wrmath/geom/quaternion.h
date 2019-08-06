#ifndef __WRMATH_QUATERNION_H
#define __WRMATH_QUATERNION_H


#include <cassert>
#include <cmath>
#include <ostream>
#include <wrmath/geom/vector.h>
#include <wrmath/math.h>


namespace wr {
namespace geom {


/**
 * Quaternions encode rotations in three-dimensional space. While technically
 * a quaternion is comprised of a real element and a complex vector<3>, for
 * the purposes of this library, it is modeled as a floating point 4D vector.
 *
 * For information on the underlying vector type, see the documentation for
 * wr::geom::Vector.
 *
 * The constructors are primarily intended for intended operations; in practice,
 * the quaternionf and quaterniond functions are more useful for constructing
 * quaternions from vectors and angles.
 *
 * Like vectors, quaternions carry an internal tolerance value ε that is used for
 * floating point comparisons. The wr::math namespace contains the default values
 * used for this; generally, a tolerance of 0.0001 is considered appropriate for
 * the uses of this library. The tolerance can be explicitly set with the
 * setEpsilon method.
 */
template <typename T>
class Quaternion {
public:
	/**
	 * The default Quaternion constructor returns an identity quaternion.
	 */
	Quaternion() : v(Vector<T, 3> {0.0, 0.0, 0.0}), w(1.0)
	{
		wr::math::DefaultEpsilon(this->eps);
		v.setEpsilon(this->eps);
		this->constrainAngle();
	};


	/**
	 * A Quaternion may be initialised with a Vector<T, 3> axis of rotation
	 * and an angle of rotation. This doesn't do the angle transforms to simplify
	 * internal operations.
	 * @param _axis A three-dimensional vector of the same type as the Quaternion.
	 * @param _angle The angle of rotation about the axis of rotation.
	 */
	Quaternion(Vector<T, 3> _axis, T _angle) : v(_axis), w(_angle)
	{
		wr::math::DefaultEpsilon(this->eps);
		this->constrainAngle();
		v.setEpsilon(this->eps);
	};

	/**
	 * A Quaternion may be initialised with a Vector<T, 4> comprised of the axis of rotation
	 * followed by the angle of rotation.
	 * @param vector A vector in the form <i, j, k, w>.
	 */
	Quaternion(Vector<T, 4> vector) :
		v(Vector<T, 3> {vector[0], vector[1], vector[2]}),
		w(vector[3])
	{
		wr::math::DefaultEpsilon(this->eps);
		this->constrainAngle();
		v.setEpsilon(this->eps);
	}


	/**
	 * Set the comparison tolerance for this quaternion.
	 * @param epsilon A tolerance value.
	 */
	void
	setEpsilon(T epsilon)
	{
		this->eps = epsilon;
		this->v.setEpsilon(epsilon);
	}


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
	norm() const
	{
		T	n = 0;

		n += (this->v[0] * this->v[0]);
		n += (this->v[1] * this->v[1]);
		n += (this->v[2] * this->v[2]);
		n += (this->w * this->w);

		return std::sqrt(n);
	}


	/**
	 * Compute the conjugate of a quaternion.
	 * @return The conjugate of this quaternion.
	 */
	Quaternion
	conjugate() const
	{
		return Quaternion(Vector<T, 4> {-this->v[0], -this->v[1], -this->v[2], this->w});
	}


	/**
	 * Compute the inverse of a quaternion.
	 * @return The inverse of this quaternion.
	 */
	Quaternion
	inverse() const
	{
		T	_norm = this->norm();

		return this->conjugate() / (_norm * _norm);
	}


	/**
	 * Determine whether this is a unit quaternion.
	 * @return true if this is a unit quaternion.
	 */
	bool
	isUnitQuaternion() const
	{
		return wr::math::WithinTolerance(this->norm(), (T)1.0, this->eps);
	}


	/**
	 * Return the quaternion as a Vector<T, 4>, with the axis of rotation
	 * followed by the angle of rotation.
	 * @return A vector representation of the quaternion.
	 */
	Vector<T, 4>
	asVector() const
	{
		return Vector<T, 4> {this->v[0], this->v[1], this->v[2], this->w};
	}


	/**
	 * Rotate vector v about this quaternion.
	 * @param v The vector to be rotated.
	 * @return The rotated vector.
	 */
	Vector<T, 3>
	rotate(Vector<T, 3> v) const
	{
		return (this->conjugate() * v * (*this)).axis();
	}


	/**
	 * Return the Euler angles for this quaternion as a vector of
	 * <yaw, pitch, roll>. Users of this function should watch out
	 * for gimball lock.
	 * @return A vector<T, 3> containing <yaw, pitch, roll>
	 */
	Vector<T, 3>
	euler() const
	{
		T	yaw, pitch, roll;
		T	a = this->w, a2 = a * a;
		T	b = this->v[0], b2 = b * b;
		T	c = this->v[1], c2 = c * c;
		T	d = this->v[2], d2 = d * d;

		yaw = std::atan2(2 * ((a*b) + (c * d)), a2 - b2 - c2 + d2);
		pitch = std::asin(2 * ((b*d) - (a*c)));
		roll = std::atan2(2 * ((a * d) + (b * c)), a2 + b2 - c2 - d2);
		
		return Vector<T, 3> {yaw, pitch, roll};
	}

	/**
	 * Perform quaternion addition with another quaternion.
	 * @param other The quaternion to be added with this one.
	 * @return The result of adding the two quaternions together.
	 */
	Quaternion
	operator+(const Quaternion<T> &other) const
	{
		return Quaternion(this->v + other.v, this->w + other.w);
	}


	/**
	 * Perform quaternion subtraction with another quaternion.
	 * @param other The quaternion to be subtracted from this one.
	 * @return The result of subtracting the other quaternion from this one.
	 */
	Quaternion
	operator-(const Quaternion<T> &other) const
	{
	    return Quaternion(this->v - other.v, this->w - other.w);
	}


	/**
	 * Perform scalar multiplication.
	 * @param k The scaling value.
	 * @return A scaled quaternion.
	 */
	Quaternion
	operator*(const T k) const
	{
		return Quaternion(this->v * k, this->w * k);
	}


	/** Perform scalar division.
	 * @param k The scalar divisor.
	 * @return A scaled quaternion.
	 */
	Quaternion
	operator/(const T k) const
	{
		return Quaternion(this->v / k, this->w / k);
	}


	/**
	 * Perform quaternion Hamilton multiplication with a three-
	 * dimensional vector; this is done by treating the vector
	 * as a pure quaternion (e.g. with an angle of rotation of 0).
	 * @param vector The vector to multiply with this quaternion.
	 * @return The Hamilton product of the quaternion and vector.
	 */
	Quaternion
	operator*(const Vector<T, 3> &vector) const
	{
		return Quaternion(vector * this->w + this->v.cross(vector),
				  (T)0.0);
	}


	/**
	 * Perform quaternion Hamilton multiplication.
	 * @param other The other quaternion to multiply with this one.
	 * @result The Hamilton product of the two quaternions.
	 */
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


	/**
	 * Perform quaternion equality checking.
	 * @param other The quaternion to check equality against.
	 * @return True if the two quaternions are equal within their tolerance.
	 */
	bool
	operator==(const Quaternion<T> &other) const
	{
		return (this->v == other.v) &&
		       (wr::math::WithinTolerance(this->w, other.w, this->eps));
	}


	/**
	 * Perform quaternion inequality checking.
	 * @param other The quaternion to check inequality against.
	 * @return True if the two quaternions are unequal within their tolerance.
	 */
	bool
	operator!=(const Quaternion<T> &other) const
	{
		return !(*this == other);
	}


	/**
	 * Support stream output of a quaternion in the form `a + <i, j, k>`.
	 * TODO: improve the formatting.
	 * @param outs An output stream
	 * @param q A quaternion
	 * @return The output stream
	 */
	friend std::ostream&
	operator<<(std::ostream& outs, const Quaternion<T>& q)
	{
		outs << q.w << " + " << q.v;
		return outs;
	}

private:
	static constexpr T	minRotation = -4 * M_PI;
	static constexpr T	maxRotation = 4 * M_PI;

	Vector<T, 3>	v; // axis of rotation
	T		w; // angle of rotation
	T		eps;

	void
	constrainAngle()
	{
		if (this->w < 0.0) {
			this->w = std::fmod(this->w, this->minRotation);
		}
		else {
			this->w = std::fmod(this->w, this->maxRotation);
		}
	}
};


/**
 * Type aliases are provided for float and double quaternions.
 */
typedef Quaternion<float>	Quaternionf;
typedef Quaternion<double>	Quaterniond;


/**
 * Return a float quaternion scaled appropriately from a vector and angle,
 * e.g. angle = cos(angle / 2), axis.unitVector() * sin(angle / 2).
 * @param axis The axis of rotation.
 * @param angle The angle of rotation.
 * @return A quaternion.
 */
static Quaternionf
quaternionf(Vector3f axis, float angle)
{
	return Quaternionf(axis.unitVector() * std::sin(angle / 2.0),
			   std::cos(angle / 2.0));
}


/**
 * Return a double quaternion scaled appropriately from a vector and angle,
 * e.g. angle = cos(angle / 2), axis.unitVector() * sin(angle / 2).
 * @param axis The axis of rotation.
 * @param angle The angle of rotation.
 * @return A quaternion.
 */
static Quaterniond
quaterniond(Vector3d axis, double angle)
{
	return Quaterniond(axis.unitVector() * std::sin(angle / 2.0),
			   std::cos(angle / 2.0));
}


/**
 * Given a vector of Euler angles in ZYX sequence (e.g. yaw, pitch, roll),
 * return a quaternion.
 * @param euler A vector Euler angle in ZYX sequence.
 * @return A Quaternion representation of the orientation represented
 *         by the Euler angles.
 */
static Quaternionf
quaternionf_from_euler(Vector3f euler)
{
	float	x, y, z, w;
	euler = euler / 2.0;

	float	cos_yaw   = std::cos(euler[0]);
	float	cos_pitch = std::cos(euler[1]);
	float	cos_roll  = std::cos(euler[2]);
	float	sin_yaw   = std::sin(euler[0]);
	float	sin_pitch = std::sin(euler[1]);
	float	sin_roll  = std::sin(euler[2]);
	
	x = (sin_yaw * cos_pitch * cos_roll) + (cos_yaw * sin_pitch * sin_roll);
	y = (sin_yaw * cos_pitch * sin_roll) - (cos_yaw * sin_pitch * cos_roll);
	z = (cos_yaw * cos_pitch * sin_roll) + (sin_yaw * sin_pitch * cos_roll);
	w = (cos_yaw * cos_pitch * cos_roll) - (sin_yaw * sin_pitch * sin_roll);

	return Quaternionf(Vector4f {x, y, z, w});
}


/**
 * Given a vector of Euler angles in ZYX sequence (e.g. yaw, pitch, roll),
 * return a quaternion.
 * @param euler A vector Euler angle in ZYX sequence.
 * @return A Quaternion representation of the orientation represented
 *         by the Euler angles.
 */
static Quaterniond
quaterniond_from_euler(Vector3d euler)
{
	double	x, y, z, w;
	euler = euler / 2.0;

	double	cos_yaw   = std::cos(euler[0]);
	double	cos_pitch = std::cos(euler[1]);
	double	cos_roll  = std::cos(euler[2]);
	double	sin_yaw   = std::sin(euler[0]);
	double	sin_pitch = std::sin(euler[1]);
	double	sin_roll  = std::sin(euler[2]);
	
	x = (sin_yaw * cos_pitch * cos_roll) + (cos_yaw * sin_pitch * sin_roll);
	y = (sin_yaw * cos_pitch * sin_roll) - (cos_yaw * sin_pitch * cos_roll);
	z = (cos_yaw * cos_pitch * sin_roll) + (sin_yaw * sin_pitch * cos_roll);
	w = (cos_yaw * cos_pitch * cos_roll) - (sin_yaw * sin_pitch * sin_roll);

	return Quaterniond(Vector4d {x, y, z, w});
}


// Helpful references for understanding quaternions:
// + "Intro to Quaternions" - https://www.youtube.com/watch?v=fKIss4EV6ME
//   15 minutes into this video I had a more intuitive understanding.
// + "Quaternions and Rotations" - http://graphics.stanford.edu/courses/cs348a-17-winter/Papers/quaternion.pdf
// + "Understanding Quaternions" - http://www.chrobotics.com/library/understanding-quaternions


} // namespace geom
} // namespace wr


#endif // WRMATH_QUATERNION_H
