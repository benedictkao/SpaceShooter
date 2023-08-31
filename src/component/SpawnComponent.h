#pragma once

#include "ComponentFlag.h"
#include "Vector2D.h"

struct SpawnDetails {
  unsigned int texId;
  unsigned int height;
  unsigned int width;
  unsigned int hp;
  Vector2D     speed;
};

struct SpawnComponent {
  int                 currCoolDown;
  int                 coolDown;
  int                 spawnCount;
  const SpawnDetails* details;

  static constexpr ComponentFlag FLAG{ ComponentFlag::SPAWN };
};