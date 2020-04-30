//
// Created by Igor Frank on 26.04.20.
//

#ifndef DUALCONTOURDEMO_VOXPARSER_H
#define DUALCONTOURDEMO_VOXPARSER_H

#include <Data/MainChunk.h>
#include <string>
#include <vector>
class VoxParser {
public:
  void loadFile(const std::string &path);
  static VoxParser &getInstance();

private:
  VoxParser() = default;
  ;
  MainChunk root{};

public:
  MainChunk &getRoot();

private:
  enum chunkType { UNKNOWN, MAIN, SIZE, PACK, XYZI, RGBA, MATT, nTRN, nGRP, nSHP, MATL, LAYR };
  static bool checkHeader(std::vector<unsigned char>::iterator &it);
  static bool checkMainChunk(std::vector<unsigned char>::iterator &it, int bytesCount);
  bool parseChunks(std::vector<unsigned char>::iterator &it, std::vector<unsigned char>::iterator &itEnd);
  static int getInt(std::vector<unsigned char>::iterator &it);
  static std::string getString(std::vector<unsigned char>::iterator &it, int length = 4);
  static chunkType string2enum(const std::string &type);
};

#endif // DUALCONTOURDEMO_VOXPARSER_H
