#pragma once
#include "ComponentFlag.h"
#include "TextureParams.h"
#include "Vector2D.h"

struct Ammo {
  TextureParams asset;
  int           coolDown;
  int           speed;
  int           width;
  int           height;

  static const Ammo Normal;
};

struct GunComponent {
  Ammo     ammo;
  Vector2D direction;
  int      coolDown;
  bool     isFiring;

  static constexpr ComponentFlag FLAG{ ComponentFlag::GUN };
};