.. _wrmath_api:

Quick Overview
==============

Namespaces
----------

All WNTRMUTE code is in the ``wr`` namespace. The ``geom`` class is
used for code concerning itself with realspace, e.g. :ref:`Quaternions
<quaternion-docs>`.

Coordinate systems
------------------

The library uses a left-hand coordinate system where +x is north, +y is
east, and +z is up. Accordingly, where Euler angles are concerned, the
ZYX (yaw / pitch / roll) axes are used. The code follows the convention
of using ψ, θ, ϕ to represent yaw, pitch, and roll.

Important classes
-----------------

The foundational class of this library (and here's to a real mathematical
workhorse) is the :class:`wr::geom::Vector` class.

Other important classes are the :class:`wr::geom::Quaternion` class.
