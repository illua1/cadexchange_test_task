
#include <array>

#include <numeric>

template<int axis>
class Float {
  std::array<float, axis> base;

  public: Float() = default;
  public: Float(const float value) {
    for (float &v : base) {
      v = value;
    }
  }
  public: Float(const Float &other) = default;

  public: Float(std::initializer_list<float> base_values)
  {
    for (int i = 0; i < axis; i++) {
      base[i] = base_values.begin()[i];
    }
  }
 
  public: const float &operator [] (const int index) const
  {
    return base[index];
  }
 
  public: float &operator [] (const int index)
  {
    return base[index];
  }
 
  public: Float<axis> operator - (const Float<axis> &other) const
  {
    Float<axis> value = *this;
    for (int i = 0; i < axis; i++) {
      value[i] -= other[i];
    }
    return value;
  }
};

template<int axis>
inline Float<axis> normalize(const Float<axis> &vector)
{
  
}

template<int axis>
inline float length(const Float<axis> &vector)
{
  float accum = 0.0f;
  for (int i = 0; i < axis; i++) {
    accum += vector[i] * vector[i];
  }
  return std::sqrt(accum);
}

using Float3 = Float<3>;