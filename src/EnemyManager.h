#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"
#include <unordered_set>

class EnemyManager {
private:
  typedef std::unordered_set<unsigned int> EntitySet;

  EntityManager& _em;
  TextureRepo&   _texRepo;
  EntitySet      _activeEnemies;

public:
  EnemyManager(EntityManager&, TextureRepo&);
  void addSimpleEnemy();
  void spawnEnemy(int spawnerId);
  void updateActiveEnemies();
  bool allEnemiesDead() const;
};