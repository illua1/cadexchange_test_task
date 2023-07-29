
#pragma once

#include <memory>
#include <iostream>

#include "math.hh"

template<typename Value>
class AbstractMathObjectBase {
  protected: const char *name;

  public: AbstractMathObjectBase(const char *obj_name) : name(obj_name) {}
  public: virtual ~AbstractMathObjectBase() = 0;

  public: Value compute(const float factor) const;
  public: virtual Value compute_imp(const float factor) const = 0;

  public: std::shared_ptr<AbstractMathObjectBase> derivative() const;
  public: virtual std::shared_ptr<AbstractMathObjectBase> derivative_imp() const;

  public: std::shared_ptr<AbstractMathObjectBase> copy() const;
  public: virtual std::shared_ptr<AbstractMathObjectBase> copy_imp() const = 0;
};

using Abstract3dMathObject = std::shared_ptr<AbstractMathObjectBase<Float3>>;

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
    const float zero_offset = 0.001f;
    const Value a_value = base->compute(factor - zero_offset);
    const Value b_value = base->compute(factor + zero_offset);
    const Value tangent = normalized(a_value - b_value);
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

class CircleMathObject : public AbstractMathObjectBase<Float3> {
  private: const float radius;

  public: CircleMathObject(const float circle_radius) : AbstractMathObjectBase<Float3>("Circle"), radius(circle_radius) {}
  public: ~CircleMathObject() = default;

  public: static Abstract3dMathObject make(const float circle_radius)
  {
    return std::make_shared<CircleMathObject>(circle_radius);
  }

  private: Float3 compute_imp(const float factor) const override;
  private: Abstract3dMathObject derivative_imp() const override;
  private: Abstract3dMathObject copy_imp() const override;
};

template<typename Value>
AbstractMathObjectBase<Value>::~AbstractMathObjectBase<Value>() = default;

template<typename Value>
Value AbstractMathObjectBase<Value>::compute(const float factor) const
{
  return this->compute_imp(factor);
}

template<typename Value>
std::shared_ptr<AbstractMathObjectBase<Value>> AbstractMathObjectBase<Value>::derivative_imp() const
{
  return BaseDerivative<Value>::make(this->copy());
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
