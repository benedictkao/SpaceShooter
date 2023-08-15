#include "PositionManager.h"

PositionManager::PositionManager(EntityManager& em) : _em(em) {}

void PositionManager::updatePositions() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities)
    updatePosition(_em.getComponent<TransformComponent>(i));
}

void PositionManager::updatePosition(TransformComponent& transform) {
  transform.position.x += transform.speed.x;
  transform.position.y += transform.speed.y;
}