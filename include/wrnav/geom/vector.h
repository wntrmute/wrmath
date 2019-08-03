#ifndef __WRNAV_GEOM_VECTOR_H
#define __WRNAV_GEOM_VECTOR_H


#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <ostream>
#include <iostream>

#include <wrnav/util/math.h>


namespace wr {
namespace geom {

template <typename T, size_t N>
class Vector {
public:
	Vector() { wr::util::DefaultEpsilon(this->epsilon); }

	Vector(std::initializer_list<T>	ilst)
	{
		assert(ilst.size() == N);

		wr::util::DefaultEpsilon(this->epsilon);
		std::copy(ilst.begin(), ilst.end(), this->arr.begin());
	}	


	T magnitude() const {
		T	result = 0;

		for (size_t i = 0; i < N; i++) {
			result += (this->arr[i] * this->arr[i]);
		}
		return std::sqrt(result);
	};


	void
	setEpsilon(T epsilon)
	{
		this->epsilon = epsilon;
	}


	bool
	isZero() const
	{
		for (size_t i = 0; i < N; i++) {
			if (!wr::util::WithinTolerance(this->arr[i], 0.0, this->epsilon)) {
				return false;
			}
		}
		return true;
	}


	Vector
	unitVector() const
	{
		return *this / this->magnitude();
	}


	T
	angle(const Vector<T, N> &rhs) const
	{
		Vector<T, N>	unitA = this->unitVector();
		Vector<T, N>	unitB = rhs.unitVector();

		return std::acos(unitA * unitB);
	}


	Vector operator+(const Vector<T, N> &rhs) const {
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] + rhs.arr[i];
		}

		return vec;
	}


	Vector operator-(const Vector<T, N> &rhs) const {
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] - rhs.arr[i];
		}

		return vec;
	}


	// Scalar multiplication.
	Vector operator*(const T k) const {
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] * k;
		}

		return vec;
	}


	// Scalar division.
	Vector operator/(const T k) const {
		Vector<T, N>	vec;

		for (size_t i = 0; i < N; i++) {
			vec.arr[i] = this->arr[i] / k;
		}

		return vec;
	}


	// Dot product.
	T operator*(const Vector<T, N> &rhs) const {
		T	result = 0;

		for (size_t i = 0; i < N; i++) {
			result += (this->arr[i] * rhs.arr[i]);
		}

		return result;
	}


	bool operator==(const Vector<T, N> &rhs) const {
		for (size_t i = 0; i<N; i++) {
			if (!wr::util::WithinTolerance(this->arr[i], rhs.arr[i], this->epsilon)) {
				return false;
			}
		}
		return true;
	}


	bool operator!=(const Vector<T, N> &rhs) const {
		return !(*this == rhs);
	}


	friend std::ostream& operator<<(std::ostream& outs, const Vector<T, N>& vec) {
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


typedef Vector<float,  3>	Vector3f;
typedef Vector<float,  4>	Vector4f;
typedef	Vector<double, 3>	Vector3d;
typedef Vector<double, 4>	Vector4d;


} // namespace geom
} // namespace wr


#endif //  __WRNAV_GEOM_VECTOR_H
