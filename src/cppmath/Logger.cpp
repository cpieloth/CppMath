#include <iostream>

#include "Logger.hpp"

using namespace cppmath;

// TODO(cpieloth): Fixed length for log level prefix.
// TODO(cpieloth): std::endl

std::ostream& log::fatal( const std::string src )
{
    return std::cerr << std::endl << "FATAL\t[" << src << "] ";
}

std::ostream& log::error( const std::string src )
{
    return std::cerr << std::endl << "ERROR\t[" << src << "] ";
}

std::ostream& log::warn( const std::string src )
{
    return std::clog << std::endl << "WARN\t[" << src << "] ";
}

std::ostream& log::info( const std::string src )
{
    return std::clog << std::endl << "INFO\t[" << src << "] ";
}

std::ostream& log::debug( const std::string src )
{
    return std::clog << std::endl << "DEBUG\t[" << src << "] ";
}

std::ostream& log::trace( const std::string src )
{
    return std::clog << std::endl << "TRACE\t[" << src << "] ";
}
