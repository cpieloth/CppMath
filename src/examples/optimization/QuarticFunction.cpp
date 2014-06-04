#include <cmath> // pow()
#include <iostream>

#include "QuarticFunction.hpp"

QuarticFunction::QuarticFunction()
{
}

QuarticFunction::~QuarticFunction()
{
}

double QuarticFunction::func( const PointT& x ) const
{
    // Powell's quartic function
    const double t1 = pow( double( x( 0 ) + 10.0 * x( 1 ) ), 2.0 );
    const double t2 = 5.0 * pow( double( x( 2 ) - x( 3 ) ), 2 );
    const double t3 = pow( double( x( 1 ) - 2 * x( 2 ) ), 4 );
    const double t4 = 10.0 * pow( double( x( 0 ) - 2 * x( 3 ) ), 4 );
    return t1 + t2 + t3 + t4;
}
