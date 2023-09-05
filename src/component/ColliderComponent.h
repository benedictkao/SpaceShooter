#pragma once
#include "ComponentFlag.h"

struct ColliderComponent {
  int          health;
  int          damage;
  unsigned int deathAnim;
  unsigned int scorePoints;

  static constexpr ComponentFlag FLAG{ ComponentFlag::COLLIDER };
};