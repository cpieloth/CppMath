#ifndef QUARTICFUNCTION_HPP_
#define QUARTICFUNCTION_HPP_

#include <cppmath/optimization/DownhillSimplexMethodNM.hpp>

/**
 * Powell's quartic function, f(0, 0, 0, 0) = 0
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
class QuarticFunction: public cppmath::DownhillSimplexMethodNM< 4 >
{
public:
    QuarticFunction();
    virtual ~QuarticFunction();

    virtual double func( const ParamsT& x ) const;
};

#endif  // QUARTICFUNCTION_HPP_
