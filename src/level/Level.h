#pragma once

#include "SpawnComponent.h"
#include "Vector2D.h"
#include <queue>

struct SingleSpawnSettings {
  int startingCooldown;
  int coolDown;
  int spawnCount;
  int x;
};

struct Spawner {
  std::vector<SingleSpawnSettings> settings;
  SpawnDetails                     details;
};

struct Phase {
  std::vector<Spawner> spawners;
};

struct Level {
  std::vector<Phase> phases;
  unsigned int       currentPhase;
};