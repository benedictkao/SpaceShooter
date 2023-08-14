#pragma once
#include "Vector2D.h"

struct TransformComponent {
  Vector2D position;
  Vector2D speed;
  int width;
  int height;

  int centerX() const;
  int centerY() const;
};