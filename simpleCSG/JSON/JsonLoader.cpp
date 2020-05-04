//
// Created by Igor Frank on 04.05.20.
//

#include "JsonLoader.h"
#include "CuboidCsgLeaf.h"
#include "OperationCsgNode.h"
#include "SphereCsgLeaf.h"
#include <fstream>
#include <nlohmann/json.hpp>

void JsonLoader::loadFile(const std::string &path) {
  std::ifstream file(path);
  nlohmann::json jsonFile;
  file >> jsonFile;

  root = getOperand(jsonFile);
  jsonLoaded = true;
}

std::unique_ptr<BaseCsgNode> JsonLoader::getOperand(const nlohmann::json &json) {
  auto type = json.at("node");
  if (type == "Operation") {
    auto node = std::make_unique<OperationCsgNode>(OperationCsgNode::OperationType::UNION); // TODO
    (*node).op1 = getOperand(json.at("operand1"));
    (*node).op2 = getOperand(json.at("operand2"));
    return node;
  }
  auto originObject = json.at("origin");
  auto origin = glm::vec3(originObject.at("x"), originObject.at("y"), originObject.at("z"));
  if (type == "Cuboid") {
    auto halfDimObj = json.at("halfDimensions");
    auto halfDim = glm::vec3(halfDimObj.at("x"), halfDimObj.at("y"), halfDimObj.at("z"));
    return std::make_unique<CuboidCsgLeaf>(BaseCsgShape::ShapeType::CUBOID, origin, halfDim);
  }
  if (type == "Sphere") {
    auto radius = json.at("radius");
    return std::make_unique<SphereCsgLeaf>(BaseCsgShape::ShapeType::SPHERE, origin, radius);
  }
}
const JsonLoader::RootNode &JsonLoader::getRoot() const { return root; }

JsonLoader &JsonLoader::getInstance() {
  static JsonLoader instance;
  return instance;
}
bool JsonLoader::isJsonLoaded() const { return jsonLoaded; }
