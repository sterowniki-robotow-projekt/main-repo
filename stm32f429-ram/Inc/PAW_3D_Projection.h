#pragma once
#include "PAW_Matrix.h"
#include <cstdlib>
#include <cmath>

PAW_Vector project_3D_to_2D(const PAW_Vector point_position);
PAW_Matrix projection_matrix(const float left, const float right, const float top, const float bottom, const float near, const float far);
