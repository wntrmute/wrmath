#include <gtest/gtest.h>
#include <wrmath/geom/quaternion.h>

using namespace std;
using namespace wr;


TEST(Quaterniond, Addition)
{
	geom::Quaterniond	p(geom::Vector3d {1.0, -2.0, 1.0}, 3.0);
	geom::Quaterniond	q(geom::Vector3d {-1.0, 2.0, 3.0}, 2.0);
	geom::Quaterniond	expected(geom::Vector3d{-9.0, -2.0, 11.0}, 8.0);

	EXPECT_EQ(p * q, expected);
}


int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
