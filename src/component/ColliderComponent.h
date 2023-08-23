#pragma once
#include "ComponentFlag.h"

namespace Mass {
  constexpr int INFINITE{ -1 };
}

struct ColliderComponent {
  int          health;
  int          damage;
  unsigned int deathAnim;

  static constexpr ComponentFlag FLAG{ ComponentFlag::COLLIDER };
};