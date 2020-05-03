//
// Created by Igor Frank on 26.04.20.
//

#ifndef DUALCONTOURDEMO_VOXPARSER_H
#define DUALCONTOURDEMO_VOXPARSER_H

#include <Data/MainChunk.h>
#include <Data/TransformationTree.h>
#include <map>
#include <string>
#include <vector>
class VoxParser {
public:
  static VoxParser &getInstance();
  void loadFile(const std::string &path);
  MainChunk &getRoot();
  bool isFileLoaded() const;

private:
  enum class chunkType { UNKNOWN, MAIN, SIZE, PACK, XYZI, RGBA, MATT, nTRN, nGRP, nSHP, MATL, LAYR };

  VoxParser() = default;

  bool fileLoaded = false;
  MainChunk root{};
  std::vector<TransformationTree> transformTree{};

  static bool checkHeader(std::vector<unsigned char>::iterator &it);
  static bool checkMainChunk(std::vector<unsigned char>::iterator &it, int bytesCount);
  bool parseChunks(std::vector<unsigned char>::iterator &it, std::vector<unsigned char>::iterator &itEnd);
  static int getInt(std::vector<unsigned char>::iterator &it);
  static std::string getString(std::vector<unsigned char>::iterator &it, int length = 4);
  static chunkType string2enum(const std::string &type);
  std::map<std::string, std::string> getDictionary(std::vector<unsigned char>::iterator &it);
  glm::vec3 getTranslation(const std::map<std::string, std::string> &dictionary);
  glm::mat3 getRotation(const std::map<std::string, std::string> &dictionary);
  std::vector<int> applyTree(const int treeIndex);
};

#endif // DUALCONTOURDEMO_VOXPARSER_H
