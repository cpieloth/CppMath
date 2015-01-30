#include "io.hpp"

using namespace cppmath;

bool matlab::ArrayFlags::isComplex( const mArrayFlags_t& data )
{
    return data & ArrayFlags::MASK_COMPLEX;
}

bool matlab::ArrayFlags::isGlobal( const mArrayFlags_t& data )
{
    return data & ArrayFlags::MASK_GLOBAL;
}

bool matlab::ArrayFlags::isLogical( const mArrayFlags_t& data )
{
    return data & ArrayFlags::MASK_LOGICAL;
}

matlab::mArrayType_t matlab::ArrayFlags::getArrayType( const mArrayFlags_t& data )
{
    const mArrayFlags_t tmp = data & ArrayFlags::MASK_GET_CLASS;
    return tmp & ArrayFlags::MASK_GET_CLASS;
}

bool matlab::ArrayTypes::isNumericArray( const mArrayType_t& type )
{
    if( type == ArrayTypes::mxDOUBLE_CLASS || type == ArrayTypes::mxSINGLE_CLASS )
    {
        return true;
    }
    if( type == ArrayTypes::mxINT8_CLASS || type == ArrayTypes::mxUINT8_CLASS )
    {
        return true;
    }
    if( type == ArrayTypes::mxINT16_CLASS || type == ArrayTypes::mxUINT16_CLASS )
    {
        return true;
    }
    if( type == ArrayTypes::mxINT32_CLASS || type == ArrayTypes::mxUINT32_CLASS )
    {
        return true;
    }
    return false;
}
