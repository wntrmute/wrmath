#include <gtest/gtest.h>
#include <wrmath/math.h>
#include <wrmath/geom/vector.h>
#include <wrmath/geom/orientation.h>

using namespace std;
using namespace wr;


TEST(UnitConversions, RadiansToDegreesF)
{
	for (int i = 0; i < 360; i++) {
		auto	deg = static_cast<float>(i);
		EXPECT_FLOAT_EQ(math::RadiansToDegreesF(math::DegreesToRadiansF(deg)), deg);
	}
}


TEST(UnitConversions, RadiansToDegreesD)
{
	for (int i = 0; i < 360; i++) {
		auto	deg = static_cast<double>(i);
		EXPECT_FLOAT_EQ(math::RadiansToDegreesD(math::DegreesToRadiansD(deg)), deg);
	}
}


TEST(Orientation2f, Heading)
{
	geom::Vector2f	a {2.0, 2.0};

	EXPECT_FLOAT_EQ(geom::Heading2f(a), math::DegreesToRadiansF(45));
}


TEST(Orientation3f, Heading)
{
	geom::Vector3f	a {2.0, 2.0, 2.0};

	EXPECT_FLOAT_EQ(geom::Heading3f(a), math::DegreesToRadiansF(45));
}


TEST(Orientation2d, Heading)
{
	geom::Vector2d	a {2.0, 2.0};

	EXPECT_NEAR(geom::Heading2d(a), math::DegreesToRadiansF(45), 0.000001);
}


TEST(Orientation3d, Heading)
{
	geom::Vector3d	a {2.0, 2.0, 2.0};

	EXPECT_NEAR(geom::Heading3d(a), math::DegreesToRadiansF(45), 0.000001);
}


int
main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
