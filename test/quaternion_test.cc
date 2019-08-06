#include <cmath>
#include <sstream>
#include <gtest/gtest.h>
#include <wrmath/geom/quaternion.h>

using namespace std;
using namespace wr;


TEST(Quaternion, SelfTest)
{
	geom::Quaternion_SelfTest();
}


TEST(Quaterniond, Addition)
{
	geom::Quaterniond	p(geom::Vector4d {1.0, -2.0, 1.0, 3.0});
	geom::Quaterniond	q(geom::Vector4d {-1.0, 2.0, 3.0, 2.0});
	geom::Quaterniond	expected(geom::Vector4d{0.0, 0.0, 4.0, 5.0});

	EXPECT_EQ(p + q, expected);
	EXPECT_EQ(expected - q, p);
	EXPECT_NE(expected - q, q); // exercise !=
}


TEST(Quaterniond, Conjugate)
{
	geom::Quaterniond	p(geom::Vector4d {3.0, 4.0, 5.0, 2.0});
	geom::Quaterniond	q(geom::Vector4d {-3.0, -4.0, -5.0, 2.0});

	EXPECT_EQ(p.conjugate(), q);
}


TEST(Quaterniond, Euler)
{
	geom::Quaterniond	p = geom::quaterniond(geom::Vector3d{5.037992718099102, 6.212303632611285, 1.7056797335843106}, M_PI/4.0);
	geom::Quaterniond	q = geom::quaterniond_from_euler(p.euler());

	EXPECT_EQ(p, q);
}


TEST(Quaterniond, Identity)
{
	geom::Quaterniond	p(geom::Vector4d {1.0, -2.0, 1.0, 3.0});
	geom::Quaterniond	q;

	EXPECT_EQ(p * q, p);
}


TEST(Quaterniond, Inverse)
{
	geom::Quaterniond	p(geom::Vector4d {3.0, 4.0, 5.0, 2.0});
	geom::Quaterniond	q(geom::Vector4d {-0.05556, -0.07407, -0.09259, 0.03704 });

	EXPECT_EQ(p.inverse(), q);
}


TEST(Quaterniond, Norm)
{
	geom::Quaterniond	p(geom::Vector4d {0.9899139811480784, 9.387110042325054, 6.161341707794767,
						  5.563199889674063});
	double 			norm = 12.57016663729933;

	EXPECT_DOUBLE_EQ(p.norm(), norm);
}


TEST(Quaterniond, Product)
{
	geom::Quaterniond	p(geom::Vector4d {1.0, -2.0, 1.0, 3.0});
	geom::Quaterniond	q(geom::Vector4d {-1.0, 2.0, 3.0, 2.0});
	geom::Quaterniond	expected(geom::Vector4d{-9.0, -2.0, 11.0, 8.0});

	EXPECT_EQ(p * q, expected);
}


TEST(Quaterniond, Rotate)
{
	// This test aims to rotate a vector v using a quaternion.
	// c.f. https://math.stackexchange.com/questions/40164/how-do-you-rotate-a-vector-by-a-unit-quaternion
	// If we assume a standard IMU frame of reference following the
	// right hand rule:
	// + The x axis points toward magnetic north
	// + The y axis points toward magnentic west
	// + The z axis points toward the sky
	// Given a vector pointing due north, rotating by 90º about
	// the y-axis should leave us pointing toward the sky.

	geom::Vector3d		v {1.0, 0.0, 0.0};     // a vector pointed north
	geom::Vector3d		yAxis {0.0, 1.0, 0.0}; // a vector representing the y axis.
	double			angle = M_PI / 2;      // 90º rotation

	// A quaternion representing a 90º rotation about the y axis.
	geom::Quaterniond	p = geom::quaterniond(yAxis, angle); 
	geom::Vector3d		vr {0.0, 0.0, 1.0};    // expected rotated vector.

	// A rotation quaternion should be a unit quaternion.
	EXPECT_TRUE(p.isUnitQuaternion());
	EXPECT_EQ(p.rotate(v), vr);
}


TEST(Quaterniond, ShortestSLERP)
{
	geom::Quaterniond	p = geom::Quaterniond {0.382683, 0, 0, 0.92388};
	geom::Quaterniond	q = geom::Quaterniond {-0.382683, 0, 0, 0.92388};
	geom::Quaterniond	r = geom::Quaterniond {0, 0, 0, 1};


	EXPECT_EQ(geom::ShortestSLERP(p, q, 0.0), p);
	EXPECT_EQ(geom::ShortestSLERP(p, q, 1.0), q);
	EXPECT_EQ(geom::ShortestSLERP(p, q, 0.5), r);
}


TEST(Quaterniond, Unit)
{
	geom::Quaterniond	q(geom::Vector4d{0.5773502691896258, 0.5773502691896258, 0.5773502691896258, 0.0});

	EXPECT_TRUE(q.isUnitQuaternion());
}


TEST(Quaterniond, UtilityCreator)
{
	geom::Vector3d		v {1.0, 1.0, 1.0};
	double			w = M_PI;
	geom::Quaterniond	p = geom::quaterniond(v, w);
	geom::Quaterniond	q(geom::Vector4d{0.5773502691896258, 0.5773502691896258, 0.5773502691896258, 0.0});

	EXPECT_EQ(p, q);
}


