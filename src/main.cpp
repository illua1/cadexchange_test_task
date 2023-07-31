
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <initializer_list>
#include <functional>
#include <random>
#include <numeric>
#include <cstdlib>

#include "math.hh"
#include "math_object.hh"

enum CurveTypes : int8_t {
  Circle,
  Elipse,
  Spiral,
};

using TProbability = std::pair<CurveTypes, float>;
static std::vector<MathObject3dPtr> random_curves(const int amount, std::initializer_list<TProbability> types)
{
  std::map<CurveTypes, float> weight_map;
  for (auto i = types.begin(); i != types.end(); i++) {
    if (weight_map.find(i->first) != weight_map.end()) {
      weight_map[i->first] += i->second;
    }else{
      weight_map[i->first] = i->second;
    }
  }
  
  if (weight_map.empty()) {
    return {};
  }

  std::map<CurveTypes, std::function<MathObject3dPtr(int)>> generators_map;
  if (weight_map.find(Circle) != weight_map.end()) {
    generators_map[Circle] = [](const int hash) -> MathObject3dPtr {
      std::srand(hash);
      const float radius = (float(std::rand()) / float(RAND_MAX));
      return CircleMathObject::make(radius * 6160.0f);
    };
  }
  if (weight_map.find(Elipse) != weight_map.end()) {
    generators_map[Elipse] = [](const int hash) -> MathObject3dPtr {
      std::srand(hash - 2);
      const float x = (float(std::rand()) / float(RAND_MAX));
      std::srand(hash + 3);
      const float y = (float(std::rand()) / float(RAND_MAX));
      return ElipseMathObject::make(x * 3300.0f, y * 8300.0f);
    };
  }
  if (weight_map.find(Spiral) != weight_map.end()) {
    generators_map[Spiral] = [](const int hash) -> MathObject3dPtr {
      std::srand(hash + 2);
      const float step_size = (float(std::rand()) / float(RAND_MAX));
      std::srand(hash + 55);
      const float radius = (float(std::rand()) / float(RAND_MAX));
      std::srand(hash - 4);
      const int step_amount = (float(std::rand()) / float(RAND_MAX)) * 150.0f;
      return HelixMathObject::make(radius * 5110.0f, step_size * 960.0f, step_amount);
    };
  }

  std::vector<float> weights;
  std::vector<CurveTypes> type_keys;
  weights.resize(weight_map.size());
  type_keys.resize(weight_map.size());
  int index = 0;
  for (auto i = weight_map.begin(); i != weight_map.end(); i++) {
    type_keys[index] = i->first;
    weights[index] = i->second;
    index++;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::discrete_distribution<int> d_ct_d(weights.begin(), weights.end());

  std::vector<MathObject3dPtr> results;
  results.resize(amount);

  for (int i = 0; i < amount; i++) {
    const int index = d_ct_d(gen);
    const CurveTypes &type = type_keys[index];
    const auto &generator = generators_map[type];
    results[i] = generator(i);
  }

  return results;
}

void main(const char **args, const int count)
{
  std::vector<MathObject3dPtr> list = random_curves(15, {{Circle, 30.0f}, {Elipse, 30.0f}, {Spiral, 10.0f}, {Elipse, 10.0f}});

  std::cout << std::setprecision(3) << std::fixed;
  for (const auto obj : list) {
    const auto derivative = obj->derivative();
    std::cout << obj->get_name() << ":" << std::endl;
    {
      const float step = pi / 4.0f;
      std::cout << std::setw(4);
      std::cout << obj->compute(step) << "\t: ";
      std::cout << derivative->compute(step) << std::endl;
    }
    std::cout << std::endl;
  }

  std::vector<MathObject3dPtr> circles;
  std::copy_if(list.begin(), list.end(),
               std::back_inserter(circles),
               [](const MathObject3dPtr &ptr) { return dynamic_cast<CircleMathObject *>(&*ptr) != nullptr; });

  std::sort(circles.begin(), circles.end(), [](const MathObject3dPtr &a_ptr, const MathObject3dPtr &b_ptr) -> bool {
    const CircleMathObject &a = static_cast<CircleMathObject &>(*a_ptr);
    const CircleMathObject &b = static_cast<CircleMathObject &>(*b_ptr);
    return a.radius < b.radius;
  });

  // Parrallel reduce...
  const float total_radii = std::accumulate(circles.begin(), circles.end(), 0.0f,
    [](const float prev, const MathObject3dPtr &ptr) -> float {
      const CircleMathObject &circle = static_cast<CircleMathObject &>(*ptr);
      return circle.radius + prev;
    });

  std::cout << "Total sum: " << total_radii << std::endl;
}