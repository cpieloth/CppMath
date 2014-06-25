#ifndef PSEUDOINVERSESVD_HPP_
#define PSEUDOINVERSESVD_HPP_

#include <Eigen/SVD>

/**
 * Calculates a SVD-based pseudo inverse matrix.
 * See:
 * - http://en.wikipedia.org/wiki/Moore-Penrose_pseudoinverse#The_general_case_and_the_SVD_method
 * - http://eigen.tuxfamily.org/index.php?title=FAQ#Is_there_a_method_to_compute_the_.28Moore-Penrose.29_pseudo_inverse_.3F
 *
 * \author cpieloth
 * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
 */
template< typename T >
class PseudoInverseSVD: private Eigen::JacobiSVD< T >
{
public:
    /**
     * Constructor.
     *
     * \param matrix Matrix to compute the pseudo inverse from.
     * \param pinvThreshold Threshold to keep value as zero/nonzero (default: 1.0e-6).
     */
    PseudoInverseSVD( const T& matrix, float threshold = 1.0e-6 );

    virtual ~PseudoInverseSVD();

    /**
     * Computes the pseudo inverse.
     * The pseudo inverse is internally stored for further calculations.
     *
     * \return Reference to the internally stored pseudo inverse matrix.
     */
    const T& compute();

    /**
     * Computes the pseudo inverse.
     *
     * \param pinvmat Holds the pseudo inverse matrix after computation.
     */
    void compute( T* const pinvmat ) const;

    /**
     * Multiplies the pseudo inverse with a matrix.
     * The pseudo inverse is internally stored for further calculations.
     *
     * \param m Matrix
     * \return Result of pinv*m
     */
    T operator*( const T& m );

    /**
     *  Multiplies the pseudo inverse with a matrix.
     *
     * \param m Matrix
     * \return Result of pinv*m
     */
    T operator*( const T& m ) const;

private:
    bool m_hasInverse; /**< Indicates if the internal inverse matrix is available. */

    T m_inverse; /**< Stores a computed inverse matrix. */

    const float m_threshold;
};

// Load the implementation
#include "PseudoInverseSVD-impl.hpp"

#endif  // PSEUDOINVERSESVD_HPP_
