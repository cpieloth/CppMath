#ifndef BEALESFUNCTION_HPP_
#define BEALESFUNCTION_HPP_

#include "../../optimization/DownhillSimplexMethod.hpp"

/**
 * TODO(pieloth): documentation
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
class BealesFunction: public DownhillSimplexMethod< 2 >
{
public:
    BealesFunction();
    virtual ~BealesFunction();

    virtual double func( const PointT& x ) const;
};

#endif  // BEALESFUNCTION_HPP_
