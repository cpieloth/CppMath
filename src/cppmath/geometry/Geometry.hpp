#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include <cmath>  // fabs()
#include <limits>  // limits<double>

#include <Eigen/Core>

namespace cppmath
{
    /**
     * Helper functions for geometric computations.
     *
     * \author cpieloth
     * \copyright Copyright 2014 Christof Pieloth, Licensed under the Apache License, Version 2.0
     */
    namespace geometry
    {
        typedef Eigen::Vector3d Vector3T;
        typedef Eigen::Matrix3Xd PointsT;
        typedef Eigen::Matrix3d Matrix3T;

        Matrix3T getRotationXYZMatrix( double x, double y, double z );

        /**
         * Calculates an orthogonal vector to v.
         *
         * \param o An orthogonal vector of v.
         * \param v Input vector.
         * \return True if o contains an orthogonal vector of v.
         */
        bool findOrthogonalVector( Vector3T* const o, const Vector3T& v );

        /**
         * Calculates an tangent plane for the normal vector n. u, v and n are orthogonal to each other.
         *
         * \param u Plane vector 1 for parametrically description.
         * \param v Plane vector 2 for parametrically description.
         * \param n Normal vector.
         * \return True if u and v contain a plane vector.
         */
        bool findTangentPlane( Vector3T* const u, Vector3T* const v, const Vector3T& n );
    }
}

#endif  // GEOMETRY_HPP_
