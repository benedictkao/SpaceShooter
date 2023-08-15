#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"

class GunManager {
private:
  EntityManager& _em;
  SDL2::Renderer _renderer;

public:
  GunManager(EntityManager&, SDL2::Renderer);
  void shootProjectiles();

private:
  void createProjectile(const GunComponent&, const TransformComponent& parent);
};