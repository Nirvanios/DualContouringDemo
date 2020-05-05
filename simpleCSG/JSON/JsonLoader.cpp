//
// Created by Igor Frank on 04.05.20.
//

#include "JsonLoader.h"
#include "ConeCsgShape.h"
#include "CuboidCsgShape.h"
#include "CylinderCsgShape.h"
#include "ElipsoidCsgShape.h"
#include "OperationCsgNode.h"
#include "SphereCsgShape.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <shapes.h>

void JsonLoader::loadFile(const std::string &path) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("File \"" + path + "\" does not exist!");
  }

  std::ifstream file(path);
  nlohmann::json jsonFile;
  file >> jsonFile;

  root = getOperand(jsonFile);
  jsonLoaded = true;
}

std::unique_ptr<BaseCsgNode> JsonLoader::getOperand(const nlohmann::json &json) {
  auto node = json.at("node");
  if (node == "Operation") {
    auto newNode = std::make_unique<OperationCsgNode>(string2enumOp(json.at("type"))); // TODO
    (*newNode).op1 = getOperand(json.at("operand1"));
    (*newNode).op2 = getOperand(json.at("operand2"));
    return newNode;
  }
  if (node == "Shape") {
    auto type = string2enumShape(json.at("type"));
    auto originObject = json.at("origin");
    auto origin = glm::vec3(originObject.at("x"), originObject.at("y"), originObject.at("z"));
    if (type == BaseCsgShape::ShapeType::CUBOID) {
      auto halfDimObj = json.at("halfDimensions");
      auto halfDim = glm::vec3(halfDimObj.at("x"), halfDimObj.at("y"), halfDimObj.at("z"));
      return std::make_unique<CuboidCsgShape>(origin, halfDim);
    }
    if (type == BaseCsgShape::ShapeType::SPHERE) {
      auto radius = json.at("radius");
      return std::make_unique<SphereCsgShape>(origin, radius);
    }
    if (type == BaseCsgShape::ShapeType::CONE) {
      auto constantsObj = json.at("Constants");
      auto constants = glm::vec3(constantsObj.at("x"), constantsObj.at("y"), constantsObj.at("z"));
      return std::make_unique<ConeCsgShape>(origin, constants);
    }
    if (type == BaseCsgShape::ShapeType::ELIPSOID) {
      auto constantsObj = json.at("Constants");
      auto constants = glm::vec3(constantsObj.at("x"), constantsObj.at("y"), constantsObj.at("z"));
      return std::make_unique<ElipsoidCsgShape>(origin, constants);
    }
    if (type == BaseCsgShape::ShapeType::CYLINDER) {
      auto constantsObj = json.at("Constants");
      auto constants = glm::vec3(constantsObj.at("x"), constantsObj.at("y"), constantsObj.at("z"));
      auto axis = json.at("Axis");
      return std::make_unique<CylinderCsgShape>(origin, constants, Shapes::string2enum(axis));
    }
  }
}

OperationCsgNode::OperationType JsonLoader::string2enumOp(const std::string &type) {
  if (type == "Union")
    return OperationCsgNode::OperationType::UNION;
  if (type == "Difference")
    return OperationCsgNode::OperationType::DIFFERENCE;
  if (type == "Intersect")
    return OperationCsgNode::OperationType::INTERSECT;
}

BaseCsgShape::ShapeType JsonLoader::string2enumShape(const std::string &type) {
  if (type == "Cone")
    return BaseCsgShape::ShapeType::CONE;
  if (type == "Cuboid")
    return BaseCsgShape::ShapeType::CUBOID;
  if (type == "Cylinder")
    return BaseCsgShape::ShapeType::CYLINDER;
  if (type == "Sphere")
    return BaseCsgShape::ShapeType::SPHERE;
  if (type == "Elipsoid")
    return BaseCsgShape::ShapeType::ELIPSOID;
}

const JsonLoader::RootNode &JsonLoader::getRoot() const { return root; }

JsonLoader &JsonLoader::getInstance() {
  static JsonLoader instance;
  return instance;
}
bool JsonLoader::isJsonLoaded() const { return jsonLoaded; }
