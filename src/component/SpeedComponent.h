#pragma once

#include "Vector2D.h"

struct SpeedComponent {
  Vector2D direction;
  unsigned int speed;

  static constexpr ComponentFlag FLAG{ ComponentFlag::SPEED };
};