#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(PlayerController& controller,
                                 LevelManager&     lvlManager)
    : _controller(controller), _lvlManager(lvlManager) {}

void KeyboardManager::handleKeydownEvent(const SDL2::Event& event) {
  auto status = _lvlManager.getStatus();
  switch (status) {
    case GameStatus::WIN:
    case GameStatus::LOSE:
    case GameStatus::NONE:
      handleLoadScreenKeydownEvent(event);
      break;
    case GameStatus::ONGOING:
      handleInGameKeydownEvent(event);
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
  if (event.key.keysym.sym == SDLK_RETURN)
    _lvlManager.initLevel();
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
    default:
      break;
  }
}