TEST(Quaternionf, Addition)
{
	geom::Quaternionf	p(geom::Vector4f {1.0, -2.0, 1.0, 3.0});
	geom::Quaternionf	q(geom::Vector4f {-1.0, 2.0, 3.0, 2.0});
	geom::Quaternionf	expected(geom::Vector4f{0.0, 0.0, 4.0, 5.0});

	EXPECT_EQ(p + q, expected);
	EXPECT_EQ(expected - q, p);
	EXPECT_NE(expected - q, q); // exercise !=
}


TEST(Quaternionf, Conjugate)
{
	geom::Quaternionf	p(geom::Vector4f {3.0, 4.0, 5.0, 2.0});
	geom::Quaternionf	q(geom::Vector4f {-3.0, -4.0, -5.0, 2.0});

	EXPECT_EQ(p.conjugate(), q);
}


TEST(Quaternionf, Euler)
{
	geom::Quaternionf	p = geom::quaternionf(geom::Vector3f{5.037992718099102, 6.212303632611285, 1.7056797335843106}, M_PI/4.0);
	geom::Quaternionf	q = geom::quaternionf_from_euler(p.euler());

	EXPECT_EQ(p, q);
}


TEST(Quaternionf, Identity)
{
	geom::Quaternionf	p(geom::Vector4f {1.0, -2.0, 1.0, 3.0});
	geom::Quaternionf	q;

	EXPECT_EQ(p * q, p);
}


TEST(Quaternionf, Inverse)
{
	geom::Quaternionf	p(geom::Vector4f {3.0, 4.0, 5.0, 2.0});
	geom::Quaternionf	q(geom::Vector4f {-0.05556, -0.07407, -0.09259, 0.03704 });

	EXPECT_EQ(p.inverse(), q);
}


TEST(Quaternionf, Norm)
{
	geom::Quaternionf	p(geom::Vector4f {0.9899139811480784,
						  9.387110042325054,
						  6.161341707794767,
						  5.563199889674063});
	float 			norm = 12.57016663729933;

	EXPECT_FLOAT_EQ(p.norm(), norm);
}


TEST(Quaternionf, Product)
{
	geom::Quaternionf	p(geom::Vector4f {1.0, -2.0, 1.0, 3.0});
	geom::Quaternionf	q(geom::Vector4f {-1.0, 2.0, 3.0, 2.0});
	geom::Quaternionf	expected(geom::Vector4f{-9.0, -2.0, 11.0, 8.0});

	EXPECT_EQ(p * q, expected);
}


TEST(Quaternionf, Rotate)
{
	geom::Vector3f		v {1.0, 0.0, 0.0};
	geom::Vector3f		yAxis {0.0, 1.0, 0.0};
	float			angle = M_PI / 2;

	geom::Quaternionf	p = geom::quaternionf(yAxis, angle); 
	geom::Vector3f		vr {0.0, 0.0, 1.0};

	EXPECT_TRUE(p.isUnitQuaternion());
	EXPECT_EQ(p.rotate(v), vr);
}


TEST(Quaternionf, Unit)
{
	geom::Quaternionf	q(geom::Vector4f{0.5773502691896258, 0.5773502691896258, 0.5773502691896258, 0.0});

	EXPECT_TRUE(q.isUnitQuaternion());
}


TEST(Quaternionf, UtilityCreator)
{
	geom::Vector3f		v {1.0, 1.0, 1.0};
	float			w = M_PI;
	geom::Quaternionf	p = geom::quaternionf(v, w);
	geom::Quaternionf	q(geom::Vector4f{0.5773502691896258, 0.5773502691896258, 0.5773502691896258, 0.0});

	EXPECT_EQ(p, q);
}


TEST(QuaternionMiscellaneous, SanityChecks)
{
	geom::Vector4d		q {1.0, 2.0, 3.0, 4.0};
	geom::Vector3d		v {1.0, 2.0, 3.0};
	double 			w = 4.0;
	geom::Quaterniond	p(q);

	EXPECT_EQ(p.axis(), v);
	EXPECT_DOUBLE_EQ(p.angle(), w);
}


TEST(QuaternionMiscellaneous, OutputStream)
{
	geom::Quaternionf	p(geom::Vector4f {1.0, 2.0, 3.0, 4.0});
	geom::Quaterniond	q(geom::Vector4d {1.0, 2.0, 3.0, 4.0});
	stringstream		ss;

	ss << p;
	EXPECT_EQ(ss.str(), "4 + <1, 2, 3>");
	ss.str("");

	ss << q;
	EXPECT_EQ(ss.str(), "4 + <1, 2, 3>");
}


TEST(QuaternionMiscellanous, InitializerConstructor)
{
	geom::Quaternionf	p {1.0, 1.0, 1.0, 1.0};
	geom::Quaternionf	q(geom::Vector4f {1.0, 1.0, 1.0, 1.0});

	EXPECT_EQ(p, q);
	EXPECT_FLOAT_EQ(p.norm(), 2.0);
}


int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
