#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(EntityManager& em) : _em(em) {}

void KeyboardManager::handleKeydownEvent(const SDL2::Event& event) {
	switch (event.key.keysym.sym) {
	case SDLK_UP:
		_em.movePlayerUp();
		break;
	case SDLK_DOWN:
		_em.movePlayerDown();
		break;
	case SDLK_LEFT:
		_em.movePlayerLeft();
		break;
	case SDLK_RIGHT:
		_em.movePlayerRight();
		break;
	default:
		break;
	}
}

void KeyboardManager::handleKeyupEvent(const SDL2::Event& event) {
	switch (event.key.keysym.sym) {
	case SDLK_UP:
		_em.stopMovingPlayerUp();
		break;
	case SDLK_DOWN:
		_em.stopMovingPlayerDown();
		break;
	case SDLK_LEFT:
		_em.stopMovingPlayerLeft();
		break;
	case SDLK_RIGHT:
		_em.stopMovingPlayerRight();
		break;
	default:
		break;
	}
}