#include <cmath> // pow()

#include "ParabolicValley.hpp"

ParabolicValley::ParabolicValley()
{
}

ParabolicValley::~ParabolicValley()
{
}

double ParabolicValley::func( const ParamsT& x ) const
{
    const double x1 = x( 0 );
    const double x2 = x( 1 );
    return 100.0 * pow( ( x2 - pow( x1, 2 ) ), 2 ) + pow( x1 - 1.0, 2 );
}
