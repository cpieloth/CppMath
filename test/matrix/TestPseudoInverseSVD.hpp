#ifndef TESTPSEUDOINVERSESVD_HPP_
#define TESTPSEUDOINVERSESVD_HPP_

#include <cxxtest/TestSuite.h>
#include <Eigen/Dense>

#include <cppmath/matrix/PseudoInverseSVD.hpp>

class TestPseudoInverseSVD: public CxxTest::TestSuite
{
public:
    void test_compute()
    {
        const Eigen::MatrixXd::Index rows = 42;
        const Eigen::MatrixXd::Index cols = 7;

        // Generate system of linear equations
        Eigen::MatrixXd A( rows, cols );
        A.setRandom();
        Eigen::VectorXd x( cols );
        x.setRandom();
        Eigen::VectorXd b = A * x;

        cppmath::PseudoInverseSVD< Eigen::MatrixXd > pinv( A );
        const Eigen::MatrixXd& Ainv = pinv.compute();
        Eigen::VectorXd xs = Ainv * b;
        Eigen::VectorXd diff = x - xs;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_computeArg()
    {
        const Eigen::MatrixXd::Index rows = 23;
        const Eigen::MatrixXd::Index cols = 23;

        // Generate system of linear equations
        Eigen::MatrixXd A( rows, cols );
        A.setRandom();
        Eigen::VectorXd x( cols );
        x.setRandom();
        Eigen::VectorXd b = A * x;

        cppmath::PseudoInverseSVD< Eigen::MatrixXd > pinv( A );
        Eigen::MatrixXd Ainv;
        pinv.compute( &Ainv );
        Eigen::VectorXd xs = Ainv * b;
        Eigen::VectorXd diff = x - xs;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_multiply()
    {
        const Eigen::MatrixXd::Index rows = 3;
        const Eigen::MatrixXd::Index cols = 2;

        // Generate system of linear equations
        Eigen::MatrixXd A( rows, cols );
        A.setRandom();
        Eigen::VectorXd x( cols );
        x.setRandom();
        Eigen::VectorXd b = A * x;

        cppmath::PseudoInverseSVD< Eigen::MatrixXd > pinv( A );
        Eigen::VectorXd xs = pinv * b;
        Eigen::VectorXd diff = x - xs;
        TS_ASSERT_LESS_THAN( diff.squaredNorm(), 1e-6 );
    }

    void test_identity1()
    {
        const Eigen::MatrixXd::Index rows = 7;
        const Eigen::MatrixXd::Index cols = 7;

        // Generate system of linear equations
        Eigen::MatrixXd A( rows, cols );
        A.setRandom();

        cppmath::PseudoInverseSVD< Eigen::MatrixXd > pinv( A );
        Eigen::MatrixXd I = pinv * A;
        TS_ASSERT( I.isIdentity() );
    }

    void test_identity2()
    {
        const Eigen::MatrixXd::Index rows = 7;
        const Eigen::MatrixXd::Index cols = 7;

        // Generate system of linear equations
        Eigen::MatrixXd A( rows, cols );
        A.setIdentity();

        cppmath::PseudoInverseSVD< Eigen::MatrixXd > pinv( A );
        const Eigen::MatrixXd& I = pinv.compute();
        TS_ASSERT( I.isIdentity() );
    }
};

#endif  // TESTPSEUDOINVERSESVD_HPP_
