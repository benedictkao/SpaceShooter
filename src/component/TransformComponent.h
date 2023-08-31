#pragma once

#include "ComponentFlag.h"
#include "Vector2D.h"

struct TransformComponent {
  Vector2D position;
  int      width;
  int      height;

  constexpr int centerX() const { return position.x + width / 2; }
  constexpr int centerY() const { return position.y + height / 2; };

  static constexpr ComponentFlag FLAG{ ComponentFlag::TRANSFORM };
};