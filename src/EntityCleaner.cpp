#include "EntityCleaner.h"

static constexpr auto LOWER_LIMIT_X{ 0 };
static constexpr auto UPPER_LIMIT_X{ 800 };
static constexpr auto LOWER_LIMIT_Y{ 0 };
static constexpr auto UPPER_LIMIT_Y{ 640 };

EntityCleaner::EntityCleaner(EntityManager& em) : _em(em) {}

static inline bool isOutOfBounds(const Vector2D& position) {
  return position.x < LOWER_LIMIT_X || position.x > UPPER_LIMIT_X ||
         position.y < LOWER_LIMIT_Y || position.y > UPPER_LIMIT_Y;
}

void EntityCleaner::removeDeadEntities() {
  int lastEntity = _em.num_entities - 1;
  for (int entity = lastEntity; entity >= 0; entity--) { // remove from back
    if (shouldRemove(entity))
      _em.removeEntity(entity);
  }
}

bool EntityCleaner::shouldRemove(int entity) {
  return isOutOfBounds(entity) || isNoHP(entity);
}

bool EntityCleaner::isOutOfBounds(int entity) {
  const Vector2D& position = _em.transforms[entity].position;
  return position.x < LOWER_LIMIT_X || position.x > UPPER_LIMIT_X ||
         position.y < LOWER_LIMIT_Y || position.y > UPPER_LIMIT_Y;
}

bool EntityCleaner::isNoHP(int entity) {
  const EntitySettings& settings = _em.settings[entity];
  return settings.hasComponents(ComponentFlag::COLLIDER) &&
         _em.colliders[entity].health <= 0;
}