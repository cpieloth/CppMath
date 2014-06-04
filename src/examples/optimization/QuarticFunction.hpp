#ifndef QUARTICFUNCTION_HPP_
#define QUARTICFUNCTION_HPP_

#include "../../optimization/DownhillSimplexMethod.hpp"

/**
 * TODO(pieloth): documentation
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
class QuarticFunction: public DownhillSimplexMethod< 4 >
{
public:
    QuarticFunction();
    virtual ~QuarticFunction();

    virtual double func( const PointT& x ) const;
};

#endif  // QUARTICFUNCTION_HPP_
