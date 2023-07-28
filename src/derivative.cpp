
#include <limits>

#include "derivative.hh"

template<typename Value>
class BaseDerivative : public AbstractMathObjectBase<Value> {
  using BaseType = std::shared_ptr<AbstractMathObjectBase<Value>>;
  const BaseType base;
  public: BaseDerivative(const BaseType obj_base) : AbstractMathObjectBase<Value>("Base Derivative"), base(obj_base) {}

  public: static std::shared_ptr<AbstractMathObjectBase<Value>> make(const BaseType obj_base)
  {
    return std::make_shared<BaseDerivative<Value>>(obj_base);
  }

  Value compute_imp(const float factor) const
  {
    const float zero_offset = std::numeric_limits<float>::min();
    const Value a_value = base->compute(factor - zero_offset);
    const Value b_value = base->compute(factor + zero_offset);
    const Value tangent = normalize(a_value - b_value);
    return tangent;
  }

  std::shared_ptr<AbstractMathObjectBase<Value>> derivative_imp() const
  {
    return std::make_shared<BaseDerivative>(*this);
  }

  std::shared_ptr<AbstractMathObjectBase<Value>> copy_imp() const
  {
    return std::make_shared<BaseDerivative>(base);
  }
};

template<typename Value>
Value AbstractMathObjectBase<Value>::compute(const float factor) const
{
  return this->compute_imp(factor);
}

template<typename Value>
std::shared_ptr<AbstractMathObjectBase<Value>> AbstractMathObjectBase<Value>::derivative() const
{
  return this->derivative_imp();
}

template<typename Value>
std::shared_ptr<AbstractMathObjectBase<Value>> AbstractMathObjectBase<Value>::copy() const
{
  return this->copy_imp();
}

template<typename Value>
std::shared_ptr<AbstractMathObjectBase<Value>> AbstractMathObjectBase<Value>::derivative_imp() const
{
  return BaseDerivative<Value>::make(this->copy());
}

Float3 CircleMathObject::compute_imp(const float factor) const
{
  Float3 start_point{0.0f, radius, 0.0f};
  
  return {};
}

Abstract3dMathObject CircleMathObject::derivative_imp() const
{
  return {};
}

Abstract3dMathObject CircleMathObject::copy_imp() const
{
  return {};
}