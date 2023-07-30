
#include <iostream>
#include <vector>

#include "math.hh"
#include "math_object.hh"

void main(const char **args, const int count)
{
  std::vector<MathObject3dPtr> list;
  list.push_back(CircleMathObject::make(2.0f));

  for (const auto obj : list) {
    const auto derivative = obj->derivative();
    for (float step = 0.0f; step < 1.0f; step += 0.125f) {
      std::cout << obj->compute(step);
      std::cout << ": " << derivative->compute(step) << std::endl;
    }
  }
}