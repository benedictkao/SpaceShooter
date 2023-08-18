#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"

class EnemyManager {
private:
  EntityManager& _em;
  TextureRepo&   _texRepo;

public:
  EnemyManager(EntityManager&, TextureRepo&);
  void addSimpleEnemy();
};