#pragma once

#include "ComponentFlag.h"
#include "Vector2D.h"
#include <vector>

struct PathComponent {
  std::vector<Point> points;
  unsigned int          current;
  int repeatFrom; // TODO: make this a vector for list of repeat from and repeat
                  // time instructions

  PathComponent& operator=(const PathComponent&);
  PathComponent& operator=(PathComponent&&) noexcept;

  static constexpr ComponentFlag FLAG{ ComponentFlag::PATH };
};