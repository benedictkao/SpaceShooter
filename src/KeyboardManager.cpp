#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(PlayerController& controller,
                                 LevelManager&     lvlManager,
                                 MusicManager&     musicManager)
    : _controller(controller)
    , _lvlManager(lvlManager)
    , _musicManager(musicManager) {}

void KeyboardManager::handleKeydownEvent(const SDL2::Event& event) {
  auto status = _lvlManager.getStatus();
  switch (status) {
    case GameStatus::WIN:
    case GameStatus::LOSE:
    case GameStatus::LOAD:
      handleLoadScreenKeydownEvent(event);
      break;
    case GameStatus::ONGOING:
      handleInGameKeydownEvent(event);
      break;
    case GameStatus::PAUSE:
      handlePauseKeydownEvent(event);
      break;
  }
}

void KeyboardManager::handleKeyupEvent(const SDL2::Event& event) {
  if (_lvlManager.getStatus() != GameStatus::ONGOING)
    return;

  switch (event.key.keysym.sym) {
    case SDLK_UP:
      _controller.stopMovingPlayerUp();
      break;
    case SDLK_DOWN:
      _controller.stopMovingPlayerDown();
      break;
    case SDLK_LEFT:
      _controller.stopMovingPlayerLeft();
      break;
    case SDLK_RIGHT:
      _controller.stopMovingPlayerRight();
      break;
    case SDLK_SPACE:
      _controller.stopShootingGun();
      break;
    default:
      break;
  }
}

void KeyboardManager::handleLoadScreenKeydownEvent(const SDL2::Event& event) {
  if (event.key.keysym.sym == SDLK_RETURN) {
    _musicManager.stopPlayingMusic();
    _musicManager.stopSounds();
    _musicManager.playSound(SoundId::START);
    _lvlManager.initLevel();
  }
}

void KeyboardManager::handleInGameKeydownEvent(const SDL2::Event& event) {
  switch (event.key.keysym.sym) {
    case SDLK_UP:
      _controller.movePlayerUp();
      break;
    case SDLK_DOWN:
      _controller.movePlayerDown();
      break;
    case SDLK_LEFT:
      _controller.movePlayerLeft();
      break;
    case SDLK_RIGHT:
      _controller.movePlayerRight();
      break;
    case SDLK_SPACE:
      _controller.shootGun();
      break;
    case SDLK_ESCAPE:
      _controller.stopMovingPlayer();
      _lvlManager.pause();
      break;
    default:
      break;
  }
}

void KeyboardManager::handlePauseKeydownEvent(const SDL2::Event& event) {
  switch (event.key.keysym.sym) {
    case SDLK_UP:
      _lvlManager.scrollOptionUp();
      break;
    case SDLK_DOWN:
      _lvlManager.scrollOptionDown();
      break;
    case SDLK_RETURN:
      _lvlManager.selectOption();
      break;
  }
}
