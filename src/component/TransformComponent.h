#pragma once

#include "Vector2D.h"
#include "ComponentFlag.h"

struct TransformComponent {
  Vector2D position;
  Vector2D speed;
  int      width;
  int      height;

  int centerX() const;
  int centerY() const;

  static constexpr ComponentFlag FLAG{ ComponentFlag::TRANSFORM };
};