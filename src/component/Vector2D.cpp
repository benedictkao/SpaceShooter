#include "Vector2D.h"

Point Point::operator-(const Point& rhs) const {
  Point p = { x - rhs.x, y - rhs.y };
  return p;
}

bool Point::operator==(const Point& rhs) const noexcept {
  return x == rhs.x && y == rhs.y;
}

Vector2D Vector2D::operator*(float multiplier) const {
  Vector2D result;
  result.x = x * multiplier;
  result.y = y * multiplier;
  return result;
}

bool Vector2D::operator==(const Vector2D& rhs) const noexcept {
  return x == rhs.x && y == rhs.y;
}