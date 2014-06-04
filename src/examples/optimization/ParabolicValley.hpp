#ifndef PARABOLICVALLEY_HPP_
#define PARABOLICVALLEY_HPP_

#include "../../optimization/DownhillSimplexMethod.hpp"

/**
 * TODO(pieloth): documentation
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
class ParabolicValley: public DownhillSimplexMethod< 2 >
{
public:
    ParabolicValley();
    virtual ~ParabolicValley();

    virtual double func( const PointT& x ) const;
};

#endif  // PARABOLICVALLEY_HPP_
