//
// Created by Igor Frank on 14.04.20.
//

#ifndef DUALCONTOURDEMO_UTILS_H
#define DUALCONTOURDEMO_UTILS_H

#include <fstream>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

namespace Utils {

template <typename T> T readFile(const std::string &path) {
  std::ifstream file(path);
  if (file.is_open()) {
    return T(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
  }
}

template <typename containerIn, typename containerOut> containerOut flatten(containerIn &&input) {
  containerOut result;
  for (const auto &item : input) {
    result.insert(result.end(), item.begin(), item.end());
  }
  return result;
}

} // namespace Utils

#endif // DUALCONTOURDEMO_UTILS_H
