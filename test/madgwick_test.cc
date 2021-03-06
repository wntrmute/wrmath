#include <cmath>
#include <sstream>
#include <gtest/gtest.h>
#include <wrmath/geom/vector.h>
#include <wrmath/geom/quaternion.h>
#include <wrmath/math.h>
#include <wrmath/filter/madgwick.h>

using namespace std;
using namespace wr;


TEST(MadgwickFilter, SimpleAngularOrientation)
{
	filter::Madgwickd	mf;
	geom::Vector3d		gyro {0.174533, 0.0, 0.0}; // 10° X rotation.
	geom::Quaterniond	frame20Deg {0.984808, 0.173648, 0, 0}; // 20° final orientation.
	double 			delta = 0.00917; // assume 109 updates per second, as per the paper.
	double			twentyDegrees = math::DegreesToRadiansD(20.0);

	// The paper specifies a minimum of 109 IMU readings to stabilize; for
	// two seconds, that means 218 updates.
	for (int i = 0; i < 218; i++) {
		mf.updateAngularOrientation(gyro, delta);
	}

	EXPECT_EQ(mf.orientation(), frame20Deg);

	auto			euler = mf.euler();
	EXPECT_NEAR(euler[0], twentyDegrees, 0.01);
	EXPECT_NEAR(euler[1], 0.0, 0.01);
	EXPECT_NEAR(euler[2], 0.0, 0.01);
}


int
main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
