#pragma once

struct Point {
  int x;
  int y;

  Point operator-(const Point&) const;
  bool operator==(const Point&) const noexcept;
};

struct Vector2D {
  float x;
  float y;

  Vector2D operator*(float) const;
  bool     operator==(const Vector2D&) const noexcept;
};

namespace Direction {
  constexpr Vector2D UP{ 0, -1 };
  constexpr Vector2D DOWN{ 0, 1 };
  constexpr Vector2D LEFT{ -1, 0 };
  constexpr Vector2D RIGHT{ 1, 0 };
} // namespace Direction