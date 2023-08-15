#pragma once

struct Vector2D {
  int x;
  int y;

  Vector2D operator*(int) const;
};

namespace Direction {
  constexpr Vector2D UP{ 0, -1 };
  constexpr Vector2D DOWN{ 0, 1 };
  constexpr Vector2D LEFT{ -1, 0 };
  constexpr Vector2D RIGHT{ 1, 0 };
} // namespace Direction