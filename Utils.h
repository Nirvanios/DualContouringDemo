//
// Created by Igor Frank on 14.04.20.
//

#ifndef DUALCONTOURDEMO_UTILS_H
#define DUALCONTOURDEMO_UTILS_H

#include <iostream>

namespace Utils{

std::string readFile(const std::string& path);

template<typename containerIn, typename containerOut>
containerOut flatten(containerIn &&input){
  containerOut result;
  for(const auto &item : input){
    result.insert(result.end(), item.begin(), item.end());
  }
  return result;
}

}


#endif // DUALCONTOURDEMO_UTILS_H
