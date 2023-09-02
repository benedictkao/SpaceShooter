#pragma once

#include "EntityManager.h"

class PositionSystem {
private:
  EntityManager& _em;

public:
  PositionSystem(EntityManager&);
  void updatePositions();

private:
  void     updatePath(int entity, SpeedComponent&, const TransformComponent&);
  void     updatePosition(const SpeedComponent&, TransformComponent&);
  Vector2D calculateDirection(const Point& current, const Point& target);
};