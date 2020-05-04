//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_JSONLOADER_H
#define DUALCONTOURDEMO_JSONLOADER_H

#include "BaseCsgNode.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
class JsonLoader {
  using RootNode = std::unique_ptr<BaseCsgNode>;

public:
  JsonLoader() = default;

  void loadFile(const std::string &path);
  static JsonLoader &getInstance();
  [[nodiscard]] const RootNode &getRoot() const;
  [[nodiscard]] bool isJsonLoaded() const;

private:
  std::unique_ptr<BaseCsgNode> getOperand(const nlohmann::basic_json<> &json);
  RootNode root;
  bool jsonLoaded = false;
};

#endif // DUALCONTOURDEMO_JSONLOADER_H
