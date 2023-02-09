#pragma once
#include "Engine/Transform.h"

namespace Math {

float EaseIn(float* speed, float acceleration, float max);
float EaseOut(float* speed, float acceleration, float min);
XMVECTOR Normal(XMVECTOR dir);

}

