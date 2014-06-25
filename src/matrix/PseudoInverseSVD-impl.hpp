#ifndef PSEUDOINVERSESVD_IMPL_HPP_
#define PSEUDOINVERSESVD_IMPL_HPP_

#include <Eigen/Core>

#include "PseudoInverseSVD.hpp"

template< typename T >
PseudoInverseSVD< T >::PseudoInverseSVD( const T& matrix, float threshold ) :
                Eigen::JacobiSVD< T >( matrix, Eigen::ComputeThinU | Eigen::ComputeThinV ), m_threshold( threshold )
{
    m_hasInverse = false;
}

template< typename T >
PseudoInverseSVD< T >::~PseudoInverseSVD< T >()
{
}

template< typename T >
const T& PseudoInverseSVD< T >::compute()
{
    if( !m_hasInverse )
    {
        compute( &m_inverse );
        m_hasInverse = true;
    }
    return m_inverse;
}

template< typename T >
void PseudoInverseSVD< T >::compute( T* const pinvmat ) const
{
    if( m_hasInverse )
    {
        *pinvmat = m_inverse;
    }
    else
    {

        eigen_assert( Eigen::JacobiSVD< T >::m_isInitialized && "SVD is not initialized." );
        typename Eigen::JacobiSVD< T >::SingularValuesType singularValues_inv = Eigen::JacobiSVD< T >::m_singularValues;
        for( long i = 0; i < Eigen::JacobiSVD< T >::m_workMatrix.cols(); ++i )
        {
            if( Eigen::JacobiSVD< T >::m_singularValues( i ) > m_threshold )
                singularValues_inv( i ) = 1.0 / Eigen::JacobiSVD< T >::m_singularValues( i );
            else
                singularValues_inv( i ) = 0;
        }
        *pinvmat = ( Eigen::JacobiSVD< T >::m_matrixV * singularValues_inv.asDiagonal()
                        * Eigen::JacobiSVD< T >::m_matrixU.transpose() );
    }
}

template< typename T >
T PseudoInverseSVD< T >::operator*( const T& m )
{
    if( !m_hasInverse )
    {
        compute( &m_inverse );
        m_hasInverse = true;
    }
    return m_inverse * m;
}

template< typename T >
T PseudoInverseSVD< T >::operator*( const T& m ) const
{
    if( m_hasInverse )
    {
        m_inverse * m;
    }
    else
    {
        T inv;
        compute( &inv );
        return inv * m;
    }
}

#endif  // PSEUDOINVERSESVD_IMPL_HPP_
