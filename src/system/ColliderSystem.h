#pragma once

#include "EntityManager.h"
#include "LevelManager.h"
#include "MusicManager.h"
#include "TextureRepo.h"

class ColliderSystem {
private:
  EntityManager& _em;
  TextureRepo&   _texRepo;
  MusicManager&  _musicManager;
  LevelManager&  _lvlManager;

public:
  ColliderSystem(EntityManager&, TextureRepo&, MusicManager&, LevelManager&);
  void calculateCollisions();

private:
  struct ColliderPair {
    int                entity;
    ColliderComponent* collider;
  };

  void handleDeadEntity(const ColliderPair&, TransformComponent&);
};