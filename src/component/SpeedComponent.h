#pragma once

#include "Vector2D.h"

struct SpeedComponent {
  int x;
  int y;

  SpeedComponent() = default;
  constexpr SpeedComponent(int x, int y) : x(x), y(y) {}
  constexpr SpeedComponent(Vector2D v) : x(v.x), y(v.y) {}

  static constexpr ComponentFlag FLAG{ ComponentFlag::SPEED };
};