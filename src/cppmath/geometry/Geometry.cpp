#include <cmath>  // sin, cos
#include <limits>  // limits<double>

#include <Eigen/Dense>

#include "Geometry.hpp"

using namespace cppmath;

geometry::Matrix3T geometry::getRotationXYZMatrix( double x, double y, double z )
{
    Matrix3T rot;

    rot( 0, 0 ) = cos( y ) * cos( z );
    rot( 0, 1 ) = -cos( y ) * sin( z );
    rot( 0, 2 ) = sin( y );

    rot( 1, 0 ) = cos( x ) * sin( z ) + cos( z ) * sin( x ) * sin( y );
    rot( 1, 1 ) = cos( x ) * cos( z ) - sin( x ) * sin( y ) * sin( z );
    rot( 1, 2 ) = -cos( y ) * sin( x );

    rot( 2, 0 ) = sin( x ) * sin( z ) - cos( x ) * cos( z ) * sin( y );
    rot( 2, 1 ) = cos( z ) * sin( x ) + cos( x ) * sin( y ) * sin( z );
    rot( 2, 2 ) = cos( x ) * cos( y );

    return rot;
}

bool geometry::findOrthogonalVector( Vector3T* const o, const Vector3T& v )
{
    // 0 = Vx Ox + Vy Oy + Vz Oz
    if( v.isZero( 1e3 * std::numeric_limits< double >::min() ) )
    {
        return false;
    }

    // avoid division by zero, pick max(abs) as divisor
    Vector3T::Index i;
    v.cwiseAbs().maxCoeff( &i );
    if( i == 2 ) // z
    {
        // - Vz Oz = Vx Ox + Vy Oy
        //      Ox = Vy
        //      Oy = Vx
        //      Oz = -2(Vx * Vy) / Vz
        o->x() = v.y();
        o->y() = v.x();

        o->z() = ( -2.0 * v.x() * v.y() ) / v.z();
        return true;
    }
    if( i == 1 ) // y
    {
        // - Vy Oy = Vx Ox + Vz Oz
        //      Ox = Vz
        //      Oz = Vx
        //      Oy = -2(Vx * Vz) / Vy
        o->x() = v.z();
        o->z() = v.x();
        o->y() = ( -2.0 * v.x() * v.z() ) / v.y();
        return true;
    }
    if( i == 0 ) // x
    {
        // - Vx Ox = Vy Oy + Vz Oz
        //      Oy = Vz
        //      Oz = Vy
        //      Ox = -2(Vy * Vz) / Vx
        o->y() = v.z();
        o->z() = v.y();
        o->x() = ( -2.0 * v.y() * v.z() ) / v.x();
        return true;
    }
    return false;
}

bool geometry::findTangentPlane( Vector3T* const u, Vector3T* const v, const Vector3T& n )
{
    if( !findOrthogonalVector( u, n ) )
    {
        return false;
    }
    *v = n.cross( *u );
    return true;
}
