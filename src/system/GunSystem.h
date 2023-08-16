#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"

class GunSystem {
private:
  EntityManager& _em;
  TextureRepo&   _textureRepo;

public:
  GunSystem(EntityManager&, TextureRepo&);
  void spawnProjectiles();

private:
  void createProjectile(const GunComponent&, const TransformComponent& parent);
};