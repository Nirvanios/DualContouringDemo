//
// Created by Igor Frank on 26.04.20.
//

#include "VoxParser.h"
#include <Utils.h>
#include <map>
#include <sstream>
#include <vector>

void VoxParser::loadFile(const std::string &path) {

  auto rawData = Utils::readFile<std::vector<unsigned char>>(path);
  auto it = rawData.begin();
  auto itEnd = rawData.end();
  if (!checkHeader(it)) {
    throw std::runtime_error("Bad .vox header.");
  }
  if (!checkMainChunk(it, rawData.size())) {
    throw std::runtime_error("Bad .vox MAIN chunk.");
  }
  if (!parseChunks(it, itEnd)) {
    throw std::runtime_error("Bad .vox MAIN chunk structure.");
  }
  applyTree(0);
  for (auto &model : root.models) {
    model.applyTransformation();
  }
  fileLoaded = true;
}

bool VoxParser::checkHeader(std::vector<unsigned char>::iterator &it) {
  auto headerId = getString(it);
  int fileVersion = getInt(it);
  return headerId == "VOX " && fileVersion == 150;
}

int VoxParser::getInt(std::vector<unsigned char>::iterator &it) {
  int number = 0;
  for (auto i = 0; i < 4; ++i) {
    number += *it << (i * 8);
    ++it;
  }
  return number;
}

bool VoxParser::checkMainChunk(std::vector<unsigned char>::iterator &it, int bytesCount) {
  auto chunkId = getString(it);
  int byteContents = getInt(it);
  int byteChildrens = getInt(it);
  return chunkId == "MAIN" && byteContents == 0 && byteChildrens + 20 == bytesCount;
}
bool VoxParser::parseChunks(std::vector<unsigned char>::iterator &it, std::vector<unsigned char>::iterator &itEnd) {
  int numVoxels = 0;
  int numChilds = 0;
  std::map<std::string, std::string> dictionary;
  while (it != itEnd) {
    auto chunkType = getString(it);
    auto contentSize = getInt(it);
    auto childrenSize = getInt(it);
    switch (string2enum(chunkType)) {
    case chunkType::PACK:
      root.models.reserve(getInt(it));
      break;
    case chunkType::SIZE:
      root.models.emplace_back((glm::uvec3(getInt(it), getInt(it), getInt(it))));
      break;
    case chunkType::XYZI:
      numVoxels = getInt(it);
      for (auto i = 0; i < numVoxels; ++i) {
        auto x = *(it++);
        auto z = *(it++);
        auto y = *(it++);
        auto colorIndex = *(it++);
        root.models.back().addVoxel(glm::vec3(x, y, z), colorIndex);
      }
      break;
    case chunkType::RGBA:
      root.palettes.emplace_back();
      it += contentSize + childrenSize;
      break;
    case chunkType::MATT:
      root.material.emplace_back();
      it += contentSize + childrenSize;
      break;
    case chunkType::MAIN:
      return false;
    case chunkType::nTRN:
      transformTree.emplace_back();
      transformTree.back().type = TransformationTree::TransformNodeType::TRANSFORM;
      transformTree.back().nodeId = getInt(it);
      getDictionary(it); // Node Attrib
      transformTree.back().childIds.emplace_back(getInt(it));
      getInt(it);
      getInt(it);
      getInt(it); // Reserved, LayerID, Frame count
      dictionary = getDictionary(it);
      transformTree.back().rotation = getRotation(dictionary);
      transformTree.back().translation = getTranslation(dictionary);
      break;
    case chunkType::nGRP:
      transformTree.emplace_back();
      transformTree.back().type = TransformationTree::TransformNodeType::GROUP;
      transformTree.back().nodeId = getInt(it);
      getDictionary(it); // Node Attrib
      numChilds = getInt(it);
      for (auto i = 0; i < numChilds; ++i) {
        transformTree.back().childIds.emplace_back(getInt(it));
      }
      break;
    case chunkType::nSHP:
      transformTree.emplace_back();
      transformTree.back().type = TransformationTree::TransformNodeType::SHAPE;
      transformTree.back().nodeId = getInt(it);
      getDictionary(it); // Node Attrib
      getInt(it);        // Num of models
      transformTree.back().childIds.emplace_back(getInt(it));
      getDictionary(it); // model attrib
      break;
    case chunkType::LAYR:
    case chunkType::MATL:
    default:
      it += contentSize + childrenSize;
      break;
    }
  }
  return true;
}

