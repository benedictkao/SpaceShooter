#include "LevelManager.h"
#include "Constants.h"

static constexpr auto RESULT_DELAY_FRAMES{ 20 };

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
    , _countdown(0) {

  // TODO: optimize this!
  Phase phase;

  Spawner spawner;
  spawner.settings.push_back({ 40, 60, 3, 100 });
  spawner.settings.push_back({ 40, 60, 3, 200 });
  spawner.settings.push_back({ 40, 60, 3, 300 });
  spawner.settings.push_back({ 40, 60, 3, 400 });
  spawner.settings.push_back({ 40, 60, 3, 500 });
  spawner.settings.push_back({ 40, 60, 3, 600 });
  spawner.settings.push_back({ 40, 60, 3, 700 });
  spawner.details = { TextureId::BASIC_ENEMY, 42, 42, 1, { 0, 3 } };

  phase.spawners.push_back(spawner);

  _currentLevel.phases.push_back(phase);

  auto it  = phase.spawners[0].settings.begin();
  auto end = phase.spawners[0].settings.end();
  while (it != end) {
    it->startingCooldown += 200;
    it->coolDown = 80;
    ++it;
    if (it != end) {
      it->startingCooldown += 240;
      it->coolDown = 80;
      ++it;
    }
  }
  _currentLevel.phases.push_back(phase);

  phase.spawners.clear();
  spawner.settings.clear();
  spawner.settings.push_back({ 300, 0, 1, 360 });
  spawner.details = { TextureId::BOSS_ENEMY, 80, 80, 20, { 0, 1 } };
  phase.spawners.push_back(spawner);
  _currentLevel.phases.push_back(phase);
}

void LevelManager::initLevel() {
  reset();

  // pre-load common textures
  _texRepo.loadTexture(TextureId::BOSS_ENEMY);
  _texRepo.loadTexture(TextureId::GREEN_SHIP);
  _texRepo.loadTexture(TextureId::YELLOW_BULLET);
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
                                   "Press enter to start");
      break;
    case GameStatus::ONGOING:
      if (_pControl.checkPlayerDead())
        setResult(GameStatus::LOSE);
      else
        updateLevel();
      break;
    case GameStatus::LOSE:
      if (_countdown == 0)
        _textRenderer.showCenterText("Game Over", "Press enter to play again");
      else
        --_countdown;
      break;
    case GameStatus::WIN:
      if (_countdown == 0)
        _textRenderer.showCenterText("You Win!", "Press enter to play again");
      else
        --_countdown;
      break;
  }
  return _currentStatus;
}

GameStatus LevelManager::getStatus() const {
  return _currentStatus;
}

void LevelManager::setResult(GameStatus status) {
  _countdown     = RESULT_DELAY_FRAMES;
  _currentStatus = status;
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
      setResult(GameStatus::WIN);
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
