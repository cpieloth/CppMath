#ifndef DOWNHILLSIMPLEXMETHODWIKI_IMPL_HPP_
#define DOWNHILLSIMPLEXMETHODWIKI_IMPL_HPP_

#include <cassert>
#include <cmath> // pow()

#include "DownhillSimplexMethodWiki.hpp"

namespace cppmath
{
    template< size_t DIM >
    DownhillSimplexMethodWiki< DIM >::DownhillSimplexMethodWiki()
    {
        m_alpha = 1.0;
        m_rho = 0.5;
        m_sigma = -0.5;
        m_gamma = 2.0;
        m_maxIterations = 128;
        m_iterations = 0;
        m_epsilon = 1e-9;
        m_initialFactor = 2.0;
        m_x.resize( DIM + 1 );
    }

    template< size_t DIM >
    DownhillSimplexMethodWiki< DIM >::~DownhillSimplexMethodWiki()
    {
    }

    template< size_t DIM >
    bool DownhillSimplexMethodWiki< DIM >::isConverged() const
    {
        return ( m_iterations >= m_maxIterations ) || ( func( m_x[0] ) <= m_epsilon );
    }

    template< size_t DIM >
    double DownhillSimplexMethodWiki< DIM >::getReflectionCoeff() const
    {
        return m_alpha;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setReflectionCoeff( double alpha )
    {
        assert( 0.0 <= alpha );
        m_alpha = alpha;
    }

    template< size_t DIM >
    double DownhillSimplexMethodWiki< DIM >::getContractionCoeff() const
    {
        return m_rho;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setContractionCoeff( double rho )
    {
        assert( -1.0 <= rho && rho <= 0.0 );
        m_rho = rho;
    }

    template< size_t DIM >
    double DownhillSimplexMethodWiki< DIM >::getReductionCoeff() const
    {
        return m_rho;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setReductionCoeff( double sigma )
    {
        assert( 0.0 <= sigma && sigma <= 1.0 );
        m_sigma = sigma;
    }

    template< size_t DIM >
    double DownhillSimplexMethodWiki< DIM >::getExpansionCoeff() const
    {
        return m_gamma;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setExpansionCoeff( double gamma )
    {
        m_gamma = gamma;
    }

    template< size_t DIM >
    size_t DownhillSimplexMethodWiki< DIM >::getMaximumIterations() const
    {
        return m_maxIterations;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setMaximumIterations( size_t iterations )
    {
        m_maxIterations = iterations;
    }

    template< size_t DIM >
    size_t DownhillSimplexMethodWiki< DIM >::getIterations() const
    {
        return m_iterations;
    }

    template< size_t DIM >
    double DownhillSimplexMethodWiki< DIM >::getEpsilon() const
    {
        return m_epsilon;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setEpsilon( double eps )
    {
        m_epsilon = eps;
    }

    template< size_t DIM >
    double DownhillSimplexMethodWiki< DIM >::getInitialFactor() const
    {
        return m_initialFactor;
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::setInitialFactor( double factor )
    {
        m_initialFactor = factor;
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::PointT DownhillSimplexMethodWiki< DIM >::getBestVariable() const
    {
        return m_x[0];
    }

    template< size_t DIM >
    void DownhillSimplexMethodWiki< DIM >::optimize( const PointT& initial )
    {
        m_x[0] = initial;
        typename PointT::Index dim = 0;
        for( typename PointVector::size_type i = 1; i < m_x.size(); ++i )
        {
            PointT p = initial;
            p( dim ) = p( dim ) * m_initialFactor;
            m_x[i] = p;
            ++dim;
        }

        Step next = STEP_ORDER;
        bool quit = false;
        while( !quit )
        {
            switch( next )
            {
                case STEP_ORDER:
                    ++m_iterations;
                    next = order();
                    if( isConverged() )
                    {
                        quit = true;
                    }
                    break;
                case STEP_CENTROID:
                    next = centroid();
                    break;
                case STEP_REFLECTION:
                    next = reflection();
                    break;
                case STEP_EXPANSION:
                    next = expansion();
                    break;
                case STEP_CONTRACTION:
                    next = contraction();
                    break;
                case STEP_REDUCTION:
                    next = reduction();
                    break;
            }
        }
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::Step DownhillSimplexMethodWiki< DIM >::order()
    {
        // order: f(x1) <= f(x2) <= ... <= f(x_n+1)
        // Insertionsort
        for( typename PointVector::size_type i = 1; i < m_x.size(); ++i )
        {
            const PointT insert = m_x[i];
            const double fInsert = func( insert );
            typename PointVector::size_type j = i;
            while( j > 0 && func( m_x[j - 1] ) > fInsert )
            {
                m_x[j] = m_x[j - 1];
                --j;
            }
            m_x[j] = insert;
        }
        return STEP_CENTROID;
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::Step DownhillSimplexMethodWiki< DIM >::centroid()
    {
        // calc: x_o - the center of all points except x_n+1
        PointT xo = PointT::Zero();
        for( typename PointVector::size_type i = 0; i < DIM; ++i )
        {
            xo += m_x[i];
        }
        m_xo = xo / DIM;
        return STEP_REFLECTION;
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::Step DownhillSimplexMethodWiki< DIM >::reflection()
    {
        // compute reflected point: x_r = x_o + alpha*(x_o - x_n+1)
        m_xr = m_xo + m_alpha * ( m_xo - m_x[DIM] );
        // If the reflected point is better than the second worst, but not better than the best, i.e.: f(x1) <= f(x_r) < f(x_n),
        const double fr = func( m_xr );
        if( func( m_x[0] ) <= fr && fr < func( m_x[DIM - 1] ) )
        {
            // then obtain a new simplex by replacing the worst point x_n+1 with the reflected point x_r, and go to step 1.
            m_x[DIM] = m_xr;
            return STEP_ORDER;
        }
        return STEP_EXPANSION;
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::Step DownhillSimplexMethodWiki< DIM >::expansion()
    {
        // If the reflected point is the best point so far, f(x_r) < f(x_1),
        const double fr = func( m_xr );
        if( fr < func( m_x[0] ) )
        {
            // compute the expanded point: x_e = x_o + gamma*(x_o - x_n+1)
            m_xe = m_xo + m_gamma * ( m_xo - m_x[DIM] );
            // If the expanded point is better than the reflected point, f(x_e) < f(x_r)
            if( func( m_xe ) < fr )
            {
                // then obtain a new simplex by replacing the worst point x_n+1 with the expanded point x_e, and go to step 1.
                m_x[DIM] = m_xe;
                return STEP_ORDER;
            }
            else
            {
                // obtain a new simplex by replacing the worst point x_n+1 with the reflected point x_r, and go to step 1.
                m_x[DIM] = m_xr;
                return STEP_ORDER;
            }
        }
        else
        {
            // reflected point is not better than second worst, continue at step 5
            return STEP_CONTRACTION;
        }
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::Step DownhillSimplexMethodWiki< DIM >::contraction()
    {
        assert( func( m_xr ) >= func( m_x[DIM - 1] ) );
        // compute contracted point: x_c = x_o + rho*(x_o - x_n+1)
        m_xc = m_xo + m_rho * ( m_xo - m_x[DIM] );
        // If the contracted point is better than the worst point, i.e. f(x_c) < f(x_n+1)
        if( func( m_xc ) < func( m_x[DIM] ) )
        {
            // obtain a new simplex by replacing the worst point x_n+1 with the contracted point x_c, and go to step 1.
            m_x[DIM] = m_xc;
            return STEP_ORDER;
        }
        return STEP_REDUCTION;
    }

    template< size_t DIM >
    typename DownhillSimplexMethodWiki< DIM >::Step DownhillSimplexMethodWiki< DIM >::reduction()
    {
        // For all but the best point/ for all i in {2, ...,n+1\}
        for( typename PointVector::size_type i = 1; i < DIM + 1; ++i )
        {
            // replace the point with: x_i = x_1 + sigma*(x_i - x_1)
            m_x[i] = m_x[0] + m_sigma * ( m_x[i] - m_x[0] );
        }
        //  go to step 1.
        return STEP_ORDER;
    }
} /* namespace cppmath */

#endif  // DOWNHILLSIMPLEXMETHODWIKI_IMPL_HPP_
