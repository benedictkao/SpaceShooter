#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"

class KeyboardManager {
private:
	EntityManager& _em;

public:
	KeyboardManager(EntityManager&);

	void handleKeydownEvent(const SDL2::Event&);

	void handleKeyupEvent(const SDL2::Event&);
};