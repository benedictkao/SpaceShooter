#pragma once

enum ComponentFlag : unsigned int {
  TRANSFORM = 1 << 0,
  SPRITE    = 1 << 1,
  GUN       = 1 << 2,
  COLLIDER  = 1 << 3,
  ANIMATION = 1 << 4,
  ENEMY     = static_cast<unsigned int>(1) << 31
};