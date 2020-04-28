//
// Created by Igor Frank on 26.04.20.
//

#include "VoxParser.h"
#include <Utils.h>
#include <VoxParser/Data/MainChunk.h>
#include <vector>

MainChunk VoxParser::parseFile(const std::string &path) {

  auto rawData = Utils::readFile<std::vector<unsigned char>>(path);
  auto it = rawData.begin();
  auto itEnd = rawData.end();
  if (!checkHeader(it)) {
    throw std::runtime_error("Bad .vox header.");
  }
  if (!checkMainChunk(it, rawData.size())) {
    throw std::runtime_error("Bad .vox MAIN chunk.");
  }
  MainChunk root{};
  if (!parseChunks(it, itEnd, root)) {
    throw std::runtime_error("Bad .vox MAIN chunk structure.");
  }

  return root;
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
bool VoxParser::parseChunks(std::vector<unsigned char>::iterator &it, std::vector<unsigned char>::iterator &itEnd,
                            MainChunk &root) {
  int numVoxels = 0;
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
        auto y = *(it++);
        auto z = *(it++);
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
    case nTRN:
    case nGRP:
    case nSHP:
    case LAYR:
    case MATL:
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
