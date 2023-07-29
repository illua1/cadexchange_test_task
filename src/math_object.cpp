
#include "math.hh"
#include "math_object.hh"

Float3 CircleMathObject::compute_imp(const float factor) const
{
  const Float3 start_point{0.0f, radius, 0.0f};
  const Float3x3 rot = boost::qvm::rot_mat_xyz<3, float>(0.0f, 0.0f, factor * 3.14);
  return rot * start_point;
}

Abstract3dMathObject CircleMathObject::derivative_imp() const
{
  return {};
}

Abstract3dMathObject CircleMathObject::copy_imp() const
{
  return CircleMathObject::make(radius);
}