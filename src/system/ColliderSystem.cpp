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
  return { transform.position.x,
           transform.position.y,
           transform.width,
           transform.height };
}

static inline void collide(ColliderComponent* a, ColliderComponent* b) {
  a->health -= b->damage == Mass::INFINITE ? a->health : b->damage;
  b->health -= a->damage == Mass::INFINITE ? b->health : a->damage;
  std::cout << "Collide" << std::endl;
}

void ColliderSystem::calculateCollisions() {
  std::vector<ColliderPair> allies;
  std::vector<ColliderPair> enemies;

  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    bool hasCollider = _em.hasComponents(i, ComponentFlag::COLLIDER);
    if (hasCollider) {
      ColliderComponent* collider = &_em.getComponent<ColliderComponent>(i);
      if (_em.hasComponents(i, ComponentFlag::ENEMY))
        enemies.push_back({ i, collider });
      else
        allies.push_back({ i, collider });
    }
  }

  for (auto& ally : allies) {
    const TransformComponent& allyTransform =
      _em.getComponent<TransformComponent>(ally.entity);
    const SDL2::Rect allyRect = toRect(allyTransform);
    for (auto& enemy : enemies) {
      const TransformComponent& enemyTransform =
        _em.getComponent<TransformComponent>(enemy.entity);
      const SDL2::Rect enemyRect = toRect(enemyTransform);
      if (SDL2::hasIntersect(allyRect, enemyRect)) {
        collide(ally.collider, enemy.collider);
        if (ally.collider->health <= 0)
          _em.scheduleRemoval(ally.entity);
        if (enemy.collider->health <= 0)
          _em.scheduleRemoval(enemy.entity);
      }
    }
  }
}