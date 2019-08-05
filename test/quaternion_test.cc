#include <sstream>
#include <gtest/gtest.h>
#include <wrmath/geom/quaternion.h>

using namespace std;
using namespace wr;


TEST(Quaterniond, Addition)
{
	geom::Quaterniond	p(geom::Vector3d {1.0, -2.0, 1.0}, 3.0);
	geom::Quaterniond	q(geom::Vector3d {-1.0, 2.0, 3.0}, 2.0);
	geom::Quaterniond	expected(geom::Vector3d{0.0, 0.0, 4.0}, 5.0);

	EXPECT_EQ(p + q, expected);
	EXPECT_EQ(expected - q, p);
	EXPECT_NE(expected - q, q); // exercise !=
}


TEST(Quaterniond, Norm)
{
	geom::Quaterniond	p(geom::Vector3d {0.9899139811480784, 9.387110042325054, 6.161341707794767},
			   5.563199889674063);
	double 			norm = 12.57016663729933;

	EXPECT_DOUBLE_EQ(p.norm(), norm);
}


TEST(Quaterniond, Product)
{
	geom::Quaterniond	p(geom::Vector3d {1.0, -2.0, 1.0}, 3.0);
	geom::Quaterniond	q(geom::Vector3d {-1.0, 2.0, 3.0}, 2.0);
	geom::Quaterniond	expected(geom::Vector3d{-9.0, -2.0, 11.0}, 8.0);

	EXPECT_EQ(p * q, expected);
}


TEST(Quaterniond, Identity)
{
	geom::Quaterniond	p(geom::Vector3d {1.0, -2.0, 1.0}, 3.0);
	geom::Quaterniond	q;

	EXPECT_EQ(p * q, p);
}


TEST(Quaternionf, Norm)
{
	geom::Quaternionf	p(geom::Vector3f {0.9899139811480784, 9.387110042325054, 6.161341707794767},
				   5.563199889674063);
	float 			norm = 12.57016663729933;

	EXPECT_DOUBLE_EQ(p.norm(), norm);
}


TEST(Quaternionf, Product)
{
	geom::Quaternionf	p(geom::Vector3f {1.0, -2.0, 1.0}, 3.0);
	geom::Quaternionf	q(geom::Vector3f {-1.0, 2.0, 3.0}, 2.0);
	geom::Quaternionf	expected(geom::Vector3f{-9.0, -2.0, 11.0}, 8.0);

	EXPECT_EQ(p * q, expected);
}


TEST(QuaternionMiscellaneous, SanityChecks)
{
	geom::Vector3d		v {1.0, 2.0, 3.0};
	double 			w = 4.0;
	geom::Quaterniond	p(v, w);

	EXPECT_EQ(p.axis(), v);
	EXPECT_DOUBLE_EQ(p.angle(), w);
}


TEST(QuaternionMiscellaneous, OutputStream)
{
	geom::Quaternionf	p(geom::Vector3f {1.0, 2.0, 3.0}, 4.0);
	geom::Quaterniond	q(geom::Vector3d {1.0, 2.0, 3.0}, 4.0);
	stringstream		ss;

	ss << p;
	EXPECT_EQ(ss.str(), "4 + <1, 2, 3>");
	ss.str("");

	ss << q;
	EXPECT_EQ(ss.str(), "4 + <1, 2, 3>");
}


int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
