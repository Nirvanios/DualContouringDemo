//
// Created by Igor Frank on 14.04.20.
//

#include <cmath>

namespace Operation{
double inline Intersect(double obj1, double obj2) {
  return std::max(obj1, obj2);
}

double inline Difference(double obj1, double obj2) {
  return std::max(obj1, -obj2);
}

double inline Union(double obj1, double obj2) { return std::min(obj1, obj2); }
}