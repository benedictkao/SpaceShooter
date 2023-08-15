#pragma once
#include "EntityManager.h"

class EntityCleaner {
private:
  EntityManager& _em;

public:
  EntityCleaner(EntityManager&);
  void removeDeadEntities();

private:
  bool shouldRemove(int entity);
  bool isOutOfBounds(int entity);
  bool isNoHP(int entity);
};