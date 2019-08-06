#ifndef __WRMATH_GEOM_VECTOR_H
#define __WRMATH_GEOM_VECTOR_H


#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <ostream>
#include <iostream>

#include <wrmath/math.h>


// This implementation is essentially a C++ translation of a Python library
// I wrote for Coursera's "Linear Algebra for Machine Learning" course. Many
// of the test vectors come from quiz questions in the class.


namespace wr {
namespace geom {


/**
 * Vector provides a standard interface for dimensionless fixed-size
 * vectors. Once instantiated, they cannot be modified. Note that while
 * the type is generic, it's intended to be used with floating-point
 * types. They can be indexed like arrays, and they contain an epsilon
 * value that defines a tolerance for equality.
 */
template <typename T, size_t N>
class Vector {
public:
    	/**
    	 * The default constructor creates a unit vector for a given
    	 * type and size.
    	 */
	Vector()
	{
		T	unitLength = (T)1.0 / std::sqrt(N);
		for (size_t i = 0; i < N; i++) {
			this->arr[i] = unitLength;
		}

		wr::math::DefaultEpsilon(this->epsilon);
	}

	/**
	 * If given an initializer_list, the vector is created with
	 * those values. There must be exactly N elements in the list.
	 * @param ilst An intializer list with N elements of type T.
	 */
	Vector(std::initializer_list<T>	ilst)
	{
		assert(ilst.size() == N);

		wr::math::DefaultEpsilon(this->epsilon);
		std::copy(ilst.begin(), ilst.end(), this->arr.begin());
	}	


	/**
	 * Magnitude computes the length of the vector.
	 * @return The length of the vector.
	 */
	T magnitude() const {
		T	result = 0;

		for (size_t i = 0; i < N; i++) {
			result += (this->arr[i] * this->arr[i]);
		}
		return std::sqrt(result);
	};


	/**
	 * Set the tolerance for equality checks. At a minimum, this allows
	 * for systemic errors in floating math arithmetic.
	 *
	 * @param eps is the maximum difference between this vector and
	 *            another.
	 */
	void
	setEpsilon(T eps)
	{
		this->epsilon = eps;
	}


	/**
	 * Determine whether this is a zero vector.
	 * @return true if the vector is zero.
	 */
	bool
	isZero() const
	{
		for (size_t i = 0; i < N; i++) {
			if (!wr::math::WithinTolerance(this->arr[i], (T)0.0, this->epsilon)) {
				return false;
			}
		}
		return true;
	}


	/**
	 * Obtain the unit vector for this vector.
	 * @return The unit vector
	 */
	Vector
	unitVector() const
	{
		return *this / this->magnitude();
	}


	/**
	 * Determine if this is a unit vector, e.g. if its length is 1.
	 * @return true if the vector is a unit vector.
	 */
	bool
	isUnitVector() const
	{
		return wr::math::WithinTolerance(this->magnitude(), (T)1.0, this->epsilon);
	}


	/**
	 * Compute the angle between two other vectors.
	 * @param other Another vector.
	 * @return The angle in radians between the two vectors.
	 */
	T
	angle(const Vector<T, N> &other) const
	{
		Vector<T, N>	unitA = this->unitVector();
		Vector<T, N>	unitB = other.unitVector();

		// Can't compute angles with a zero vector.
		assert(!this->isZero());
		assert(!other.isZero());
		return std::acos(unitA * unitB);
	}


	/**
	 * Determine whether two vectors are parallel.
	 * @param other Another vector
	 * @return True if the angle between the vectors is zero.
	 */
	bool
	isParallel(const Vector<T, N> &other) const
	{
		if (this->isZero() || other.isZero()) {
			return true;
		}

		T angle = this->angle(other);
		if (wr::math::WithinTolerance(angle, (T)0.0, this->epsilon)) {
			return true;
		}

		return false;
	}


	/**
	 * Determine if two vectors are orthogonal or perpendicular to each
	 * other.
	 * @param other Another vector
	 * @return True if the two vectors are orthogonal.
	 */
	bool
	isOrthogonal(const Vector<T, N> &other) const
	{
		if (this->isZero() || other.isZero()) {
			return true;
		}

		return wr::math::WithinTolerance(*this * other, (T)0.0, this->epsilon);
	}


	/**
	 * Project this vector onto some basis vector.
	 * @param basis The basis vector to be projected onto.
	 * @return A vector that is the projection of this onto the basis
	 *         vector.
	 */
	Vector
	projectParallel(const Vector<T, N> &basis) const
	{
		Vector<T, N>	unit_basis = basis.unitVector();

		return unit_basis * (*this * unit_basis);
	}


