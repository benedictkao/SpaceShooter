#include "EntityCleaner.h"

#include <vector>

static constexpr auto LOWER_LIMIT_X{ 0 };
static constexpr auto UPPER_LIMIT_X{ 800 };
static constexpr auto LOWER_LIMIT_Y{ 0 };
static constexpr auto UPPER_LIMIT_Y{ 640 };

EntityCleaner::EntityCleaner(EntityManager& em) : _em(em) {}

static bool isOutOfBounds(int entity, EntityManager& em) {
  const Vector2D& position =
    em.getComponent<TransformComponent>(entity).position;
  return position.x < LOWER_LIMIT_X || position.x > UPPER_LIMIT_X ||
         position.y < LOWER_LIMIT_Y || position.y > UPPER_LIMIT_Y;
}

static bool isNoHP(int entity, EntityManager& em) {
  const EntitySettings& settings = em.getComponent<EntitySettings>(entity);
  return settings.hasComponents(ComponentFlag::COLLIDER) &&
         em.getComponent<ColliderComponent>(entity).health <= 0;
}

static bool shouldRemove(int entity, EntityManager& em) {
  return isOutOfBounds(entity, em) || isNoHP(entity, em);
}

void EntityCleaner::removeDeadEntities() {
  _em.removeByCondition(shouldRemove);
}