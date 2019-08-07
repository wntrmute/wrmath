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
	geom::Quaterniond	p(geom::Vector4d {3.0, 1.0, -2.0, 1.0});
	geom::Quaterniond	q(geom::Vector4d {2.0, -1.0, 2.0, 3.0});
	geom::Quaterniond	expected(geom::Vector4d{5.0, 0.0, 0.0, 4.0});

	EXPECT_EQ(p + q, expected);
	EXPECT_EQ(expected - q, p);
	EXPECT_NE(expected - q, q); // exercise !=
}


TEST(Quaterniond, Conjugate)
{
	geom::Quaterniond	p {2.0, 3.0, 4.0, 5.0};
	geom::Quaterniond	q {2.0, -3.0, -4.0, -5.0};

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
	geom::Quaterniond	p {3.0, 1.0, -2.0, 1.0};
	geom::Quaterniond	q;

	EXPECT_TRUE(q.isIdentity());
	EXPECT_EQ(p * q, p);
}


TEST(Quaterniond, Inverse)
{
	geom::Quaterniond	p {2.0, 3.0, 4.0, 5.0};
	geom::Quaterniond	q {0.03704, -0.05556, -0.07407, -0.09259};

	EXPECT_EQ(p.inverse(), q);
}


TEST(Quaterniond, Norm)
{
	geom::Quaterniond	p {5.563199889674063, 0.9899139811480784, 9.387110042325054, 6.161341707794767};
	double 			norm = 12.57016663729933;

	EXPECT_DOUBLE_EQ(p.norm(), norm);
}


TEST(Quaterniond, Product)
{
	geom::Quaterniond	p {3.0, 1.0, -2.0, 1.0};
	geom::Quaterniond	q {2.0, -1.0, 2.0, 3.0};
	geom::Quaterniond	expected {8.0, -9.0, -2.0, 11.0};

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
	// Our starting point is an orientation that is yawed 45° - our
	// orientation is pointed π/4 radians in the X axis.
	geom::Quaterniond	p {0.92388, 0.382683, 0, 0};
	// Our ending point is an orientation that is yawed -45° - or
	// pointed -π/4 radians in the X axis.
	geom::Quaterniond	q {0.92388, -0.382683, 0, 0};
	// The halfway point should be oriented midway about the X axis. It turns
	// out this is an identity quaternion.
	geom::Quaterniond	r;

	EXPECT_EQ(geom::ShortestSLERP(p, q, 0.0), p);
	EXPECT_EQ(geom::ShortestSLERP(p, q, 1.0), q);
	EXPECT_EQ(geom::ShortestSLERP(p, q, 0.5), r);
}


TEST(Quaterniond, ShortestSLERP2)
{
	// Start with an orientation pointing forward, all Euler angles
	// set to 0.
	geom::Quaterniond	start {1.0, 0.0, 0.0, 0.0};
	// The goal is to end up face up, or 90º pitch (still facing forward).
	geom::Quaterniond	end {0.707107, 0, -0.707107, 0};
	// Halfway to the endpoint should be a 45º pitch.
	geom::Quaterniond	halfway {0.92388, 0, -0.382683, 0};
	// 2/3 of the way should be 60º pitch.
	geom::Quaterniond	twoThirds {0.866025, 0, -0.5, 0};

	EXPECT_EQ(ShortestSLERP(start, end, 0.0), start);
	EXPECT_EQ(ShortestSLERP(start, end, 1.0), end);
	EXPECT_EQ(ShortestSLERP(start, end, 0.5), halfway);
	EXPECT_EQ(ShortestSLERP(start, end, 2.0/3.0), twoThirds);
}


TEST(Quaterniond, Unit)
{
	geom::Quaterniond	q {0.0, 0.5773502691896258, 0.5773502691896258, 0.5773502691896258};

	EXPECT_TRUE(q.isUnitQuaternion());
}


TEST(Quaterniond, UtilityCreator)
{
	geom::Vector3d		v {1.0, 1.0, 1.0};
	double			w = M_PI;
	geom::Quaterniond	p = geom::quaterniond(v, w);
	geom::Quaterniond	q {0.0, 0.5773502691896258, 0.5773502691896258, 0.5773502691896258};

	EXPECT_EQ(p, q);
}


TEST(Quaternionf, Addition)
{
	geom::Quaternionf	p {3.0, 1.0, -2.0, 1.0};
	geom::Quaternionf	q {2.0, -1.0, 2.0, 3.0};
	geom::Quaternionf	expected {5.0, 0.0, 0.0, 4.0};

	EXPECT_EQ(p + q, expected);
	EXPECT_EQ(expected - q, p);
	EXPECT_NE(expected - q, q); // exercise !=
}


