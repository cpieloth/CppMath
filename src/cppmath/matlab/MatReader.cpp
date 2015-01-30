#include <list>
#include <string>

#include "../Logger.hpp"
#include "io.hpp"

using std::ifstream;
using namespace cppmath;

const std::string matlab::MatReader::CLASS = "MatReader";

bool matlab::MatReader::readHeader( FileInfo* const infoIn, std::ifstream& ifs )
{
    if( infoIn == NULL )
    {
        log::error( CLASS ) << "FileInfo is null!";
        ifs.seekg( 0, ifs.beg );
        return false;
    }

    infoIn->fileSize = 0;
    infoIn->isMatFile = false;

    if( !ifs || ifs.bad() )
    {
        log::error( CLASS ) << "Problem with input stream!";
        ifs.seekg( 0, ifs.beg );
        return false;
    }

    // Check minimum file size
    ifs.seekg( 0, ifs.end );
    const ifstream::pos_type file_size = ifs.tellg();
    infoIn->fileSize = file_size;
    log::debug( CLASS ) << "File size: " << infoIn->fileSize;
    if( file_size < 127 )
    {
        log::error( CLASS ) << "File size is to small for a MAT file!";
        ifs.seekg( 0, ifs.beg );
        return false;
    }
    ifs.seekg( 0, ifs.beg );

    // Read description text
    char description[117];
    ifs.read( description, 116 );
    description[116] = '\0';
    infoIn->description.assign( description );
    log::debug( CLASS ) << description;

    // Read version
    ifs.seekg( 8, ifstream::cur );
    char version[2] = { 0 };
    ifs.read( version, 2 );
    if( version[0] != 0x00 || version[1] != 0x01 )
    {
        log::error( CLASS ) << "Wrong version!";
        ifs.seekg( 0, ifs.beg );
        return false;
    }
    infoIn->isMatFile = true;

    // Read endian indicator
    char endian[2] = { 0 };
    ifs.read( endian, 2 );
    if( endian[0] == 'I' && endian[1] == 'M' )
    {
        infoIn->isLittleEndian = true;
    }
    else
        if( endian[0] == 'M' && endian[1] == 'I' )
        {
            infoIn->isLittleEndian = false;
            log::error( CLASS ) << "Big endian is not yet supported!";
            return false;
        }
        else
        {
            log::error( CLASS ) << "Unknown endian indicator!";
            return false;
        }

    ifs.seekg( 128 );

    return true;
}

bool matlab::MatReader::retrieveDataElements( std::list< ElementInfo >* const elements, std::ifstream& ifs,
                const FileInfo& info )
{
    if( elements == NULL )
    {
        log::error( CLASS ) << "List for ElementInfo is null!";
        return false;
    }
    ifs.seekg( 128 );

    // Temporary data to write to
    matlab::mDataType_t type;
    matlab::mNumBytes_t bytes;
    std::streampos pos;
    const std::streamoff min_tag_size = 4;
    while( ifs.good() && static_cast< size_t >( ifs.tellg() + min_tag_size ) < info.fileSize )
    {
        type = 0;
        bytes = 0;
        pos = ifs.tellg();
        if( !readTagField( &type, &bytes, ifs ) )
        {
            log::error( CLASS ) << "Unknown data type or wrong data structure. Cancel retrieving!";
            ifs.seekg( 128 );
            return false;
        }

        ElementInfo element;
        element.dataType = type;
        element.numBytes = bytes;
        element.pos = pos;
        log::debug( CLASS ) << "Data Type: " << element.dataType;
        log::debug( CLASS ) << "Number of Bytes: " << element.numBytes;

        if( element.dataType == matlab::DataTypes::miMATRIX )
        {
            if( !readArraySubelements( &element, ifs ) )
            {
                nextElement( ifs, element.pos, element.numBytes );
                continue;
            }
        }

        nextElement( ifs, element.pos, element.numBytes );
        elements->push_back( element );
    }

    ifs.clear();
    ifs.seekg( 128 );
    return true;
}

bool matlab::MatReader::readTagField( mDataType_t* const dataType, mNumBytes_t* const numBytes, std::ifstream& ifs )
{
    const std::streampos pos = ifs.tellg();
    ifs.read( ( char* )dataType, sizeof(matlab::mDataType_t) );
    ifs.read( ( char* )numBytes, sizeof(matlab::mNumBytes_t) );
    if( *dataType > matlab::DataTypes::miUTF32 )
    {
        log::debug( CLASS ) << "Small Data Element Format found.";
        matlab::mDataTypeSmall_t typeSmall;
        matlab::mNumBytesSmall_t bytesSmall;
        ifs.seekg( -( sizeof(matlab::mDataType_t) + sizeof(matlab::mNumBytes_t) ), ifstream::cur );
        ifs.read( ( char* )&typeSmall, sizeof(matlab::mDataTypeSmall_t) );
        ifs.read( ( char* )&bytesSmall, sizeof(matlab::mNumBytesSmall_t) );
        *dataType = typeSmall;
        *numBytes = bytesSmall;
    }
    if( *dataType > matlab::DataTypes::miUTF32 )
    {
        log::error( CLASS ) << "Unknown data type or wrong data structure!";
        ifs.seekg( pos );
        return false;
    }
    return true;
}

