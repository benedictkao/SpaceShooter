#include "LevelManager.h"
#include "Constants.h"

static constexpr auto LOSS_DELAY_FRAMES{ 20 };

LevelManager::LevelManager(EntityManager&    em,
                           PlayerController& pControl,
                           TextureRepo&      texRepo,
                           TextRenderer&     textRenderer)
    : _em(em)
    , _pControl(pControl)
    , _texRepo(texRepo)
    , _textRenderer(textRenderer)
    , _enemyManager(em, texRepo)
    , _currentStatus(GameStatus::NONE)
    , _lossCountdown(0) {

  // TODO: optimize this!
  Phase   phase1;

  Spawner spawner1;
  spawner1.settings.push_back({ 40, 80, 4, 200 });
  spawner1.details = { TextureId::BASIC_ENEMY, 48, 48, 1, { 0, 4 } };
  Spawner spawner2;
  spawner2.settings.push_back({ 40, 80, 4, 400 });
  spawner2.details = { TextureId::BASIC_ENEMY, 48, 48, 1, { 0, 4 } };

  phase1.spawners.push_back(spawner1);
  phase1.spawners.push_back(spawner2);
  _currentLevel.phases.push_back(phase1);
}

void LevelManager::initLevel() {
  reset();

  // pre-load common textures
  _texRepo.loadTexture(TextureId::RED_BULLET);
  _texRepo.loadTexture(TextureId::GREEN_SHIP);
  _texRepo.loadTexture(TextureId::BLUE_BULLET);
  _texRepo.loadTexture(TextureId::BASIC_ENEMY);
  _texRepo.loadTexture(TextureId::EXPLOSION);

  _pControl.addPlayer(384, 500);
  _currentLevel.currentPhase = -1;
  initNextPhase();
  _currentStatus = GameStatus::ONGOING;
}

void LevelManager::reset() {
  _textRenderer.clearCenterText();
  _pControl.reset();
  _em.reset();
  _texRepo.clearCache();
}

GameStatus LevelManager::updateStatus() {
  switch (_currentStatus) {
    case GameStatus::NONE:
      _textRenderer.showCenterText(Constants::GAME_NAME,
                                   "Press space to start");
      break;
    case GameStatus::ONGOING:
      if (_pControl.checkPlayerDead())
        setLoseStatus();
      else
        updateLevel();
      break;
    case GameStatus::LOSE:
      if (_lossCountdown == 0)
        _textRenderer.showCenterText("Game Over", "Press space to play again");
      else
        --_lossCountdown;
      break;
    case GameStatus::WIN:
      _textRenderer.showCenterText("You Win!", "Press space to play again");
      break;
  }
  return _currentStatus;
}

GameStatus LevelManager::getStatus() const {
  return _currentStatus;
}

void LevelManager::setLoseStatus() {
  _lossCountdown = LOSS_DELAY_FRAMES;
  _currentStatus = GameStatus::LOSE;
}

void LevelManager::updateLevel() {
  bool phaseComplete = true;

  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::SPAWN)) {
      phaseComplete = false;
      _enemyManager.spawnEnemy(i);
    }
  }
  _enemyManager.updateActiveEnemies();

  if (phaseComplete) {
    if (_currentLevel.currentPhase < _currentLevel.phases.size() - 1) {
      initNextPhase();
    } else if (_enemyManager.allEnemiesDead()) {
      _currentStatus = GameStatus::WIN;
      _pControl.stopMovingPlayer();
      _pControl.stopShootingGun();
    }
  }
}

void LevelManager::initNextPhase() {
  const auto& spawners =
    _currentLevel.phases[++_currentLevel.currentPhase].spawners;

  for (const auto& spawner : spawners) {
    for (const auto& setting : spawner.settings) {
      SpawnComponent spawnComponent;
      spawnComponent.currCoolDown = setting.startingCooldown;
      spawnComponent.coolDown     = setting.coolDown;
      spawnComponent.spawnCount   = setting.spawnCount;
      spawnComponent.details      = &spawner.details;
      TransformComponent t;
      t.position = { setting.x, 0 };
      t.height   = 0;
      t.width    = 0;
      _em.addEntity()
        .add<SpawnComponent>(spawnComponent)
        .add<TransformComponent>(t);
    }
  }
}
