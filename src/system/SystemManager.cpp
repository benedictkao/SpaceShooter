#include "SystemManager.h"
#include "Constants.h"

SystemManager::SystemManager(EntityManager&    em,
                             TextureRepo&      texRepo,
                             PlayerController& pControl,
                             TextRenderer&     textRenderer,
                             LevelManager&     levelManager,
                             MusicManager&     musicManager)
    : _em(em)
    , _textureSystem(em)
    , _positionSystem(em)
    , _colliderSystem(em, texRepo, musicManager, levelManager)
    , _gunSystem(em, texRepo, musicManager)
    , _pControl(pControl)
    , _levelManager(levelManager)
    , _musicManager(musicManager)
    , _bgManager(texRepo) {}

void SystemManager::init(SDL2::Renderer renderer) {
  _textureSystem.setRenderer(renderer);
  _bgManager.setRenderer(renderer);
  _musicManager.init();
  _musicManager.playMusic(MusicId::LOAD);
}

void SystemManager::update() {
  _bgManager.updateBackground();

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