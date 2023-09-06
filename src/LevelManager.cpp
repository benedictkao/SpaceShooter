#include "LevelManager.h"
#include "Constants.h"
#include "utils/Math.h"
#include <iostream>

static constexpr auto RESULT_DELAY_FRAMES{ 20 };

static constexpr auto WIN_TITLE{ "You Win!" };
static constexpr auto GAME_OVER{ "Game Over" };
static constexpr auto START_SUBTITLE{ "Press enter to start" };
static constexpr auto PLAY_AGAIN{ "Press enter to play again" };

LevelManager::LevelManager(EntityManager&    em,
                           PlayerController& pControl,
                           TextureRepo&      texRepo,
                           TextRenderer&     textRenderer,
                           MusicManager&     musicManager)
    : _em(em)
    , _pControl(pControl)
    , _texRepo(texRepo)
    , _textRenderer(textRenderer)
    , _musicManager(musicManager)
    , _enemyManager(em, texRepo)
    , _currentStatus(GameStatus::LOAD)
    , _countdown(0)
    , _currentScore(0)
    , _newScore(0)
    , _selectedOption(0) {

  // TODO: optimize this!
  Phase phase;
  phase.musicId = MusicId::NONE;

  Spawner spawner;
  spawner.settings.push_back({ 80, 60, 3, 100 });
  spawner.settings.push_back({ 80, 60, 3, 200 });
  spawner.settings.push_back({ 80, 60, 3, 300 });
  spawner.settings.push_back({ 80, 60, 3, 400 });
  spawner.settings.push_back({ 80, 60, 3, 500 });
  spawner.settings.push_back({ 80, 60, 3, 600 });
  spawner.settings.push_back({ 80, 60, 3, 700 });
  spawner.type = EnemyType::BASIC;
  phase.spawners.push_back(spawner);
  _currentLevel.phases.push_back(phase);

  auto it  = phase.spawners[0].settings.begin();
  auto end = phase.spawners[0].settings.end();
  while (it != end) {
    // it->startingCooldown += 60;
    it->coolDown = 80;
    ++it;
    if (it != end) {
      it->startingCooldown += 40;
      it->coolDown = 80;
      ++it;
    }
  }
  _currentLevel.phases.push_back(phase);

  phase.spawners.clear();
  spawner.settings.clear();
  spawner.settings.push_back({ 200, 0, 1, 400 });
  spawner.type = EnemyType::BOSS;
  phase.spawners.push_back(spawner);
  phase.musicId = MusicId::BOSS;
  _currentLevel.phases.push_back(phase);
}

void LevelManager::initLevel() {
  std::cout << "+++++\nInit level!" << std::endl;
  reset();

  // pre-load common textures
  _texRepo.loadTexture(TextureId::BOSS_ENEMY);
  _texRepo.loadTexture(TextureId::FIREBALL);
  _texRepo.loadTexture(TextureId::HEART);
  _texRepo.loadTexture(TextureId::GREEN_SHIP);
  _texRepo.loadTexture(TextureId::BLUE_BULLET);
  _texRepo.loadTexture(TextureId::BASIC_ENEMY);
  _texRepo.loadTexture(TextureId::EXPLOSION);

  _pControl.addPlayer(Constants::PLAYER_START_X, Constants::PLAYER_START_Y);
  _textRenderer.showEmptyScore();
  _currentLevel.currentPhase = -1;
  initNextPhase();
  _currentStatus = GameStatus::ONGOING;
}

void LevelManager::pause() {
  std::cout << "Game paused!" << std::endl;
  _textRenderer.clearCenterText();
  _selectedOption = 0;
  _currentStatus  = GameStatus::PAUSE;
}

void LevelManager::resume() {
  std::cout << "Game resumed!" << std::endl;
  _textRenderer.clearCenterText();
  _currentStatus = GameStatus::ONGOING;
}

void LevelManager::scrollOptionUp() {
  coerceAtLeast(--_selectedOption, 0);
}

void LevelManager::scrollOptionDown() {
  coerceAtMost(++_selectedOption, 2);
}


