#pragma once
#include "EntityManager.h"

class EntityCleaner {
private:
  EntityManager& _em;

public:
  EntityCleaner(EntityManager&);
  void removeDeadEntities();
};