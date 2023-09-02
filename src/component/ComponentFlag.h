#pragma once

constexpr unsigned int ONE{ 1 };

enum ComponentFlag : unsigned int {
  TRANSFORM = ONE << 0,
  SPRITE    = ONE << 1,
  GUN       = ONE << 2,
  COLLIDER  = ONE << 3,
  ANIMATION = ONE << 4,
  SPEED     = ONE << 5,
  SPAWN     = ONE << 6,
  TEXT      = ONE << 7,
  PATH      = ONE << 8,
  ENEMY     = ONE << 31
};