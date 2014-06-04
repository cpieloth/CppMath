#include <cmath> // pow()

#include "ParabolicValley.hpp"

ParabolicValley::ParabolicValley()
{
}

ParabolicValley::~ParabolicValley()
{
}

double ParabolicValley::func( const PointT& x ) const
{
    // Rosenbrock's parabolic valley or Banana Function min 0 at 1,1
//    return 100.0 * pow( ( x.y() - ( x.x() * x.x() ) ), 2 ) + pow( 1.0 - x.x(), 2 );
    return 100.0 * pow( double( ( x( 1 ) - ( x( 0 ) * x( 0 ) ) ) ), 2 ) + pow( double( 1.0 - x( 0 ) ), 2 );
}
