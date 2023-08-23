#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"

class ColliderSystem {
private:
  EntityManager& _em;
  TextureRepo&   _texRepo;

public:
  ColliderSystem(EntityManager&, TextureRepo&);
  void calculateCollisions();

private:
  struct ColliderPair {
    int                entity;
    ColliderComponent* collider;
  };

  void handleDeadEntity(const ColliderPair&, TransformComponent&);
};