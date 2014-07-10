#ifndef PARABOLICVALLEY_HPP_
#define PARABOLICVALLEY_HPP_

#include <cppmath/optimization/DownhillSimplexMethod.hpp>

/**
 * Rosenbrock's valley or Rosenbrock's banana function, f(1, 1) = 0
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
class ParabolicValley: public cppmath::DownhillSimplexMethod< 2 >
{
public:
    ParabolicValley();
    virtual ~ParabolicValley();

    virtual double func( const ParamsT& x ) const;
};

#endif  // PARABOLICVALLEY_HPP_
