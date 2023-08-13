#pragma once

#include <array>
#include "SDLWrapper.h"
#include "component/Components.h"

constexpr int MAX_ENTITIES{ 5 };

class EntityManager {
private:
	int _num_entities;
	SDL2::Renderer _renderer;
	std::array<SpriteComponent, MAX_ENTITIES> _sprites;
	std::array<TransformComponent, MAX_ENTITIES> _transforms;

public:
	EntityManager(SDL2::Renderer);

	int addPlayer(int, int);

	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();

	void stopMovingPlayerUp();
	void stopMovingPlayerDown();
	void stopMovingPlayerLeft();
	void stopMovingPlayerRight();

	void updateAllPositions();
	void updateAllTextures();

private:
	void updatePosition(TransformComponent&);
	void updateTexture(const SpriteComponent&);
};