TEST(Quaternionf, Conjugate)
{
	geom::Quaternionf	p {2.0, 3.0, 4.0, 5.0};
	geom::Quaternionf	q {2.0, -3.0, -4.0, -5.0};

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
	geom::Quaternionf	p {1.0, 3.0, 1.0, -2.0};
	geom::Quaternionf	q;

	EXPECT_EQ(p * q, p);
}


TEST(Quaternionf, Inverse)
{
	geom::Quaternionf	p {2.0, 3.0, 4.0, 5.0};
	geom::Quaternionf	q {0.03704, -0.05556, -0.07407, -0.09259};

	EXPECT_EQ(p.inverse(), q);
}


TEST(Quaternionf, Norm)
{
	geom::Quaternionf	p {0.9899139811480784, 9.387110042325054, 6.161341707794767, 5.563199889674063};
	float 			norm = 12.57016663729933;

	EXPECT_FLOAT_EQ(p.norm(), norm);
}


TEST(Quaternionf, Product)
{
	geom::Quaternionf	p {3.0, 1.0, -2.0, 1.0};
	geom::Quaternionf	q {2.0, -1.0, 2.0, 3.0};
	geom::Quaternionf	expected {8.0, -9.0, -2.0, 11.0};

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


TEST(Quaternionf, ShortestSLERP)
{
	// Our starting point is an orientation that is yawed 45° - our
	// orientation is pointed π/4 radians in the X axis.
	geom::Quaternionf	p {0.92388, 0.382683, 0, 0};
	// Our ending point is an orientation that is yawed -45° - or
	// pointed -π/4 radians in the X axis.
	geom::Quaternionf	q {0.92388, -0.382683, 0, 0};
	// The halfway point should be oriented midway about the X axis. It turns
	// out this is an identity quaternion.
	geom::Quaternionf	r;

	EXPECT_EQ(geom::ShortestSLERP(p, q, (float)0.0), p);
	EXPECT_EQ(geom::ShortestSLERP(p, q, (float)1.0), q);
	EXPECT_EQ(geom::ShortestSLERP(p, q, (float)0.5), r);
}


TEST(Quaternionf, ShortestSLERP2)
{
	// Start with an orientation pointing forward, all Euler angles
	// set to 0.
	geom::Quaternionf	start {1.0, 0.0, 0.0, 0.0};
	// The goal is to end up face up, or 90º pitch (still facing forward).
	geom::Quaternionf	end {0.707107, 0, -0.707107, 0};
	// Halfway to the endpoint should be a 45º pitch.
	geom::Quaternionf	halfway {0.92388, 0, -0.382683, 0};
	// 2/3 of the way should be 60º pitch.
	geom::Quaternionf	twoThirds {0.866025, 0, -0.5, 0};

	EXPECT_EQ(ShortestSLERP(start, end, (float)0.0), start);
	EXPECT_EQ(ShortestSLERP(start, end, (float)1.0), end);
	EXPECT_EQ(ShortestSLERP(start, end, (float)0.5), halfway);
	EXPECT_EQ(ShortestSLERP(start, end, (float)(2.0/3.0)), twoThirds);
}


TEST(Quaternionf, Unit)
{
	geom::Quaternionf	q {0.0, 0.5773502691896258, 0.5773502691896258, 0.5773502691896258};

	EXPECT_TRUE(q.isUnitQuaternion());
}


TEST(Quaternionf, UtilityCreator)
{
	geom::Vector3f		v {1.0, 1.0, 1.0};
	float			w = M_PI;
	geom::Quaternionf	p = geom::quaternionf(v, w);
	geom::Quaternionf	q {0.0, 0.5773502691896258, 0.5773502691896258, 0.5773502691896258};

	EXPECT_EQ(p, q);
}


TEST(QuaternionMiscellaneous, SanityChecks)
{
	geom::Vector4d		q {4.0, 1.0, 2.0, 3.0};
	geom::Vector3d		v {1.0, 2.0, 3.0};
	double 			w = 4.0;
	geom::Quaterniond	p(q);
	geom::Quaterniond	u = p.unitQuaternion();

	EXPECT_EQ(p.axis(), v);
	EXPECT_DOUBLE_EQ(p.angle(), w);
	EXPECT_TRUE(u.isUnitQuaternion());
}


TEST(QuaternionMiscellaneous, OutputStream)
{
	geom::Quaternionf	p {4.0, 1.0, 2.0, 3.0};
	geom::Quaterniond	q {4.0, 1.0, 2.0, 3.0};
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
