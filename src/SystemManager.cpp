#include "SystemManager.h"

SystemManager::SystemManager(EntityManager&    em,
                             TextureRepo&      texRepo,
                             PlayerController& pControl)
    : _em(em)
    , _textureSystem(em)
    , _positionSystem(em)
    , _colliderSystem(em, texRepo)
    , _gunSystem(em, texRepo)
    , _pControl(pControl) {}

void SystemManager::setRenderer(SDL2::Renderer renderer) {
  _textureSystem.setRenderer(renderer);
}

void SystemManager::init() {}

void SystemManager::update() {
  _positionSystem.updatePositions();
  _pControl.keepWithinWindow();
  _colliderSystem.calculateCollisions();
  _gunSystem.spawnProjectiles();
  _textureSystem.updateSprites();
  _textureSystem.updateAnimations();
  _em.removeDeadEntities();
}