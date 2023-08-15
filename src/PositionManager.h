#pragma once

#include "EntityManager.h"

class PositionManager {
private:
  EntityManager& _em;

public:
  PositionManager(EntityManager&);
  void updatePositions();

private:
  void updatePosition(TransformComponent&);
};