#include "Vector2D.h"

Vector2D Vector2D::operator*(int multiplier) const {
  Vector2D result;
  result.x = x * multiplier;
  result.y = y * multiplier;
  return result;
}