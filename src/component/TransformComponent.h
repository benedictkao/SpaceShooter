#pragma once

#include "ComponentFlag.h"
#include "Vector2D.h"

struct TransformComponent {
  Point position;
  int   width;
  int   height;

  static constexpr ComponentFlag FLAG{ ComponentFlag::TRANSFORM };
};