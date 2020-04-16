//
// Created by Igor Frank on 14.04.20.
//


#include <cmath>

#include "operations.h"

double Operations::Intersect(double obj1, double obj2) {
  return std::max(obj1, obj2);
}

double Operations::Difference(double obj1, double obj2) {
  return std::max(obj1, -obj2);
}

double Operations::Union(double obj1, double obj2) {
  return std::min(obj1, obj2);
}
