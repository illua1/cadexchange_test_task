
#pragma once

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
inline constexpr float pi = M_PI;
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

inline Float3 operator *(const Float3 &a, const Float3 &b)
{
  Float3 result;
  X(result) = X(a) * X(b);
  Y(result) = Y(a) * Y(b);
  Z(result) = Z(a) * Z(b);
  return result;
}