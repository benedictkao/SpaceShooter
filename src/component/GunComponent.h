#pragma once
#include "ComponentFlag.h"
#include "ResId.h"
#include "Vector2D.h"

struct Ammo {
  unsigned int assetId;
  int          soundId;
  int          coolDown;
  int          speed;
  int          width;
  int          height;
  int          damage;
};

struct GunComponent {
  Ammo     ammo;
  Vector2D direction;
  int      coolDown;
  bool     isFiring;

  static constexpr ComponentFlag FLAG{ ComponentFlag::GUN };
};

namespace AmmoTypes {
  constexpr Ammo PLAYER_DEFAULT = { TextureId::BLUE_BULLET, SoundId::SMALL_SHOT, 12, 12, 10, 14, 1 };

  constexpr Ammo ENEMY_BOSS = { TextureId::FIREBALL, SoundId::FIREBALL, 50, 8, 20, 40, 3 };
} // namespace AmmoTypes