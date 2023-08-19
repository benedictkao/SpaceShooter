#pragma once

#include "EntityManager.h"

class PositionSystem {
private:
  EntityManager& _em;

public:
  PositionSystem(EntityManager&);
  void updatePositions();

private:
  void updatePosition(TransformComponent&);
};