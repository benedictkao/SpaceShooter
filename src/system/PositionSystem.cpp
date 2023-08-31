#include "PositionSystem.h"
#include "Constants.h"

PositionSystem::PositionSystem(EntityManager& em) : _em(em) {}

static constexpr bool isOutOfBounds(const TransformComponent& transform) {
  return transform.position.x + transform.width < Constants::X_MIN ||
         transform.position.x > Constants::WINDOW_WIDTH ||
         transform.position.y + transform.height < Constants::Y_MIN ||
         transform.position.y > Constants::WINDOW_HEIGHT;
}

void PositionSystem::updatePositions() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::SPEED)) {
      const SpeedComponent& speed     = _em.getComponent<SpeedComponent>(i);
      TransformComponent&   transform = _em.getComponent<TransformComponent>(i);
      updatePosition(speed, transform);
      if (isOutOfBounds(transform))
        _em.scheduleRemoval(i);
    }
  }
}

void PositionSystem::updatePosition(const SpeedComponent& speed,
                                    TransformComponent&   transform) {
  transform.position.x += speed.x;
  transform.position.y += speed.y;
}