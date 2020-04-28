//
// Created by Igor Frank on 26.04.20.
//

#ifndef DUALCONTOURDEMO_MAINCHUNK_H
#define DUALCONTOURDEMO_MAINCHUNK_H

#include "MaterialChunk.h"
#include "ModelChunk.h"
#include "PaletteChunk.h"
#include <vector3d.hh>
#include <vector>
class MainChunk {
public:
  std::vector<ModelChunk> models{};
  std::vector<PaletteChunk> palettes{};
  std::vector<MaterialChunk> material{};

  double Density(const DualContouring::Vector3D &pos) const;
};

#endif // DUALCONTOURDEMO_MAINCHUNK_H
