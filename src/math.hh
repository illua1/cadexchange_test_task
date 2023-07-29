
#pragma once

#include <iostream>

#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_mat_operations.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/vec_access.hpp>

using Float3 = boost::qvm::vec<float, 3>;
using Float3x3 = boost::qvm::mat<float, 3, 3>;

inline std::ostream &operator << (std::ostream &os, const Float3 &point)
{
    os << "(" << X(point) << ", " << Y(point) << ", " << Z(point) << ")";  
    return os;
}