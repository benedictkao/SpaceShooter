#pragma once

#include "EntityManager.h"
#include "TextureManager.h"

class GunManager {
private:
  EntityManager&  _em;
  TextureManager& _tm;

public:
  GunManager(EntityManager&, TextureManager&);
  void shootProjectiles();

private:
  void createProjectile(const GunComponent&, const TransformComponent& parent);
};