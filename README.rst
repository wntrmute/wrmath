wrmath
======

The WNTRMUTE ROBOTICS maths library is a C++11 library containing various
useful maths components for robotics and navigation.

Dependencies
------------

This project uses Google Test as a dependency::

  $ git submodule update --init --recursive

Additionally, building this requires

+ a C++11 compiler
+ CMake (minimum 3.15 to support code coverage, otherwise 3.10).
+ Doxygen


Building
--------

.. code::

    mkdir build
    cmake ..
    make check
