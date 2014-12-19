#ifndef TESTGEOMETRY_HPP_
#define TESTGEOMETRY_HPP_

#include <limits> // limits<double>

#include <cxxtest/TestSuite.h>

#include <cppmath/geometry/Geometry.hpp>

/**
 * \author cpieloth
 */
class TestGeometry: public CxxTest::TestSuite
{
public:
    void test_findOrthogonalVector()
    {
        const double eps = 1e-12;
        cppmath::geometry::Vector3T v;
        cppmath::geometry::Vector3T o;

        v = cppmath::geometry::Vector3T::Zero();
        TS_ASSERT( cppmath::geometry::findOrthogonalVector( &o, v ) == false );

        v = cppmath::geometry::Vector3T::Random();
        TS_ASSERT( cppmath::geometry::findOrthogonalVector( &o, v ) );
        TS_ASSERT_DELTA( v.dot( o ), 0.0, eps );

        v.setZero();
        v.x() = 8;
        TS_ASSERT( cppmath::geometry::findOrthogonalVector( &o, v ) );
        TS_ASSERT_DELTA( v.dot( o ), 0.0, eps );

        v.setZero();
        v.y() = 23;
        TS_ASSERT( cppmath::geometry::findOrthogonalVector( &o, v ) );
        TS_ASSERT_DELTA( v.dot( o ), 0.0, eps );

        v.setZero();
        v.z() = 42;
        TS_ASSERT( cppmath::geometry::findOrthogonalVector( &o, v ) );
        TS_ASSERT_DELTA( v.dot( o ), 0.0, eps );
    }

    void test_findTagentPlane()
    {
        const double eps = 1e-12;
        cppmath::geometry::Vector3T n;
        cppmath::geometry::Vector3T u;
        cppmath::geometry::Vector3T v;

        n = cppmath::geometry::Vector3T::Zero();
        TS_ASSERT( cppmath::geometry::findTagentPlane( &u, &v, n ) == false );

        n = cppmath::geometry::Vector3T::Random();
        TS_ASSERT( cppmath::geometry::findTagentPlane( &u, &v, n ) );
        TS_ASSERT_DELTA( n.dot( u ), 0.0, eps );
        TS_ASSERT_DELTA( n.dot( v ), 0.0, eps );
        TS_ASSERT_DELTA( u.dot( v ), 0.0, eps );

        n.setZero();
        n.x() = 42;
        TS_ASSERT( cppmath::geometry::findTagentPlane( &u, &v, n ) );
        TS_ASSERT_DELTA( n.dot( u ), 0.0, eps );
        TS_ASSERT_DELTA( n.dot( v ), 0.0, eps );
        TS_ASSERT_DELTA( u.dot( v ), 0.0, eps );

        n.setZero();
        n.y() = 23;
        TS_ASSERT( cppmath::geometry::findTagentPlane( &u, &v, n ) );
        TS_ASSERT_DELTA( n.dot( u ), 0.0, eps );
        TS_ASSERT_DELTA( n.dot( v ), 0.0, eps );
        TS_ASSERT_DELTA( u.dot( v ), 0.0, eps );

        n.setZero();
        n.z() = 8;
        TS_ASSERT( cppmath::geometry::findTagentPlane( &u, &v, n ) );
        TS_ASSERT_DELTA( n.dot( u ), 0.0, eps );
        TS_ASSERT_DELTA( n.dot( v ), 0.0, eps );
        TS_ASSERT_DELTA( u.dot( v ), 0.0, eps );
    }
};

#endif  // TESTGEOMETRY_HPP_
