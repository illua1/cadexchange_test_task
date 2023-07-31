
#pragma once

#include <memory>
#include <iostream>

#include "math.hh"

template<typename Value>
class AbstractMathObjectBase {
  protected: const char *name;

  public: AbstractMathObjectBase(const char *obj_name) : name(obj_name) {}
  public: virtual ~AbstractMathObjectBase() = 0;

  public: const char *get_name() const;

  /* Factor in range [0, 1]. Mapped in [0, pi * 2] range for cyclic curve. */
  public: Value compute(const float factor) const;
  protected: virtual Value compute_imp(const float factor) const = 0;

  public: std::shared_ptr<AbstractMathObjectBase> derivative() const;
  protected: virtual std::shared_ptr<AbstractMathObjectBase> derivative_imp() const;

  public: std::shared_ptr<AbstractMathObjectBase> copy() const;
  protected: virtual std::shared_ptr<AbstractMathObjectBase> copy_imp() const = 0;
};

/* 3D calculation & derivativition only supported yet. */

using AbstractMathObject3d = AbstractMathObjectBase<Float3>;

using MathObject3dPtr = std::shared_ptr<AbstractMathObject3d>;

class BaseDerivative : public AbstractMathObject3d {
  private: const MathObject3dPtr base;

  public: BaseDerivative(const MathObject3dPtr obj_base) : AbstractMathObject3d("Base Derivative"), base(obj_base) {}

  public: static MathObject3dPtr make(const MathObject3dPtr obj_base)
  {
    return std::make_shared<BaseDerivative>(obj_base);
  }

  public: Float3 compute_imp(const float factor) const override final
  {
    const float zero_offset = 0.001f;
    const Float3 a_value = base->compute(factor - zero_offset);
    const Float3 b_value = base->compute(factor + zero_offset);
    const Float3 tangent = normalized(a_value - b_value);
    return tangent;
  }

  public: MathObject3dPtr derivative_imp() const override final
  {
    return std::make_shared<BaseDerivative>(*this);
  }

  public: MathObject3dPtr copy_imp() const override final
  {
    return std::make_shared<BaseDerivative>(base);
  }
};

class CircleMathObject : public AbstractMathObject3d {
  public: const float radius;

  public: CircleMathObject(const float circle_radius) : AbstractMathObject3d("Circle"), radius(circle_radius) {}
  public: ~CircleMathObject() = default;

  public: static MathObject3dPtr make(const float circle_radius)
  {
    return std::make_shared<CircleMathObject>(circle_radius);
  }

  private: Float3 compute_imp(const float factor) const override;
  private: MathObject3dPtr derivative_imp() const override;
  private: MathObject3dPtr copy_imp() const override;
};

class CircleDerivativeMathObject : public CircleMathObject {
  public: using CircleMathObject::CircleMathObject;
  public: ~CircleDerivativeMathObject() = default;

  public: static MathObject3dPtr make(const float circle_radius)
  {
    return std::make_shared<CircleDerivativeMathObject>(circle_radius);
  }

  private: Float3 compute_imp(const float factor) const override final;
  private: MathObject3dPtr derivative_imp() const override final;
  private: MathObject3dPtr copy_imp() const override final;
};

class ElipseMathObject : public AbstractMathObject3d {
  protected: float x;
  protected: float y;

  public: ElipseMathObject(const float x_size, const float y_size) : AbstractMathObject3d("Elipse"), x(x_size), y(y_size) {}
  public: ~ElipseMathObject() = default;

  public: static MathObject3dPtr make(const float x_size, const float y_size)
  {
    return std::make_shared<ElipseMathObject>(x_size, y_size);
  }

  private: Float3 compute_imp(const float factor) const override;
  private: MathObject3dPtr derivative_imp() const override;
  private: MathObject3dPtr copy_imp() const override;
};

class ElipseDerivativeMathObject : public ElipseMathObject {
  public: using ElipseMathObject::ElipseMathObject;
  public: ~ElipseDerivativeMathObject() = default;

  public: static MathObject3dPtr make(const float x_size, const float y_size)
  {
    return std::make_shared<ElipseDerivativeMathObject>(x_size, y_size);
  }

  private: Float3 compute_imp(const float factor) const override final;
  private: MathObject3dPtr derivative_imp() const override final;
  private: MathObject3dPtr copy_imp() const override final;
};

class HelixMathObject : public AbstractMathObject3d {
  protected: const float radius;
  protected: const float step_height;
  protected: const int steps_amount;

  public: HelixMathObject(const float helix_radius, const float helix_step_height, const int helix_steps_amount) :
    AbstractMathObject3d("Helix"), radius(helix_radius), step_height(helix_step_height), steps_amount(helix_steps_amount) {}
  public: ~HelixMathObject() = default;

  public: static MathObject3dPtr make(const float helix_radius, const float helix_step_height, const int helix_steps_amount)
  {
    return std::make_shared<HelixMathObject>(helix_radius, helix_step_height, helix_steps_amount);
  }

  private: Float3 compute_imp(const float factor) const override;
  private: MathObject3dPtr derivative_imp() const override;
  private: MathObject3dPtr copy_imp() const override;
};

class HelixDerivativeMathObject : public HelixMathObject {
  public: using HelixMathObject::HelixMathObject;
  public: ~HelixDerivativeMathObject() = default;

  public: static MathObject3dPtr make(const float helix_radius, const float helix_step_height, const int helix_steps_amount)
  {
    return std::make_shared<HelixDerivativeMathObject>(helix_radius, helix_step_height, helix_steps_amount);
  }

  private: Float3 compute_imp(const float factor) const override final;
  private: MathObject3dPtr derivative_imp() const override final;
  private: MathObject3dPtr copy_imp() const override final;
};

/* Implemenations of base template class. */

template<typename Value>
const char *AbstractMathObjectBase<Value>::get_name() const
{
  return name;
}

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
  static_assert(std::is_same_v<Value, Float3>);
  return BaseDerivative::make(this->copy());
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