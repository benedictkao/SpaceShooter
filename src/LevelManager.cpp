#include "LevelManager.h"
#include "Constants.h"

static constexpr auto LOSS_DELAY_FRAMES{ 20 };

LevelManager::LevelManager(EntityManager&    em,
                           PlayerController& pControl,
                           TextureRepo&      texRepo,
                           TextRenderer&     textRenderer)
    : _pControl(pControl)
    , _texRepo(texRepo)
    , _textRenderer(textRenderer)
    , _enemyManager(em, texRepo)
    , _currentStatus(GameStatus::NONE)
    , _lossCountdown(0) {}

void LevelManager::initLevel() {
  // pre-load common textures
  _texRepo.clearCache();
  _texRepo.loadTexture(TextureId::RED_BULLET);
  _texRepo.loadTexture(TextureId::GREEN_SHIP);
  _texRepo.loadTexture(TextureId::BLUE_BULLET);
  _texRepo.loadTexture(TextureId::ENEMY_SHIP);
  _texRepo.loadTexture(TextureId::EXPLOSION);

  _textRenderer.clearCenterText();
  _pControl.addPlayer(384, 500);
  _enemyManager.addSimpleEnemy();
  _currentStatus = GameStatus::ONGOING;
}

void LevelManager::clearLevel() {
  // kill current player and remove all enemies
}

GameStatus LevelManager::updateStatus() {
  switch (_currentStatus) {
    case GameStatus::NONE:
      _textRenderer.showCenterText(Constants::GAME_NAME,
                                   "Press space to start");
      break;
    case GameStatus::ONGOING:
      _pControl.keepWithinWindow();
      if (_pControl.checkPlayerDead()) {
        _lossCountdown = LOSS_DELAY_FRAMES;
        _currentStatus = GameStatus::LOSE;
      }
      break;
    case GameStatus::LOSE:
      if (_lossCountdown == 0)
        _textRenderer.showCenterText("Game Over", nullptr);
      else
        --_lossCountdown;
      break;
    case GameStatus::WIN:
      _textRenderer.showCenterText("You Win!", nullptr);
      break;
  }
  return _currentStatus;
}

GameStatus LevelManager::getStatus() const {
  return _currentStatus;
}