bool matlab::MatReader::readArraySubelements( ElementInfo* const element, std::ifstream& ifs )
{
    if( element == NULL )
    {
        log::error( CLASS ) << "ElementInfo_t is null!";
        return false;
    }

    ifs.seekg( element->pos );
    ifs.seekg( 8, ifstream::cur );
    if( !ifs.good() )
    {
        log::error( CLASS ) << "Could not jump to element: " << element->pos;
        ifs.seekg( element->pos );
        return false;
    }

    matlab::mDataType_t type;
    matlab::mNumBytes_t bytes;
    std::streampos tagStart;
    // Read Array Flags //
    // ---------------- //
    if( !readTagField( &type, &bytes, ifs ) )
    {
        log::error( CLASS ) << "Could not read Array Flags!";
        return false;
    }
    else
        if( bytes != 8 || type != DataTypes::miUINT32 )
        {
            log::error( CLASS ) << "Bytes for Array Flags or Data Type is wrong: " << bytes << " (expected: 8) or "
                            << type << " (expected: " << DataTypes::miUINT32 << ")";
            ifs.seekg( element->pos );
            return false;
        }

    // Read flags and class
    mArrayFlags_t arrayFlags[2];
    ifs.read( ( char* )&arrayFlags, 8 );
    const mArrayFlags_t arrayFlag = arrayFlags[0];
    log::debug( CLASS ) << "Array Flag: " << arrayFlag;
    if( ArrayFlags::isComplex( arrayFlag ) )
    {
        log::debug( CLASS ) << "Is complex.";
    }
    if( ArrayFlags::isGlobal( arrayFlag ) )
    {
        log::debug( CLASS ) << "Is global.";
    }
    if( ArrayFlags::isLogical( arrayFlag ) )
    {
        log::debug( CLASS ) << "Is logical.";
    }

    element->arrayFlags = arrayFlag;
    const mArrayType_t clazz = ArrayFlags::getArrayType( arrayFlag );
    log::debug( CLASS ) << "Array Type/Class: " << ( miUINT32_t )ArrayFlags::getArrayType( arrayFlag );
    if( !ArrayTypes::isNumericArray( clazz ) && clazz != ArrayTypes::mxCHAR_CLASS )
    {
        element->posData = ifs.tellg();
        ifs.seekg( element->pos );
        return true;
    }

    log::debug( CLASS ) << "Data element is numeric array. Retrieving more subelements.";

    // Read Dimension //
    // -------------- //
    tagStart = ifs.tellg();
    if( !readTagField( &type, &bytes, ifs ) )
    {
        log::error( CLASS ) << "Could not read Dimension!";
        return false;
    }
    else
        if( bytes < 8 || type != DataTypes::miINT32 )
        {
            log::error( CLASS ) << "Bytes for Dimension or Data Type is wrong: " << bytes << " (expected: 8) or "
                            << type << " (expected: " << DataTypes::miINT32 << ")";
            ifs.seekg( element->pos );
            return false;
        }

    // TODO(cpieloth): Check for dimensions n > 2
    if( bytes != 8 )
    {
        log::error( CLASS ) << "Dimension n != 2 is not yet supported!";
        return false;
    }
    ifs.read( ( char* )&element->rows, sizeof(miINT32_t) );
    ifs.read( ( char* )&element->cols, sizeof(miINT32_t) );

    if( element->rows < 1 || element->cols < 1 )
    {
        log::error( CLASS ) << "Rows/Cols error: " << element->rows << "x" << element->cols;
        ifs.seekg( element->pos );
        return false;
    }
    log::debug( CLASS ) << "Array size: " << element->rows << "x" << element->cols;
    nextElement( ifs, tagStart, bytes );

    // Read Array Name //
    // --------------- //
    tagStart = ifs.tellg();
    if( !readTagField( &type, &bytes, ifs ) )
    {
        log::error( CLASS ) << "Could not read Array Name!";
        return false;
    }
    else
        if( type != DataTypes::miINT8 )
        {
            log::error( CLASS ) << "Data Type is wrong: " << type << " (expected: " << DataTypes::miINT8 << ")";
            ifs.seekg( element->pos );
            return false;
        }

    char* tmp = ( char* )malloc( bytes + 1 );
    ifs.read( tmp, bytes );
    tmp[bytes] = '\0';
    element->arrayName.assign( tmp );
    free( tmp );
    log::debug( CLASS ) << "Array Name: " << element->arrayName;
    if( bytes > 4 ) // Fix names with more than 4 characters, thx Patrick.
    {
        tagStart += bytes;
    }
    nextElement( ifs, tagStart, bytes );

    // Set Data Position
    element->posData = ifs.tellg();
    return true;
}

