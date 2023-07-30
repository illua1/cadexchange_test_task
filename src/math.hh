
#pragma once

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
static constexpr float pi = M_PI;
#undef _USE_MATH_DEFINES

#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/vec_mat_operations.hpp>
#include <boost/qvm/vec_operations.hpp>
#include <boost/qvm/vec_access.hpp>

namespace math = boost::qvm;

using Float3 = math::vec<float, 3>;
using Float3x3 = math::mat<float, 3, 3>;

inline std::ostream &operator << (std::ostream &os, const Float3 &point)
{
    os << "(" << X(point) << ", " << Y(point) << ", " << Z(point) << ")";  
    return os;
}
