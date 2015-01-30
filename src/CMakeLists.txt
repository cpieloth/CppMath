# --------------------------------------------------------------------------------------------------------------------------------
#
# General CMake Setup
#
# --------------------------------------------------------------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( CppMath )

IF( NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE Release )
ENDIF( NOT CMAKE_BUILD_TYPE )

SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../tools/cmake" )

FIND_PACKAGE( Eigen3 REQUIRED )

# --------------------------------------
# TODO(cpieloth): target for 'make test'
# --------------------------------------


# --------------------------------------------------------------------------------------------------------------------------------
# Matlab
# --------------------------------------------------------------------------------------------------------------------------------

IF( CMAKE_COMPILER_IS_GNUCXX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
ELSE( CMAKE_COMPILER_IS_GNUCXX )
    MESSAGE( WARNING "You may have to activate c++0x support for your compiler!" )
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

SET( TARGET CppMath1Matlab )

FILE( GLOB CppMathMatlab_SRC
    "${CMAKE_SOURCE_DIR}/cppmath/matlab/*.h"
    "${CMAKE_SOURCE_DIR}/cppmath/matlab/*.cpp"
    "${CMAKE_SOURCE_DIR}/cppmath/Logger.h"
    "${CMAKE_SOURCE_DIR}/cppmath/Logger.cpp"
)

ADD_LIBRARY( ${TARGET} SHARED ${CppMathMatlab_SRC} )
INCLUDE_DIRECTORIES( ${TARGET} ./ )
INCLUDE_DIRECTORIES( ${TARGET} ${EIGEN3_INCLUDE_DIR} )

SET( TARGET ReadMatExample )

FILE( GLOB ReadMatExample_SRC
    "${CMAKE_SOURCE_DIR}/examples/matlab/*.h"
    "${CMAKE_SOURCE_DIR}/examples/matlab/*.cpp"
)

ADD_EXECUTABLE( ${TARGET} ${ReadMatExample_SRC} )
TARGET_LINK_LIBRARIES( ${TARGET} CppMath1Matlab )

INCLUDE_DIRECTORIES( ${TARGET} ./ )
INCLUDE_DIRECTORIES( ${TARGET} ${EIGEN3_INCLUDE_DIR} )


# --------------------------------------------------------------------------------------------------------------------------------
# Examples: matrix
# --------------------------------------------------------------------------------------------------------------------------------

SET( TARGET PseudoInverseSvdExample )

FILE( GLOB PseudoInverseSvdExample_SRC
    "${CMAKE_SOURCE_DIR}/examples/matrix/*.h"
    "${CMAKE_SOURCE_DIR}/examples/matrix/*.cpp"
)

ADD_EXECUTABLE( ${TARGET} ${PseudoInverseSvdExample_SRC} )

INCLUDE_DIRECTORIES( ${TARGET} ./ )
INCLUDE_DIRECTORIES( ${TARGET} ${EIGEN3_INCLUDE_DIR} )


# --------------------------------------------------------------------------------------------------------------------------------
# Examples: optimization
# --------------------------------------------------------------------------------------------------------------------------------

SET( TARGET DownhillSimplexExample )

FILE( GLOB DownhillSimplexExample_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/examples/optimization/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/examples/optimization/*.cpp"
)

ADD_EXECUTABLE( ${TARGET} ${DownhillSimplexExample_SRC} )

INCLUDE_DIRECTORIES( ${TARGET} ./ )
INCLUDE_DIRECTORIES( ${TARGET} ${EIGEN3_INCLUDE_DIR} )
