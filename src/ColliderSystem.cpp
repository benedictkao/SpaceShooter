#include "ColliderSystem.h"
#include "SDLWrapper.h"
#include <iostream>
#include <vector>

ColliderSystem::ColliderSystem(EntityManager& em) : _em(em) {}

struct ColliderPair {
  int                entity;
  ColliderComponent* collider;
};

static inline SDL2::Rect toRect(const TransformComponent& transform) {
  SDL2::Rect rect;
  rect.x = transform.position.x;
  rect.y = transform.position.y;
  rect.w = transform.width;
  rect.h = transform.height;
  return rect;
}

static inline void collide(ColliderComponent* a, ColliderComponent* b) {
  a->health -= b->mass == Mass::INFINITE ? a->health : b->mass;
  b->health -= a->mass == Mass::INFINITE ? b->health : a->mass;
}

void ColliderSystem::calculateCollisions() {
  std::vector<ColliderPair> allies;
  std::vector<ColliderPair> enemies;

  for (int i = 0; i < _em.num_entities; i++) {
    bool result = _em.settings[i].hasComponents(ComponentFlag::COLLIDER);
    if (_em.settings[i].hasComponents(ComponentFlag::COLLIDER)) {
      ColliderComponent* collider = &_em.colliders[i];
      if (collider->isEnemy)
        enemies.push_back({ i, collider });
      else
        allies.push_back({ i, collider });
    }
  }

  for (auto& ally : allies) {
    const TransformComponent& allyTransform = _em.transforms[ally.entity];
    const SDL2::Rect          allyRect      = toRect(allyTransform);
    for (auto& enemy : enemies) {
      const TransformComponent& enemyTransform = _em.transforms[enemy.entity];
      const SDL2::Rect          enemyRect      = toRect(enemyTransform);
      if (SDL2::hasIntersect(allyRect, enemyRect))
        collide(ally.collider, enemy.collider);
    }
  }
}