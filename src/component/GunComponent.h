#pragma once
#include "ComponentFlag.h"
#include "TextureId.h"
#include "Vector2D.h"

struct Ammo {
  unsigned int assetId;
  int          coolDown;
  int          speed;
  int          width;
  int          height;
};

struct GunComponent {
  Ammo     ammo;
  Vector2D direction;
  int      coolDown;
  bool     isFiring;

  static constexpr ComponentFlag FLAG{ ComponentFlag::GUN };
};

namespace AmmoTypes {
  constexpr Ammo PLAYER_DEFAULT = { TextureId::BLUE_BULLET, 12, 12, 8, 8 };

  constexpr Ammo ENEMY_DEFAULT = { TextureId::RED_BULLET, 60, 12, 8, 8 };
} // namespace AmmoTypes