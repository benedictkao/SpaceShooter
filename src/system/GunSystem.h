#pragma once

#include "EntityManager.h"
#include "MusicManager.h"
#include "TextureRepo.h"

class GunSystem {
private:
  EntityManager& _em;
  TextureRepo&   _textureRepo;
  MusicManager&  _musicManager;

public:
  GunSystem(EntityManager&, TextureRepo&, MusicManager&);
  void spawnProjectiles();

private:
  void createProjectile(const GunComponent&, const TransformComponent& parent, bool isEnemy);
};