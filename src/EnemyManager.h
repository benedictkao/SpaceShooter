#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"
#include "Vector2D.h"
#include <unordered_set>

class EnemyManager {
private:
  typedef std::unordered_set<unsigned int> EntitySet;

  EntityManager& _em;
  TextureRepo&   _texRepo;
  EntitySet      _activeEnemies;

public:
  EnemyManager(EntityManager&, TextureRepo&);
  void updateSpawner(int spawnerId);
  void updateActiveEnemies();
  bool allEnemiesDead() const;
  void reset();

private:
  void spawnBasic(const Point&);
  void spawnBoss(const Point&);
};