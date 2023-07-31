
#include "math.hh"
#include "math_object.hh"

Float3 CircleMathObject::compute_imp(const float factor) const
{
  const Float3 start_point{0.0f, radius, 0.0f};
  const Float3x3 rot = math::rot_mat_xyz<3, float>(0.0f, 0.0f, factor * pi * 2.0f);
  return rot * start_point;
}

MathObject3dPtr CircleMathObject::derivative_imp() const
{
  return CircleDerivativeMathObject::make(radius);
}

MathObject3dPtr CircleMathObject::copy_imp() const
{
  return CircleMathObject::make(radius);
}



Float3 CircleDerivativeMathObject::compute_imp(const float factor) const
{
  const Float3 start_point{0.0f, 1.0f, 0.0f};
  const Float3x3 rot = math::rot_mat_xyz<3, float>(0.0f, 0.0f, (factor - 0.25f) * pi * 2.0f);
  return rot * start_point;
}

MathObject3dPtr CircleDerivativeMathObject::derivative_imp() const
{
  return BaseDerivative::make(copy());
}

MathObject3dPtr CircleDerivativeMathObject::copy_imp() const
{
  return CircleDerivativeMathObject::make(radius);
}



Float3 ElipseMathObject::compute_imp(const float factor) const
{
  const Float3 start_point{0.0f, 1.0f, 0.0f};
  const Float3x3 rot = math::rot_mat_xyz<3, float>(0.0f, 0.0f, factor * 3.14);
  const Float3 normalized_point = rot * start_point;
  const Float3 elipse_box{x, y, 0.0f};
  return normalized_point * elipse_box;
}

MathObject3dPtr ElipseMathObject::derivative_imp() const
{
  return ElipseDerivativeMathObject::make(x, y);
}

MathObject3dPtr ElipseMathObject::copy_imp() const
{
  return ElipseMathObject::make(x, y);
}



static Float3 tangent_to_vector_for_xoz(const Float3 &vector)
{
  static const Float3 vertival_vector{0.0f, 0.0f, 1.0f};
  return math::cross(vector, vertival_vector);
}

Float3 ElipseDerivativeMathObject::compute_imp(const float factor) const
{
  const Float3 start_point{0.0f, 1.0f, 0.0f};
  const Float3x3 rot = math::rot_mat_xyz<3, float>(0.0f, 0.0f, factor * 3.14);
  const Float3 normalized_point = rot * start_point;
  const Float3 elipse_box{x, y, 0.0f};
  return tangent_to_vector_for_xoz(normalized(normalized_point * elipse_box));
}

MathObject3dPtr ElipseDerivativeMathObject::derivative_imp() const
{
  return BaseDerivative::make(copy());
}

MathObject3dPtr ElipseDerivativeMathObject::copy_imp() const
{
  return ElipseDerivativeMathObject::make(x, y);
}



Float3 HelixMathObject::compute_imp(const float factor) const
{
  //const Float3 start_point{0.0f, radius, 0.0f};
  //const Float3x3 rot = math::rot_mat_xyz<3, float>(0.0f, 0.0f, factor * 3.14);
  return {};//rot * start_point;
}

MathObject3dPtr HelixMathObject::derivative_imp() const
{
  return HelixDerivativeMathObject::make(radius, step_height, steps_amount);
}

MathObject3dPtr HelixMathObject::copy_imp() const
{
  return HelixMathObject::make(radius, step_height, steps_amount);
}



Float3 HelixDerivativeMathObject::compute_imp(const float factor) const
{
  //const Float3 start_point{0.0f, radius + 3.14f / 2.0f, 0.0f};
  //const Float3x3 rot = math::rot_mat_xyz<3, float>(0.0f, 0.0f, factor * 3.14);
  return {};//rot * start_point;
}

MathObject3dPtr HelixDerivativeMathObject::derivative_imp() const
{
  return BaseDerivative::make(copy());
}

MathObject3dPtr HelixDerivativeMathObject::copy_imp() const
{
  return HelixDerivativeMathObject::make(radius, step_height, steps_amount);
}