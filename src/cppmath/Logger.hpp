#ifndef CPPMATH_UTIL_LOGGER_HPP_
#define CPPMATH_UTIL_LOGGER_HPP_

#include <ostream>
#include <string>

namespace cppmath
{
    /**
     * Simple logging methods (in progress).
     * \author cpieloth
     * \copyright Copyright 2015 Christof Pieloth, Licensed under the Apache License, Version 2.0
     */
    namespace log
    {
        std::ostream& fatal( const std::string src );
        std::ostream& error( const std::string src );
        std::ostream& warn( const std::string src );
        std::ostream& info( const std::string src );
        std::ostream& debug( const std::string src );
        std::ostream& trace( const std::string src );
    } /* namespace log */
} /* namespace cppmath */

#endif  // CPPMATH_UTIL_LOGGER_HPP_
