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
