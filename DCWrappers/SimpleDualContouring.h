//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_SIMPLEDUALCONTOURING_H
#define DUALCONTOURDEMO_SIMPLEDUALCONTOURING_H

#include "BaseDualContouring.h"
#include <Data/MainChunk.h>
#include <functional>

class SimpleDualContouring : public BaseDualContouring {

public:
  void computeMesh() override;
};

#endif // DUALCONTOURDEMO_SIMPLEDUALCONTOURING_H
