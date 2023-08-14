#pragma once
#include "EntityManager.h"

class EntityCleaner {
private:
  EntityManager &_em;

public:
  EntityCleaner(EntityManager &);
  void removeDeadEntities();

private:
  static bool isOutOfBounds(const Vector2D &position);
};