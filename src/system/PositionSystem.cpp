#include "PositionSystem.h"

static constexpr auto LOWER_LIMIT_X{ 0 };
static constexpr auto UPPER_LIMIT_X{ 800 };
static constexpr auto LOWER_LIMIT_Y{ 0 };
static constexpr auto UPPER_LIMIT_Y{ 640 };

PositionSystem::PositionSystem(EntityManager& em) : _em(em) {}

static bool isOutOfBounds(Vector2D& position) {
  return position.x < LOWER_LIMIT_X || position.x > UPPER_LIMIT_X ||
         position.y < LOWER_LIMIT_Y || position.y > UPPER_LIMIT_Y;
}

void PositionSystem::updatePositions() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    TransformComponent& transform = _em.getComponent<TransformComponent>(i);
    updatePosition(_em.getComponent<TransformComponent>(i));
    if (isOutOfBounds(transform.position))
      _em.scheduleRemoval(i);
  }
}

void PositionSystem::updatePosition(TransformComponent& transform) {
  transform.position.x += transform.speed.x;
  transform.position.y += transform.speed.y;
}