#ifndef DOWNHILLSIMPLEXMETHOD_HPP_
#define DOWNHILLSIMPLEXMETHOD_HPP_

#include <cstddef> // size_t
#include <vector>

#include <Eigen/Dense>

namespace cppmath
{
    /**
     * Implementation of the Downhill Simplex or Nelder-Mead method for nonlinear optimization.
     * Nelder, John Ashworth; Mead, Roger: A Simplex Method for Function Minimization. Computer Journal, 1965, 7, 308-313
     *
     * \author cpieloth
     * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
     */
    template< size_t DIM >
    class DownhillSimplexMethod
    {
    public:
        typedef Eigen::Matrix< double, DIM, 1 > ParamsT; /**< Abbreviation for a vector of parameters. */

        /**
         * Enum to indicate how the optimization was converged.
         */
        enum Converged
        {
            CONVERGED_NO, /**< Optimization was not started. */
            CONVERGED_EPSILON, /**< Optimization is smaller than epsilon/threshold. */
            CONVERGED_ITERATIONS, /**< Maximum iterations was reached. */
            CONVERGED_YES /**< Optimization is converged, but not specified how. */
        };

        DownhillSimplexMethod();
        virtual ~DownhillSimplexMethod();

        /**
         * Implementation of the function to minimize.
         *
         * \param x  n-dimensional parameter vector.
         * \return function value for vector x.
         */
        virtual double func( const ParamsT& x ) const = 0;

        /**
         * Indicates how the optimization was converged.
         *
         * \return Enum::Converged
         */
        virtual Converged converged() const;

        double getReflectionCoeff() const;

        void setReflectionCoeff( double alpha );

        double getContractionCoeff() const;

        void setContractionCoeff( double beta );

        double getExpansionCoeff() const;

        void setExpansionCoeff( double gamma );

        size_t getMaximumIterations() const;

        void setMaximumIterations( size_t iterations );

        double getEpsilon() const;

        void setEpsilon( double eps );

        double getInitialFactor() const;

        void setInitialFactor( double factor );

        size_t getIterations() const;

        ParamsT getBestVariable() const;

        /**
         * Starts the optimization.
         *
         * \param initial Initial start point.
         */
        void optimize( const ParamsT& initial );

    protected:
        typedef std::vector< ParamsT > PointVector;
        PointVector m_x; /**< Vector of all n+1 points. */

        double m_epsilon; /**< Threshold or deviation for convergence. */

        size_t m_maxIterations; /**< Maximum iterations until the algorithm is canceled. */
        size_t m_iterations; /**< Iteration counter used for break condition. */

    private:
        enum Step
        {
            STEP_START, STEP_EXIT, STEP_REFLECTION, STEP_EXPANSION, STEP_CONTRACTION
        };

        double m_alpha; /**< Reflection coefficient. */
        double m_beta; /**< Contraction coefficient. */
        double m_gamma; /**< Expansion coefficient. */
        double m_initialFactor; /**< Factor to create the initial point set. */

        void order();
        void centroid();
        Step reflection();
        Step expansion();
        Step contraction();

        ParamsT m_xo;
        ParamsT m_xr;
    };
} /* namespace cppmath */

// Load the implementation
#include "DownhillSimplexMethod-impl.hpp"

#endif  // DOWNHILLSIMPLEXMETHOD_HPP_
