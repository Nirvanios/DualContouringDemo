//
// Created by Igor Frank on 14.04.20.
//

#include <fstream>

#include "Utils.h"

std::string Utils::readFile(const std::string& path) {
  std::ifstream file(path);
  if (file.is_open()) {
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
  }
}
