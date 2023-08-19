#include "SystemManager.h"

SystemManager::SystemManager(EntityManager& em, TextureRepo& texRepo)
    : _em(em)
    , _textureSystem(em)
    , _positionSystem(em)
    , _colliderSystem(em)
    , _gunSystem(em, texRepo) {}

void SystemManager::setRenderer(SDL2::Renderer renderer) {
  _textureSystem.setRenderer(renderer);
}

void SystemManager::init() {}

void SystemManager::update() {
  _positionSystem.updatePositions();
  _colliderSystem.calculateCollisions();
  _gunSystem.spawnProjectiles();
  _textureSystem.updateTextures();
  _em.removeDeadEntities();
}