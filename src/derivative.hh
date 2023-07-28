
#include <memory>

#include "math_vector.hh"

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