#include <iostream>

#include <Eigen/Dense>

#include "../../matrix/PseudoInverseSVD.hpp"

using namespace Eigen;
using namespace std;

int main()
{
    const MatrixXd::Index rows = 42;
    const MatrixXd::Index cols = 7;

    // Generate system of linear equations
    MatrixXd A( rows, cols );
    A.setRandom();
    VectorXd x( cols );
    x.setRandom();
    VectorXd b( 102 );
    b = A * x;
    cout << "x:" << endl << x << endl;
    VectorXd diff;

    // Method call #1
    PseudoInverseSVD< MatrixXd > pinv( A );
    MatrixXd Ainv;
    pinv.compute( &Ainv );
    VectorXd xs1 = Ainv * b;
    diff = x - xs1;
    cout << "xs1:" << endl << xs1 << endl;
    cout << "x - xs1: " << diff.squaredNorm() << endl;

    // Methof call #2
    const MatrixXd& Apinv = pinv.compute();
    VectorXd xs2 = Apinv * b;
    diff = x - xs2;
    cout << "xs2:" << endl << xs2 << endl;
    cout << "x - xs2: " << diff.squaredNorm() << endl;

    // Operator call
    VectorXd xs3 = pinv * b;
    diff = x - xs3;
    cout << "xs3:" << endl << xs3 << endl;
    cout << "x - xs3: " << diff.squaredNorm() << endl;

    return 0;
}