void LevelManager::selectOption() {
  switch (_selectedOption) {
    case 0:
      resume();
      break;
    case 1:
      initLevel();
      break;
    case 2:
      SDL2::quit();
      break;
  }
}

void LevelManager::addScore(unsigned int score) {
  _newScore += score;
}

void LevelManager::reset() {
  _textRenderer.clearAllTexts();
  _pControl.reset();
  _enemyManager.reset();
  _em.reset();
  _texRepo.clear();
  _newScore     = 0;
  _currentScore = 0;
  _countdown    = 0;
}

GameStatus LevelManager::updateStatus() {
  switch (_currentStatus) {
    case GameStatus::LOAD:
      _textRenderer.showCenterText(Constants::GAME_NAME, START_SUBTITLE);
      break;
    case GameStatus::PAUSE:
      _textRenderer.showOptionText("Paused",
                                   { "Resume", "Restart", "Quit" },
                                   _selectedOption);
      break;
    case GameStatus::ONGOING:
      _pControl.updateHpBar();
      if (_pControl.checkPlayerDead())
        setResult(GameStatus::LOSE);
      else
        updateLevel();
      break;
    case GameStatus::LOSE:
      displayResult(GAME_OVER, PLAY_AGAIN, SoundId::FAIL);
      break;
    case GameStatus::WIN:
      displayResult(WIN_TITLE, PLAY_AGAIN, SoundId::VICTORY);
      break;
  }
  return _currentStatus;
}

GameStatus LevelManager::getStatus() const {
  return _currentStatus;
}

void LevelManager::setResult(GameStatus status) {
  std::cout << "Set result: " << status << std::endl;
  _musicManager.stopPlayingMusic();
  _countdown     = RESULT_DELAY_FRAMES;
  _currentStatus = status;
}

void LevelManager::displayResult(const char*  title,
                                 const char*  subtitle,
                                 unsigned int soundId) {
  if (_countdown > 0) {
    --_countdown;
  } else {
    if (_countdown == 0) {
      _musicManager.playSound(soundId);
      --_countdown;
    }
    _textRenderer.showCenterText(title, subtitle);
  }
}

void LevelManager::updateLevel() {
  if (_currentScore != _newScore) {
    _currentScore = _newScore;
    _textRenderer.updateScore(_currentScore);
  }

  bool phaseComplete = true;

  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::SPAWN)) {
      phaseComplete = false;
      _enemyManager.updateSpawner(i);
    }
  }
  _enemyManager.updateActiveEnemies();

  bool enemiesDead = _enemyManager.allEnemiesDead();
  // std::cout << "phaseComplete, enemiesDead: " << phaseComplete << enemiesDead
  // << std::endl;
  if (phaseComplete && enemiesDead) {
    if (_currentLevel.currentPhase < _currentLevel.phases.size() - 1) {
      initNextPhase();
    } else {
      setResult(GameStatus::WIN);
      _pControl.stopMovingPlayer();
      _pControl.stopShootingGun();
    }
  }
}

void LevelManager::initNextPhase() {
  const Phase& newPhase = _currentLevel.phases[++_currentLevel.currentPhase];
  std::cout << "+++++\nInit phase " << _currentLevel.currentPhase << std::endl;

  if (newPhase.musicId == MusicId::NONE) {
    _musicManager.stopPlayingMusic();
  } else {
    _musicManager.playMusic(newPhase.musicId);
  }

  const auto& spawners = newPhase.spawners;

  for (const auto& spawner : spawners) {
    for (const auto& setting : spawner.settings) {
      SpawnComponent spawnComponent;
      spawnComponent.currCoolDown = setting.startingCooldown;
      spawnComponent.coolDown     = setting.coolDown;
      spawnComponent.spawnCount   = setting.spawnCount;
      spawnComponent.type         = spawner.type;
      TransformComponent t;
      t.position.x = setting.x;
      t.position.y = 0;
      t.height     = 0;
      t.width      = 0;
      _em.addEntity()
        .add<SpawnComponent>(spawnComponent)
        .add<TransformComponent>(t);
    }
  }
}
