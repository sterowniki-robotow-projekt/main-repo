#pragma once
#include "PAW_Color.h"
#include "PAW_Scene.h"
#include "PAW_Figure.h"

void PAW_MakeStarFromFigure(PAW_Figure &figure, const PAW_Vector position, const float radius, const PAW_Color color);
void PAW_MakeDonutFromFigure(PAW_Figure &figure, const PAW_Vector position, const float radius1, const float radius2, const PAW_Color color);
void PAW_MakeFeatherFromFigure(PAW_Figure &figure);