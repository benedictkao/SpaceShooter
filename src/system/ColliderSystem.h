#pragma once

#include "EntityManager.h"
#include "MusicManager.h"
#include "TextureRepo.h"

class ColliderSystem {
private:
  EntityManager& _em;
  TextureRepo&   _texRepo;
  MusicManager&  _musicManager;

public:
  ColliderSystem(EntityManager&, TextureRepo&, MusicManager&);
  void calculateCollisions();

private:
  struct ColliderPair {
    int                entity;
    ColliderComponent* collider;
  };

  void handleDeadEntity(const ColliderPair&, TransformComponent&);
};