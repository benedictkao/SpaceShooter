#include "EntityCleaner.h"

static constexpr auto LOWER_LIMIT_X{0};
static constexpr auto UPPER_LIMIT_X{800};
static constexpr auto LOWER_LIMIT_Y{0};
static constexpr auto UPPER_LIMIT_Y{640};

EntityCleaner::EntityCleaner(EntityManager &em) : _em(em) {}

void EntityCleaner::removeDeadEntities() {
  int n = _em.num_entities;
  for (int i = n - 1; i >= 0; i--) { // remove from back
    const TransformComponent &transform = _em.transforms[i];
    if (isOutOfBounds(transform.position))
      _em.removeEntity(i);
  }
}

bool EntityCleaner::isOutOfBounds(const Vector2D &position) {
  return position.x < LOWER_LIMIT_X || position.x > UPPER_LIMIT_X ||
         position.y < LOWER_LIMIT_Y || position.y > UPPER_LIMIT_Y;
}