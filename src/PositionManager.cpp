#include "PositionManager.h"

PositionManager::PositionManager(EntityManager& em) : _em(em) {}

void PositionManager::updatePositions() {
  for (int i = 0; i < _em.num_entities; i++)
    updatePosition(_em.transforms[i]);
}

void PositionManager::updatePosition(TransformComponent& transform) {
  transform.position.x += transform.speed.x;
  transform.position.y += transform.speed.y;
}