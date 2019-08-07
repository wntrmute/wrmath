.. _vector-docs:
.. highlight:: c++

Vectors
=======

Examples taken from the unit tests::

  TEST(Vector3FloatTests, Projections)
  {
          geom::Vector3f  a {4.866769214609107, 6.2356222686140566, 9.140878417029711};
          geom::Vector3f  b {6.135533104801077, 8.757851406697895, 0.6738031370548048};
          geom::Vector3f  c {4.843812341655318, 6.9140509888133055, 0.5319465962229454};
          geom::Vector3f  d {0.02295687295378901, -0.6784287201992489, 8.608931820806765};
  
          ASSERT_EQ(a.projectParallel(b), c);
          ASSERT_EQ(a.projectOrthogonal(b), d);
  }
  
  
  TEST(Vector3FloatTests, CrossProduct)
  {
          geom::Vector3f  a {8.462, 7.893, -8.187};
          geom::Vector3f  b {6.984, -5.975, 4.778};
          geom::Vector3f  c {-11.2046, -97.6094, -105.685};
  
          c.setEpsilon(0.001);
          EXPECT_EQ(c, a.cross(b));
  }


.. doxygenclass:: wr::geom::Vector
   :members:
