#pragma once
#include "Vector2D.h"

struct Ammo {
  const char* asset;
  int         coolDown;
  int         speed;
  int         width;
  int         height;

  static const Ammo Normal;
};

struct GunComponent {
  Ammo     ammo;
  Vector2D direction;
  int      coolDown;
  bool     isFiring;
};