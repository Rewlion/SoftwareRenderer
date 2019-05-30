#pragma once

#include "Math.hpp"
#include "Color.h"

struct Vertex
{
    Math::fVec3 XYZ;
    Math::fVec3 Normal;
    RGB Color;
    Math::fVec2 UV;
};