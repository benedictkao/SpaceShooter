#include "PositionSystem.h"
#include "Constants.h"
#include "PositionSystem.h"
#include <math.h>

PositionSystem::PositionSystem(EntityManager& em) : _em(em) {}

static constexpr bool isOutOfBounds(const TransformComponent& transform) {
  return transform.position.x < Constants::X_MIN - transform.width / 2 ||
         transform.position.x > Constants::WINDOW_WIDTH + transform.width / 2 ||
         transform.position.y < Constants::Y_MIN - transform.height / 2 ||
         transform.position.y > Constants::WINDOW_HEIGHT + transform.height / 2;
}

void PositionSystem::updatePositions() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::SPEED)) {
      SpeedComponent&     speed     = _em.getComponent<SpeedComponent>(i);
      TransformComponent& transform = _em.getComponent<TransformComponent>(i);

      if (_em.hasComponents(i, ComponentFlag::PATH))
        updatePath(i, speed, transform);

      updatePosition(speed, transform);
      if (isOutOfBounds(transform))
        _em.scheduleRemoval(i);
    }
  }
}

void PositionSystem::updatePath(int                       entity,
                                SpeedComponent&           speed,
                                const TransformComponent& transform) {
  PathComponent& path   = _em.getComponent<PathComponent>(entity);
  const Point&   target = path.points[path.current];
  if (transform.position == target) {
    if (++path.current == path.points.size()) {
      if (path.repeatFrom >= 0) {
        path.current = path.repeatFrom;
        speed.direction =
          calculateDirection(transform.position, path.points[path.current]);
      } else {
        speed.direction = { 0, 0 };
        path.points.clear();
        _em.removeComponents(entity, ComponentFlag::PATH);
      }
    } else {
      speed.direction =
        calculateDirection(transform.position, path.points[path.current]);
    }
  } else {
    speed.direction = calculateDirection(transform.position, target);
  }
}

void PositionSystem::updatePosition(const SpeedComponent& speed,
                                    TransformComponent&   transform) {
  transform.position.x += speed.direction.x * speed.speed;
  transform.position.y += speed.direction.y * speed.speed;
}

Vector2D PositionSystem::calculateDirection(const Point& current,
                                            const Point& target) {
  const Point& displacement = target - current;
  double       distance     = std::sqrt(displacement.x * displacement.x +
                              displacement.y * displacement.y);

  float x = static_cast<float>(displacement.x) / distance;
  float y = static_cast<float>(displacement.y) / distance;
  return { x, y };
}