#pragma once

#include "ComponentFlag.h"
#include "Vector2D.h"

enum EnemyType {
	BASIC, BOSS
};

struct SpawnComponent {
  int                 currCoolDown;
  int                 coolDown;
  int                 spawnCount;
  EnemyType           type;

  static constexpr ComponentFlag FLAG{ ComponentFlag::SPAWN };
};