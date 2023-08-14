#pragma once

struct Vector2D {
  int x;
  int y;

  Vector2D operator*(int) const;
};