#include "BealesFunction.hpp"

BealesFunction::BealesFunction()
{
}

BealesFunction::~BealesFunction()
{
}

double BealesFunction::func( const ParamsT& x ) const
{
    const double x1 = x( 0 );
    const double x2 = x( 1 );
    const double t1 = pow( 1.5 - x1 * ( 1 - x2 ), 2 );
    const double t2 = pow( 2.25 - x1 * ( 1 - pow( x2, 2 ) ), 2 );
    const double t3 = pow( 2.625 - x1 * ( 1 - pow( x2, 3 ) ), 2 );
    return t1 + t2 + t3;
}

