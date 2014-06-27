#ifndef TESTDOWNHILLSIMPLEXMETHOD_HPP_
#define TESTDOWNHILLSIMPLEXMETHOD_HPP_

#include <cxxtest/TestSuite.h>

#include "optimization/DownhillSimplexMethod.hpp"

/**
 * Beale's function, f(3, 0.5) = 0
 */
class BealesFunction: public DownhillSimplexMethod< 2 >
{
public:
    BealesFunction()
    {
    }

    virtual ~BealesFunction()
    {
    }

    virtual double func( const PointT& x ) const;
};

inline
double BealesFunction::func( const PointT& x ) const
{
    const double x1 = x( 0 );
    const double x2 = x( 1 );
    const double t1 = pow( 1.5 - x1 * ( 1 - x2 ), 2 );
    const double t2 = pow( 2.25 - x1 * ( 1 - pow( x2, 2 ) ), 2 );
    const double t3 = pow( 2.625 - x1 * ( 1 - pow( x2, 3 ) ), 2 );
    return t1 + t2 + t3;
}

/**
 * Rosenbrock's valley or Rosenbrock's banana function, f(1, 1) = 0
 */
class ParabolicValley: public DownhillSimplexMethod< 2 >
{
public:
    ParabolicValley()
    {

    }
    virtual ~ParabolicValley()
    {
    }

    virtual double func( const PointT& x ) const;
};

inline
double ParabolicValley::func( const PointT& x ) const
{
    const double x1 = x( 0 );
    const double x2 = x( 1 );
    return 100.0 * pow( ( x2 - pow( x1, 2 ) ), 2 ) + pow( x1 - 1.0, 2 );
}

/**
 * Powell's quartic function, f(0, 0, 0, 0 ) = 0
 */
class QuarticFunction: public DownhillSimplexMethod< 4 >
{
public:
    QuarticFunction()
    {
    }
    virtual ~QuarticFunction()
    {
    }

    virtual double func( const PointT& x ) const;
};

inline
double QuarticFunction::func( const PointT& x ) const
{
    const double x1 = x( 0 );
    const double x2 = x( 1 );
    const double x3 = x( 2 );
    const double x4 = x( 3 );
    const double t1 = pow( x1 + 10.0 * x2, 2 );
    const double t2 = 5.0 * pow( x3 - x4, 2 );
    const double t3 = pow( x2 - 2 * x3, 4 );
    const double t4 = 10.0 * pow( x1 - x4, 4 );
    return t1 + t2 + t3 + t4;
}

/**
 * Tests Downhill-Simplex-Method with some predefined functions.
 */
class TestDownhillSimplexMethod: public CxxTest::TestSuite
{
public:
    void test_optimizeBeale0()
    {
        const BealesFunction::PointT exp( 3.0, 0.5 );

        BealesFunction opt;
        const BealesFunction::PointT initial = exp;
        opt.optimize( initial );

        const BealesFunction::PointT res = opt.getBestVariable();
        const BealesFunction::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeBeale1()
    {
        const BealesFunction::PointT exp( 3.0, 0.5 );

        BealesFunction opt;
        const BealesFunction::PointT initial = exp * -1.0;
        opt.optimize( initial );

        const BealesFunction::PointT res = opt.getBestVariable();
        const BealesFunction::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeBeale2()
    {
        const BealesFunction::PointT exp( 3.0, 0.5 );

        BealesFunction opt;
        const BealesFunction::PointT initial( 5.0, 5.0 );
        opt.optimize( initial );

        const BealesFunction::PointT res = opt.getBestVariable();
        const BealesFunction::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeBeale3()
    {
        const float eps = 1e-4;
        const size_t max_it = 1024;

        BealesFunction opt;
        const BealesFunction::PointT initial( 5.0, 5.0 );
        opt.setMaximumIterations( max_it );
        opt.setEpsilon( eps );
        opt.optimize( initial );

        const BealesFunction::PointT res = opt.getBestVariable();
        const double fx = opt.func( res );
        TS_ASSERT_LESS_THAN( fx, eps );
        TS_ASSERT_LESS_THAN( opt.getIterations(), max_it );
    }

    void test_optimizeParabolic0()
    {
        const ParabolicValley::PointT exp( 1.0, 1.0 );

        ParabolicValley opt;
        const ParabolicValley::PointT initial = exp;
        opt.optimize( initial );

        const ParabolicValley::PointT res = opt.getBestVariable();
        const ParabolicValley::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeParabolic1()
    {
        const ParabolicValley::PointT exp( 1.0, 1.0 );

        ParabolicValley opt;
        const ParabolicValley::PointT initial = exp * -1.0;
        opt.optimize( initial );

        const ParabolicValley::PointT res = opt.getBestVariable();
        const ParabolicValley::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeParabolic2()
    {
        const ParabolicValley::PointT exp( 1.0, 1.0 );

        ParabolicValley opt;
        const ParabolicValley::PointT initial( 5.0, 5.0 );
        opt.setMaximumIterations( 500 );
        opt.optimize( initial );

        const ParabolicValley::PointT res = opt.getBestVariable();
        const ParabolicValley::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeParabolic3()
    {
        const float eps = 1e-4;
        const size_t max_it = 1024;

        ParabolicValley opt;
        const ParabolicValley::PointT initial( 5.0, 5.0 );
        opt.setMaximumIterations( max_it );
        opt.setEpsilon( eps );
        opt.optimize( initial );

        const ParabolicValley::PointT res = opt.getBestVariable();
        const double fx = opt.func( res );
        TS_ASSERT_LESS_THAN( fx, eps );
        TS_ASSERT_LESS_THAN( opt.getIterations(), max_it );
    }

    void test_optimizeQuartic0()
    {
        const QuarticFunction::PointT exp( 0.0, 0.0, 0.0, 0.0 );

        QuarticFunction opt;
        const QuarticFunction::PointT initial = exp;
        opt.optimize( initial );

        const QuarticFunction::PointT res = opt.getBestVariable();
        const QuarticFunction::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeQuartic1()
    {
        const QuarticFunction::PointT exp( 0.0, 0.0, 0.0, 0.0 );

        QuarticFunction opt;
        const QuarticFunction::PointT initial( 5.0, 5.0, 5.0, 5.0 );
        opt.setMaximumIterations(500);
        opt.optimize( initial );

        const QuarticFunction::PointT res = opt.getBestVariable();
        const QuarticFunction::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeQuartic2()
    {
        const QuarticFunction::PointT exp( 0.0, 0.0, 0.0, 0.0 );

        QuarticFunction opt;
        const QuarticFunction::PointT initial( 3.0, -1.0, 0.0, 1.0 );
        opt.setMaximumIterations( 500 );
        opt.optimize( initial );

        const QuarticFunction::PointT res = opt.getBestVariable();
        const QuarticFunction::PointT diff = res - exp;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_optimizeQuartic3()
    {
        const float eps = 1e-4;
        const size_t max_it = 1024;

        QuarticFunction opt;
        const QuarticFunction::PointT initial( -5.0, -5.0, -5.0, -5.0 );
        opt.setMaximumIterations( max_it );
        opt.setEpsilon( eps );
        opt.optimize( initial );

        const QuarticFunction::PointT res = opt.getBestVariable();
        const double fx = opt.func( res );
        TS_ASSERT_LESS_THAN( fx, eps );
        TS_ASSERT_LESS_THAN( opt.getIterations(), max_it );
    }

};

#endif  // TESTDOWNHILLSIMPLEXMETHOD_HPP_
