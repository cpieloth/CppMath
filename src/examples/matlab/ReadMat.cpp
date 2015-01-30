#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include <Eigen/Core>

#include <cppmath/matlab/io.hpp>

using namespace std;
using namespace Eigen;
using namespace cppmath;

int main()
{
    const string FNAME = "cppmath.mat";
    cout << "Read MAT-file: " << FNAME << endl;

    // Open file
    // ---------
    ifstream ifs;
    ifs.open( FNAME.c_str(), ifstream::in | ifstream::binary );
    if( !ifs || ifs.bad() )
    {
        cout << "Could not open file!" << endl;
        return EXIT_FAILURE;
    }

    // Read file info
    // --------------
    matlab::FileInfo fileInfo;
    if( !matlab::MatReader::readHeader( &fileInfo, ifs ) )
    {
        cout << "Could read header!" << endl;
        return EXIT_FAILURE;
    }
    if( !fileInfo.isMatFile )
    {
        cout << "No MAT-file!" << endl;
        return EXIT_FAILURE;
    }
    cout << endl; // FIXME(cpieloth): Missing endl in logger methods.
    cout << "Description: " << fileInfo.description << endl;

    // Retrieve elements
    // -----------------
    list< matlab::ElementInfo > elements;
    if( !matlab::MatReader::retrieveDataElements( &elements, ifs, fileInfo ) )
    {
        cout << "Error while retrieving data elements!" << endl;
        return EXIT_FAILURE;
    }
    cout << endl; // FIXME(cpieloth): Missing endl in logger methods.
    cout << "Element count: " << elements.size() << endl;

    // Read elements
    // -------------
    cout << "Elements:" << endl;
    for( list< matlab::ElementInfo >::const_iterator it = elements.begin(); it != elements.end(); ++it )
    {
        cout << "Element name: " << it->arrayName << endl;
        if( it->dataType != matlab::DataTypes::miMATRIX )
        {
            cout << "No matrix, skipping element!" << endl;
            continue;
        }

        const bool isComplex = matlab::ArrayFlags::isComplex( it->arrayFlags );
        const bool isDouble = matlab::ArrayFlags::getArrayType( it->arrayFlags ) == matlab::ArrayTypes::mxDOUBLE_CLASS;
        if( !isDouble || isComplex )
        {
            cout << endl; // FIXME(cpieloth): Missing endl in logger methods.
            cout << "Data type not supported, skipping element!" << endl;
            continue;
        }

        Eigen::MatrixXd matrixDbl;
        if( !matlab::MatReader::readMatrixDouble( &matrixDbl, *it, ifs, fileInfo ) )
        {
            cout << endl; // FIXME(cpieloth): Missing endl in logger methods.
            cout << "Error on reading matrix, skipping element!" << endl;
            continue;
        }
        cout << "Matrix:\n" << matrixDbl << endl;
    }

    return EXIT_SUCCESS;
}
