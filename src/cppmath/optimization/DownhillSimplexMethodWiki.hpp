#ifndef DOWNHILLSIMPLEXMETHODWIKI_HPP_
#define DOWNHILLSIMPLEXMETHODWIKI_HPP_

#include <cstddef> // size_t
#include <vector>

#include <Eigen/Dense>

namespace cppmath
{
    /**
     * Implementation of the Downhill Simplex or Nelder-Mead method for nonlinear optimization.
     * A variation from Wikipedia: http://en.wikipedia.org/w/index.php?title=Nelder%E2%80%93Mead_method&oldid=606313559
     *
     * \author cpieloth
     * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
     */
    template< size_t DIM >
    class DownhillSimplexMethodWiki
    {
    public:
        DownhillSimplexMethodWiki();
        virtual ~DownhillSimplexMethodWiki();

        typedef Eigen::Matrix< double, 1, DIM > PointT;

        virtual bool isConverged() const;

        double getReflectionCoeff() const;

        void setReflectionCoeff( double alpha );

        double getContractionCoeff() const;

        void setContractionCoeff( double rho );

        double getReductionCoeff() const;

        void setReductionCoeff( double sigma );

        double getExpansionCoeff() const;

        void setExpansionCoeff( double gamma );

        size_t getMaximumIterations() const;

        void setMaximumIterations( size_t iterations );

        double getEpsilon() const;

        void setEpsilon( double eps );

        double getInitialFactor() const;

        void setInitialFactor( double factor );

        size_t getIterations() const;

        PointT getBestVariable() const;

        void optimize( const PointT& initial );

        virtual double func( const PointT& x ) const = 0;

    protected:
        typedef std::vector< PointT > PointVector;
        PointVector m_x;

        double m_epsilon;

        size_t m_maxIterations;
        size_t m_iterations;

    private:
        enum Step
        {
            STEP_ORDER, STEP_CENTROID, STEP_REFLECTION, STEP_EXPANSION, STEP_CONTRACTION, STEP_REDUCTION
        };

        double m_alpha; /**< Reflection coefficient */
        double m_rho; /**< Contraction coefficient */
        double m_sigma; /**< Reduction coefficient */
        double m_gamma; /**< Expansion coefficient */
        double m_initialFactor;

        Step order();
        Step centroid();
        Step reflection();
        Step expansion();
        Step contraction();
        Step reduction();

        PointT m_xo;
        PointT m_xr;
        PointT m_xe;
        PointT m_xc;
    };
} /* namespace cppmath */

#include "DownhillSimplexMethodWiki-impl.hpp"

#endif  // DOWNHILLSIMPLEXMETHODWIKI_HPP_
