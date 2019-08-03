#include <iostream>
#include <gtest/gtest.h>
#include <wrnav/geom/vector.h>

using namespace std;
using namespace wr;


TEST(Vector3FloatTests, Magnitude)
{
	geom::Vector3f	v3f {1.0, -2.0, 3.0};
	const float	expected = 3.74165738677394;

	EXPECT_FLOAT_EQ(v3f.magnitude(), expected);
}


TEST(Vector3FloatTests, Equality)
{
	geom::Vector3f	a {1.0, 2.0, 3.0};
	geom::Vector3f	b {1.0, 2.0, 3.0};
	geom::Vector3f	c {1.0, 2.0, 1.0};

	EXPECT_EQ(a, b);
	EXPECT_EQ(b, a);
	EXPECT_NE(a, c);
	EXPECT_NE(b, c);
}


TEST(Vector3FloatTests, Addition)
{
	geom::Vector3f	a {1.0, 2.0, 3.0};
	geom::Vector3f	b {4.0, 5.0, 6.0};
	geom::Vector3f	expected {5.0, 7.0, 9.0};

	EXPECT_EQ(a+b, expected);
}


TEST(Vector3FloatTests, Subtraction)
{
	geom::Vector3f	a {1.0, 2.0, 3.0};
	geom::Vector3f	b {4.0, 5.0, 6.0};
	geom::Vector3f	c {5.0, 7.0, 9.0};

	EXPECT_EQ(c-b, a);
}


TEST(Vector3FloatTests, ScalarMultiplication)
{
	geom::Vector3f	a {1.0, 2.0, 3.0};
	geom::Vector3f	expected {3.0, 6.0, 9.0};

	EXPECT_EQ(a * 3.0, expected);
}


TEST(Vector3FloatTests, ScalarDivision)
{
	geom::Vector3f	a {1.0, 2.0, 3.0};
	geom::Vector3f	b {3.0, 6.0, 9.0};

	EXPECT_EQ(b / 3.0, a);
}


TEST(Vector3FloatTests, DotProduct)
{
	geom::Vector3f	a {1.0, 2.0, 3.0};
	geom::Vector3f	b {4.0, 5.0, 6.0};

	EXPECT_FLOAT_EQ(a * b, 32.0);	
}


TEST(Vector3FloatTests, UnitVector)
{
	// Test values randomly generated and calculated with numpy.
	geom::Vector3f	vec3 {5.320264018493507, 5.6541812891273935, 1.9233435162644652};
	geom::Vector3f	unit {0.6651669556972103, 0.7069150218815566, 0.24046636539587804};

	EXPECT_EQ(vec3.unitVector(), unit);
}


TEST(Vector3FloatTests, Angle)
{
	geom::Vector3f	a {0.3977933061361172, 8.053980094436525, 8.1287759943773};
	geom::Vector3f	b {9.817895298608196, 4.034166890407462, 4.37628316513266};
	geom::Vector3f	c {7.35, 0.221, 5.188};
	geom::Vector3f	d {2.751, 8.259, 3.985};
	
	EXPECT_FLOAT_EQ(a.angle(b), 0.9914540426033251);
	EXPECT_NEAR(c.angle(d), 1.052, 0.001);
}


TEST(Vector3DoubleTests, Magnitude)
{
	geom::Vector3d	v3d{1.0, -2.0, 3.0};
	const double	expected = 3.74165738677394;

	EXPECT_DOUBLE_EQ(v3d.magnitude(), expected);
}


TEST(Vector3DoubleTests, Equality)
{
	geom::Vector3d	a {1.0, 2.0, 3.0};
	geom::Vector3d	b {1.0, 2.0, 3.0};
	geom::Vector3d	c {1.0, 2.0, 1.0};

	EXPECT_EQ(a, b);
	EXPECT_EQ(b, a);
	EXPECT_NE(a, c);
	EXPECT_NE(b, c);
}


TEST(Vector3DoubleTests, Addition)
{
	geom::Vector3d	a {1.0, 2.0, 3.0};
	geom::Vector3d	b {4.0, 5.0, 6.0};
	geom::Vector3d	expected {5.0, 7.0, 9.0};

	EXPECT_EQ(a+b, expected);
}


TEST(Vector3DoubleTests, Subtraction)
{
	geom::Vector3d	a {1.0, 2.0, 3.0};
	geom::Vector3d	b {4.0, 5.0, 6.0};
	geom::Vector3d	c {5.0, 7.0, 9.0};

	EXPECT_EQ(c-b, a);
}


TEST(Vector3DoubleTests, ScalarMultiplication)
{
	geom::Vector3d	a {1.0, 2.0, 3.0};
	geom::Vector3d	expected {3.0, 6.0, 9.0};

	EXPECT_EQ(a * 3.0, expected);
}


TEST(Vector3DoubleTests, ScalarDivision)
{
	geom::Vector3d	a {1.0, 2.0, 3.0};
	geom::Vector3d	b {3.0, 6.0, 9.0};

	EXPECT_EQ(b / 3.0, a);
}


TEST(Vector3DoubleTests, DotProduct)
{
	geom::Vector3d	a {1.0, 2.0, 3.0};
	geom::Vector3d	b {4.0, 5.0, 6.0};

	EXPECT_DOUBLE_EQ(a * b, 32.0);	
}


TEST(Vector3DoubleTests, UnitVector)
{
	// Test values randomly generated and calculated with numpy.
	geom::Vector3d	vec3 {5.320264018493507, 5.6541812891273935, 1.9233435162644652};
	geom::Vector3d	unit {0.6651669556972103, 0.7069150218815566, 0.24046636539587804};

	EXPECT_EQ(vec3.unitVector(), unit);
}


TEST(Vector3DoubleTests, Angle)
{
	geom::Vector3d	a {0.3977933061361172, 8.053980094436525, 8.1287759943773};
	geom::Vector3d	b {9.817895298608196, 4.034166890407462, 4.37628316513266};
	geom::Vector3d	c {7.35, 0.221, 5.188};
	geom::Vector3d	d {2.751, 8.259, 3.985};
	
	EXPECT_DOUBLE_EQ(a.angle(b), 0.9914540426033251);
	EXPECT_NEAR(c.angle(d), 1.052, 0.001);
}


int
main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