std::string VoxParser::getString(std::vector<unsigned char>::iterator &it, int length) {
  std::string parsed(it, it + length);
  it += length;
  return parsed;
}

std::map<std::string, std::string> VoxParser::getDictionary(std::vector<unsigned char>::iterator &it) {
  std::map<std::string, std::string> dictionary;
  auto size = getInt(it);
  for (auto i = 0; i < size; ++i)
    dictionary.insert({getString(it, getInt(it)), getString(it, getInt(it))});
  return dictionary;
}

glm::vec3 VoxParser::getTranslation(const std::map<std::string, std::string> &dictionary) {
  try {
    auto str = dictionary.at("_t");

    std::vector<int> array;
    std::stringstream ss(str);
    int temp;
    while (ss >> temp)
      array.push_back(temp);
    return glm::vec3(array[0], array[1], array[2]);
  } catch (std::out_of_range &e) {
    return glm::vec3(0);
  }
}

glm::mat3 VoxParser::getRotation(const std::map<std::string, std::string> &dictionary) {
  try {
    auto value = std::stoi(dictionary.at("_r"));
    glm::vec3 r1(0);
    glm::vec3 r2(0);
    glm::vec3 r3(0);
    auto i1 = value & 0x3;
    auto i2 = (value & 0xC) >> 2;
    auto s1 = ((value & 0x10) >> 4);
    auto s2 = ((value & 0x20) >> 5);
    auto s3 = ((value & 0x40) >> 6);
    r1[i1] = 1 - (2 * s1);
    r2[i2] = 1 - (2 * s2);
    r3.x = 1 - (2 * s3);
    //    if (r1 == glm::vec3(1, 0, 0))
    //      r3.y =0;//1
    //    else if (r1 == glm::vec3(0, 0, 1))
    //      r3.x = -1;
    //    else
    //      r3.z = 0;//1

    return glm::mat3(r1, r2, r3);

  } catch (std::out_of_range &e) {
    return glm::mat3(1);
  }
}

std::vector<int> VoxParser::applyTree(const int treeIndex) {
  std::vector<int> models{};
  auto &currNode = transformTree[treeIndex];
  if (currNode.type == TransformationTree::TransformNodeType::SHAPE)
    return currNode.childIds;
  for (const auto child : currNode.childIds) {
    auto tmp = applyTree(child);
    for (const auto model : tmp) {
      root.models[model].setRotation(currNode.rotation);
      root.models[model].setTranslation(currNode.translation);
    }
    models.insert(models.begin(), tmp.begin(), tmp.end());
  }
  return models;
}

VoxParser::chunkType VoxParser::string2enum(const std::string &type) {
  if (type == "PACK")
    return chunkType::PACK;
  if (type == "MAIN")
    return chunkType::MAIN;
  if (type == "SIZE")
    return chunkType::SIZE;
  if (type == "XYZI")
    return chunkType::XYZI;
  if (type == "RGBA")
    return chunkType::RGBA;
  if (type == "MATT")
    return chunkType::MATT;
  if (type == "nTRN")
    return chunkType::nTRN;
  if (type == "nGRP")
    return chunkType::nGRP;
  if (type == "nSHP")
    return chunkType::nSHP;
  if (type == "MATL")
    return chunkType::MATL;
  if (type == "LAYR")
    return chunkType::LAYR;
  return chunkType ::UNKNOWN;
}

VoxParser &VoxParser::getInstance() {
  static VoxParser instance;
  return instance;
}
MainChunk &VoxParser::getRoot() { return root; }
bool VoxParser::isFileLoaded() const { return fileLoaded; }