	/**
	 * Project this vector perpendicularly onto some basis vector.
	 * This is also called the rejection of the vector.
	 * @param basis The basis vector to be projected onto.
	 * @return A vector that is the orthogonal projection of this onto
	 *         the basis vector.
	 */
	Vector
	projectOrthogonal(const Vector<T, N> &basis)
	{
		Vector<T, N>	spar = this->projectParallel(basis);
		return *this - spar;
	}


	/**
	 * Compute the cross product of two vectors. This is only defined
	 * over three-dimensional vectors.
	 * @param other Another 3D vector.
	 * @return The cross product vector.
	 */
	Vector
	cross(const Vector<T, N> &other) const
	{
		assert(N == 3);
		return Vector<T, N> {
			(this->arr[1] * other.arr[2]) - (other.arr[1] * this->arr[2]),
			-((this->arr[0] * other.arr[2]) - (other.arr[0] * this->arr[2])),
			(this->arr[0] * other.arr[1]) - (other.arr[0] * this->arr[1])
		};
	}


	/**
	 * Perform vector addition with another vector.
	 * @param other The vector to be added.
	 * @return A new vector that is the result of adding this and the
	 *         other vector.
	 */
	Vector
	operator+(const Vector<T, N> &other) const
	{
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] + other.arr[i];
		}

		return vec;
	}


	/**
	 * Perform vector subtraction with another vector.
	 * @param other The vector to be subtracted from this vector.
	 * @return A new vector that is the result of subtracting the
	 *         other vector from this one.
	 */
	Vector
	operator-(const Vector<T, N> &other) const
	{
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] - other.arr[i];
		}

		return vec;
	}


	/**
	 * Perform scalar multiplication of this vector by some scale factor.
	 * @param k The scaling value.
	 * @return A new vector that is this vector scaled by k.
	 */
	Vector
	operator*(const T k) const
	{
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] * k;
		}

		return vec;
	}


	/**
	 * Perform scalar division of this vector by some scale factor.
	 * @param k The scaling value
	 * @return A new vector that is this vector scaled by 1/k.
	 */
	Vector
	operator/(const T k) const
	{
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] / k;
		}

		return vec;
	}


	/**
	 * Compute the dot product between two vectors.
	 * @param other The other vector.
	 * @return A scalar value that is the dot product of the two vectors.
	 */
	T
	operator*(const Vector<T, N> &other) const
	{
		T	result = 0;

		for (size_t i = 0; i < N; i++) {
			result += (this->arr[i] * other.arr[i]);
		}

		return result;
	}


	/**
	 * Compare two vectors for equality.
	 * @param other The other vector.
	 * @return Return true if all the components of both vectors are
	 *         within the tolerance value.
	 */
	bool
	operator==(const Vector<T, N> &other) const
	{
		for (size_t i = 0; i<N; i++) {
			if (!wr::math::WithinTolerance(this->arr[i], other.arr[i], this->epsilon)) {
				return false;
			}
		}
		return true;
	}


	/**
	 * Compare two vectors for inequality.
	 * @param other The other vector.
	 * @return Return true if any of the components of both vectors are
	 *         not within the tolerance value.
	 */
	bool
	operator!=(const Vector<T, N> &other) const
	{
		return !(*this == other);
	}


	/**
	 * Support array indexing into vector.
	 * @param i The component index.
	 * @return The value of the vector component at i.
	 */
	T
	operator[](size_t i) const
	{
		return this->arr[i];
	}


	/**
	 * Support outputting vectors in the form "<i, j, ...>".
	 * @param outs An output stream.
	 * @param vec The vector to be formatted.
	 * @return The output stream.
	 */
	friend std::ostream&
	operator<<(std::ostream& outs, const Vector<T, N>& vec)
	{
		outs << "<";
		for (size_t i = 0; i < N; i++) {
			outs << vec.arr[i];
			if (i < (N-1)) {
				outs << ", ";
			}
		}
		outs << ">";
		return outs;
	}

private:
	static const size_t	dim = N;
	T			epsilon;
	std::array<T, N>	arr;
};


/**
 * A number of shorthand aliases for vectors are provided. They follow
 * the form of VectorNt, where N is the dimension and t is the type.
 * For example, a 2D float vector is Vector2f.
 */

typedef Vector<float,  2>	Vector2f;
typedef Vector<float,  3>	Vector3f;
typedef Vector<float,  4>	Vector4f;

typedef Vector<double,  2>	Vector2d;
typedef	Vector<double, 3>	Vector3d;
typedef Vector<double, 4>	Vector4d;


} // namespace geom
} // namespace wr


#endif //  __WRMATH_GEOM_VECTOR_H
