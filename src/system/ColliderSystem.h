#pragma once

#include "EntityManager.h"

class ColliderSystem {
private:
  EntityManager& _em;

public:
  ColliderSystem(EntityManager&);
  void calculateCollisions();
};