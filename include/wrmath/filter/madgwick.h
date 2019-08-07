/// \file madgwick.h
/// \brief Implementation of a Madgwick filter.
///
/// See [the paper](http://x-io.co.uk/res/doc/madgwick_internal_report.pdf).
#ifndef __WRMATH_FILTER_MADGWICK_H
#define __WRMATH_FILTER_MADGWICK_H


#include <wrmath/geom/vector.h>
#include <wrmath/geom/quaternion.h>


namespace wr {
/// filter contains filtering algorithms.
namespace filter {


/// Madgwick implements an efficient orientation filter for IMUs.
///
/// \tparam T A floating point type.
template <typename T>
class Madgwick {
public:
	/// The Madgwick filter is initialised with an identity quaternion.
	Madgwick() : deltaT(0.0), previousSensorFrame(), sensorFrame() {};


	/// The Madgwick filter is initialised with a sensor frame.
	///
	/// \param sf A sensor frame; if zero, the sensor frame will be
	///           initialised as an identity quaternion.
	Madgwick(geom::Vector<T, 3> sf) : deltaT(0.0), previousSensorFrame()
	{
		if (!sf.isZero()) {
			sensorFrame = geom::quaternion(sf, 0.0);
		}
	}


	/// Initialise the filter with a sensor frame quaternion.
	///
	/// \param sf A quaternion representing the current orientation.
	Madgwick(geom::Quaternion<T> sf) :
		deltaT(0.0), previousSensorFrame(), sensorFrame(sf) {};


	/// Return the current orientation as measured by the filter.
	///
	/// \return The current sensor frame.
	geom::Quaternion<T>
	orientation() const
	{
		return this->sensorFrame;
	}


	/// Return the rate of change of the orientation of the earth frame
	/// with respect to the sensor frame.
	///
	/// \param gyro A three-dimensional vector containing gyro readings
	///             as \f$<\omega_x, \omega_y, \omega_z\>f$.
	/// \return A quaternion representing the rate of angular change.
	geom::Quaternion<T>
	angularRate(const geom::Vector<T, 3> &gyro) const
	{
		return (this->sensorFrame * 0.5) * geom::Quaternion<T>(gyro, 0.0);
	}

	/// Update the sensor frame to a new frame.
	///
	void
	updateFrame(const geom::Quaternion<T> &sf, T delta)
	{
		this->previousSensorFrame = this->sensorFrame;
		this->sensorFrame = sf;
		this->deltaT = delta;
	}


	/// Update the sensor frame with a gyroscope reading.
	///
	/// \param gyro A three-dimensional vector containing gyro readings
	///             as \f$<\omega_{x}, \omega_y, \omega_z>\f$.
	/// \param delta The time step between readings. It must not be zero.
	void
	updateAngularOrientation(const geom::Vector<T, 3> &gyro, T delta)
	{
		assert(!math::WithinTolerance(delta, 0.0, 0.001));
		geom::Quaternion<T>	q = this->angularRate(gyro) * delta;

		this->updateFrame(this->sensorFrame + q, delta);
	}

private:
	T			deltaT;
	geom::Quaternion<T>	previousSensorFrame;
	geom::Quaternion<T>	sensorFrame;
};


} // namespace filter
} // namespace wr


#endif // __WRMATH_FILTER_MADGWICK_H
