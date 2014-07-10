#include <cmath> // pow()

#include "QuarticFunction.hpp"

QuarticFunction::QuarticFunction()
{
}

QuarticFunction::~QuarticFunction()
{
}

double QuarticFunction::func( const ParamsT& x ) const
{
    const double x1 = x( 0 );
    const double x2 = x( 1 );
    const double x3 = x( 2 );
    const double x4 = x( 3 );
    const double t1 = pow( x1 + 10.0 * x2, 2 );
    const double t2 = 5.0 * pow( x3 - x4, 2 );
    const double t3 = pow( x2 - 2 * x3, 4 );
    const double t4 = 10.0 * pow( x1 - x4, 4 );
    return t1 + t2 + t3 + t4;
}
