#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(PlayerController &controller)
    : _controller(controller) {}

void KeyboardManager::handleKeydownEvent(const SDL2::Event &event) {
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
  default:
    break;
  }
}

void KeyboardManager::handleKeyupEvent(const SDL2::Event &event) {
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
  default:
    break;
  }
}