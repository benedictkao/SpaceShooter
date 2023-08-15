#pragma once

enum ComponentFlag {
  TRANSFORM = 1 << 0,
  SPRITE    = 1 << 1,
  GUN       = 1 << 2,
  COLLIDER  = 1 << 3
};