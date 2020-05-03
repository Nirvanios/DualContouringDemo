//
// Created by Igor Frank on 28.04.20.
//

#ifndef DUALCONTOURDEMO_DENSITY_H
#define DUALCONTOURDEMO_DENSITY_H

#include "operations.h"
#include "shapes.h"
#include <VoxParser.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <optional>
#include <vector3d.hh>

double Density_Func(const glm::vec3 &pos);

double Density_FuncDC(const DualContouring::Vector3D &pos);

#endif // DUALCONTOURDEMO_DENSITY_H
