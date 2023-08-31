#include "SystemManager.h"
#include "Constants.h"

SystemManager::SystemManager(EntityManager&    em,
                             TextureRepo&      texRepo,
                             PlayerController& pControl,
                             TextRenderer&     textRenderer,
                             LevelManager&     levelManager)
    : _em(em)
    , _textureSystem(em)
    , _positionSystem(em)
    , _colliderSystem(em, texRepo)
    , _gunSystem(em, texRepo)
    , _pControl(pControl)
    , _levelManager(levelManager) {}

void SystemManager::init(SDL2::Renderer renderer) {
  _textureSystem.setRenderer(renderer);
}

void SystemManager::update() {
  _positionSystem.updatePositions();
  if (_levelManager.getStatus() == GameStatus::ONGOING)
    _pControl.keepWithinWindow();

  _colliderSystem.calculateCollisions();
  _gunSystem.spawnProjectiles();

  _textureSystem.updateSprites();
  _textureSystem.updateAnimations();

  _levelManager.updateStatus();
  _em.removeDeadEntities();
}