bool matlab::MatReader::readMatrixDouble( Eigen::MatrixXd* const matrix, const ElementInfo& element, std::ifstream& ifs,
                const FileInfo& info )
{
    // Check some errors //
    // ----------------- //
    if( matrix == NULL )
    {
        log::error( CLASS ) << "Matrix object is null!";
        return false;
    }

    if( info.fileSize <= static_cast< size_t >( element.posData ) )
    {
        log::error( CLASS ) << "Data position is beyond file end!";
        return false;
    }

    if( element.dataType != DataTypes::miMATRIX )
    {
        log::error( CLASS ) << "Data type is not a matrix: " << element.dataType;
        return false;
    }

    const mArrayType_t arrayType = ArrayFlags::getArrayType( element.arrayFlags );
    if( arrayType != ArrayTypes::mxDOUBLE_CLASS )
    {
        log::error( CLASS ) << "Numeric Types does not match!";
        return false;
    }

    const std::streampos pos = ifs.tellg();

    // Read data //
    // --------- //
    ifs.seekg( element.posData );
    mDataType_t type;
    mNumBytes_t bytes;
    if( !readTagField( &type, &bytes, ifs ) )
    {
        log::error( CLASS ) << "Could not read Data Element!";
        ifs.seekg( pos );
        return false;
    }
    if( type != DataTypes::miDOUBLE )
    {
        log::error( CLASS ) << "Numeric Types does not match or compressed data, which is not supported: " << type;
        ifs.seekg( pos );
        return false;
    }

    matrix->resize( element.rows, element.cols );
    ifs.read( ( char* )matrix->data(), bytes );

    nextElement( ifs, element.posData, bytes );
    return true;
}

bool matlab::MatReader::readMatrixComplex( Eigen::MatrixXcd* const matrix, const ElementInfo& element,
                std::ifstream& ifs, const FileInfo& info )
{
    // Check some errors //
    // ----------------- //
    if( matrix == NULL )
    {
        log::error( CLASS ) << "Matrix object is null!";
        return false;
    }

    if( info.fileSize <= static_cast< size_t >( element.posData ) )
    {
        log::error( CLASS ) << "Data position is beyond file end!";
        return false;
    }

    if( element.dataType != DataTypes::miMATRIX )
    {
        log::error( CLASS ) << "Data type is not a matrix: " << element.dataType;
        return false;
    }

    const bool isDouble = ArrayFlags::getArrayType( element.arrayFlags ) == ArrayTypes::mxDOUBLE_CLASS;
    const bool isComplex = ArrayFlags::isComplex( element.arrayFlags );
    if( !isDouble || !isComplex )
    {
        log::error( CLASS ) << "Numeric Types does not match!";
        return false;
    }

    const std::streampos pos = ifs.tellg();

    // Read data //
    // --------- //
    ifs.seekg( element.posData );
    mDataType_t type;
    mNumBytes_t bytes;
    if( !readTagField( &type, &bytes, ifs ) )
    {
        log::error( CLASS ) << "Could not read real data tag!";
        ifs.seekg( pos );
        return false;
    }
    if( type != DataTypes::miDOUBLE )
    {
        log::error( CLASS ) << "Numeric Type does not match or compressed data, which is not supported: " << type;
        ifs.seekg( pos );
        return false;
    }

    Eigen::MatrixXd real( element.rows, element.cols );
    ifs.read( ( char* )real.data(), bytes );

    if( !readTagField( &type, &bytes, ifs ) )
    {
        log::error( CLASS ) << "Could not read imag data tag!";
        ifs.seekg( pos );
        return false;
    }
    if( type != DataTypes::miDOUBLE )
    {
        log::error( CLASS ) << "Numeric Type does not match or compressed data, which is not supported: " << type;
        ifs.seekg( pos );
        return false;
    }

    Eigen::MatrixXd imag( element.rows, element.cols );
    ifs.read( ( char* )imag.data(), bytes );

    matrix->resize( element.rows, element.cols );
    matrix->real() = real;
    matrix->imag() = imag;

    nextElement( ifs, element.posData, bytes );
    return true;
}

void matlab::MatReader::nextElement( std::ifstream& ifs, const std::streampos& tagStart, size_t numBytes )
{
    ifs.seekg( tagStart );
    if( numBytes > 4 ) // short data element
    {
        ifs.seekg( 8, ifstream::cur );
        if( numBytes % 8 )
        {
            numBytes = 8 - ( numBytes % 8 );
        }
        ifs.seekg( numBytes, ifstream::cur );
    }
    else
    {
        ifs.seekg( 8, ifstream::cur );
    }
}
