#include "Vector2D.h"

Vector2D Vector2D::operator*(int multiplier) const {
  Vector2D result;
  result.x = x * multiplier;
  result.y = y * multiplier;
  return result;
}

bool Vector2D::operator==(const Vector2D& rhs) const noexcept {
  return x == rhs.x && y == rhs.y;
}