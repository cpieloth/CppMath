#include "BealesFunction.hpp"

BealesFunction::BealesFunction()
{
}

BealesFunction::~BealesFunction()
{
}

double BealesFunction::func( const PointT& x ) const
{
    // BealesFunction min 0 at 3,0.5
    const double t1 = pow( double( 1.5 - x( 0 ) * ( 1 - x( 1 ) ) ), 2 );
    const double t2 = pow( double( 2.25 - x( 0 ) * ( 1 - x( 1 ) * x( 1 ) ) ), 2 );
    const double t3 = pow( double( 2.625 - x( 0 ) * ( 1 - x( 1 ) * x( 1 ) * x( 1 ) ) ), 2 );
    return t1 + t2 + t3;
}

