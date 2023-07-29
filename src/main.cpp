
#include <iostream>
#include <vector>

#include "math.hh"
#include "math_object.hh"

void main(const char **args, const int count)
{
  std::vector<Abstract3dMathObject> list;
  list.push_back(CircleMathObject::make(2.0f));

  for (const auto obj : list) {
    const auto derivative = obj->derivative();
    for (float step = 0.0f; step < 2.0f; step += 0.25f){
      std::cout << obj->compute(step * 3.14f) << std::endl;
      std::cout << "- " << derivative->compute(step * 3.14f) << std::endl;
    }
  }
}