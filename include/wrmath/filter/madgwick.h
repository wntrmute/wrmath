/// \file madgwick.h
/// \brief Implementation of a Madgwick filter.
///
/// See
#ifndef __WRMATH_FILTER_MADGWICK_H
#define __WRMATH_FILTER_MADGWICK_H


#include <wrmath/geom/vector.h>
#include <wrmath/geom/quaternion.h>


/// wr contains the wntrmute robotics code.
namespace wr {
/// filter contains filtering algorithms.
namespace filter {


/// @brief Madgwick implements an efficient orientation filter for IMUs.
///
/// Madgwick is a  novel  orientation  filter  applicable  to  IMUs
/// consisting of tri-axis  gyroscopes  and  accelerometers,  and  MARG
/// sensor  arrays  that  also  include tri-axis magnetometers.  The MARG
/// implementation incorporates magnetic distortionand  gyroscope  bias
/// drift  compensation.
///
/// It is described in the paper [An efficient orientation filter for inertial and inertial/magnetic sensor arrays](http://x-io.co.uk/res/doc/madgwick_internal_report.pdf).
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
	///             as w_x, w_y, w_z.
	/// \return A quaternion representing the rate of angular change.
	geom::Quaternion<T>
	angularRate(const geom::Vector<T, 3> &gyro) const
	{
		return (this->sensorFrame * 0.5) * geom::Quaternion<T>(gyro, 0.0);
	}

	/// Update the sensor frame to a new frame.
	///
	/// \param sf The new sensor frame replacing the previous one.
	/// \param delta The time delta since the last update.
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
	///             as w_x, w_y, w_z.
	/// \param delta The time step between readings. It must not be zero.
	void
	updateAngularOrientation(const geom::Vector<T, 3> &gyro, T delta)
	{
		assert(!math::WithinTolerance(delta, 0.0, 0.001));
		geom::Quaternion<T>	q = this->angularRate(gyro) * delta;

		this->updateFrame(this->sensorFrame + q, delta);
	}


	/// Retrieve a vector of the Euler angles in ZYX orientation.
	///
	/// \return A vector of Euler angles as <ψ, θ, ϕ>.
	geom::Vector<T, 3>
	euler()
	{
		return this->sensorFrame.euler();
	}

private:
	T			deltaT;
	geom::Quaternion<T>	previousSensorFrame;
	geom::Quaternion<T>	sensorFrame;
};


/// Madgwickd is a shorthand alias for a Madgwick<double>.
typedef Madgwick<double>	Madgwickd;

/// Madgwickf is a shorthand alias for a Madgwick<float>.
typedef Madgwick<float>		Madgwickf;


} // namespace filter
} // namespace wr


#endif // __WRMATH_FILTER_MADGWICK_H
