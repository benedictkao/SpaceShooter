#include "PathComponent.h"
#include <utility>

PathComponent& PathComponent::operator=(const PathComponent& rhs) {
  points     = rhs.points;
  current    = rhs.current;
  repeatFrom = rhs.repeatFrom;
  return *this;
}

PathComponent& PathComponent::operator=(PathComponent&& rhs) noexcept {
  points     = std::move(rhs.points);
  current    = rhs.current;
  repeatFrom = rhs.repeatFrom;
  return *this;
}