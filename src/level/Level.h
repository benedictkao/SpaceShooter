#pragma once

#include "SpawnComponent.h"
#include "Vector2D.h"

struct SingleSpawnSettings {
  int startingCooldown;
  int coolDown;
  int spawnCount;
  int x;
};

struct Spawner {
  std::vector<SingleSpawnSettings> settings;
  EnemyType                        type;
};

struct Phase {
  std::vector<Spawner> spawners;
  int                  musicId;
  int                  minDuration;
};

struct Level {
  std::vector<Phase> phases;
  int                currentPhase;
};