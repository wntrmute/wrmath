.. _quaternion-docs:
.. highlight:: c++

Quaternions
===========

Examples taken from the unit tests::

  TEST(Quaterniond, Rotate)
  {
          // This test aims to rotate a vector v using a quaternion.
          // c.f. https://math.stackexchange.com/questions/40164/
	  //
          // If we assume a standard IMU frame of reference following the
          // right hand rule:
          // + The x axis points toward magnetic north
          // + The y axis points toward magnentic east
          // + The z axis points toward the sky
          // Given a vector pointing due north, rotating by 90º about
          // the y-axis should leave us pointing toward the sky.
  
          geom::Vector3d          v {1.0, 0.0, 0.0};     // a vector pointed north
          geom::Vector3d          yAxis {0.0, 1.0, 0.0}; // a vector representing the y axis.
          double                  angle = M_PI / 2;      // 90º rotation
  
          // A quaternion representing a 90º rotation about the y axis.
          geom::Quaterniond       p = geom::quaterniond(yAxis, angle);
          geom::Vector3d          vr {0.0, 0.0, 1.0};    // expected rotated vector.
  
          // A rotation quaternion should be a unit quaternion.
          EXPECT_TRUE(p.isUnitQuaternion());
          EXPECT_EQ(p.rotate(v), vr);
  }
  
  
  TEST(Quaterniond, ShortestSLERP)
  {
          // Our starting point is an orientation that is yawed 45° - our
          // orientation is pointed π/4 radians in the X axis.
          geom::Quaterniond       p {0.382683, 0, 0, 0.92388};

          // Our ending point is an orientation that is yawed -45° - or
          // pointed -π/4 radians in the X axis.
          geom::Quaterniond       q {-0.382683, 0, 0, 0.92388};

          // The halfway point should be oriented midway about the X axis. It turns
          // out this is an identity quaternion.
          geom::Quaterniond       r;
  
          EXPECT_EQ(geom::ShortestSLERP(p, q, 0.0), p);
          EXPECT_EQ(geom::ShortestSLERP(p, q, 1.0), q);
          EXPECT_EQ(geom::ShortestSLERP(p, q, 0.5), r);
  }
  
  
  TEST(Quaterniond, ShortestSLERP2)
  {
          // Start with an orientation pointing forward, all Euler angles
          // set to 0.
          geom::Quaterniond       start {0.0, 0.0, 0.0, 1.0};
          // The goal is to end up face up, or 90º pitch (still facing forward).
          geom::Quaterniond       end {0, -0.707107, 0, 0.707107};
          // Halfway to the endpoint should be a 45º pitch.
          geom::Quaterniond       halfway {0, -0.382683, 0, 0.92388 };
          // 2/3 of the way should be 60º pitch.
          geom::Quaterniond       twoThirds {0, -0.5, 0, 0.866025};
  
          EXPECT_EQ(ShortestSLERP(start, end, 0.0), start);
          EXPECT_EQ(ShortestSLERP(start, end, 1.0), end);
          EXPECT_EQ(ShortestSLERP(start, end, 0.5), halfway);
          EXPECT_EQ(ShortestSLERP(start, end, 2.0/3.0), twoThirds);
  }


.. doxygenclass:: wr::geom::Quaternion
   :members:

