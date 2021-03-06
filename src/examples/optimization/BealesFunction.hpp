#ifndef BEALESFUNCTION_HPP_
#define BEALESFUNCTION_HPP_

#include <cppmath/optimization/DownhillSimplexMethodNM.hpp>

/**
 * Beale's function, f(3, 0.5) = 0
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
class BealesFunction: public cppmath::DownhillSimplexMethodNM< 2 >
{
public:
    BealesFunction();
    virtual ~BealesFunction();

    virtual double func( const ParamsT& x ) const;
};

#endif  // BEALESFUNCTION_HPP_
