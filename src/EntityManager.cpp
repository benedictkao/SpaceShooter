#include "EntityManager.h"
#include "Math.h"
#include <iostream>	// TODO: remove after testing

static constexpr int PLAYER_SPEED{ 7 };

int EntityManager::addPlayer(int x, int y) {
	int entityId = _num_entities++;

	// TODO: put this in a separate fun
	SpriteComponent& sprite = _sprites[entityId];
	sprite.entity = entityId;
	sprite.texture = SDL2::loadTexture("../../../res/spaceship.png", _renderer);

	// TODO: put this in a separate fun
	TransformComponent& transform = _transforms[entityId];
	transform.entity = entityId;
	transform.position.x = x;
	transform.position.y = y;
	transform.speed.x = 0;
	transform.speed.y = 0;
	transform.height = 32;
	transform.width = 32;

	return entityId;
}

EntityManager::EntityManager(SDL2::Renderer renderer) : _num_entities(0), _renderer(renderer) {}


void EntityManager::movePlayerUp() {
	// 0 always refers to the player
	_transforms[0].speed.y = -PLAYER_SPEED;
}

void EntityManager::movePlayerDown() {
	// 0 always refers to the player
	_transforms[0].speed.y = PLAYER_SPEED;
}

void EntityManager::movePlayerLeft() {
	// 0 always refers to the player
	_transforms[0].speed.x = -PLAYER_SPEED;
}

void EntityManager::movePlayerRight() {
	// 0 always refers to the player
	_transforms[0].speed.x = PLAYER_SPEED;
}

void EntityManager::stopMovingPlayerUp() {
	int currYSpeed = _transforms[0].speed.y;
	_transforms[0].speed.y = max(currYSpeed, 0);
}

void EntityManager::stopMovingPlayerDown() {
	int currYSpeed = _transforms[0].speed.y;
	_transforms[0].speed.y = min(currYSpeed, 0);
}

void EntityManager::stopMovingPlayerLeft() {
	int currXSpeed = _transforms[0].speed.x;
	_transforms[0].speed.x = max(currXSpeed, 0);
}

void EntityManager::stopMovingPlayerRight() {
	int currXSpeed = _transforms[0].speed.x;
	_transforms[0].speed.x = min(currXSpeed, 0);
}

void EntityManager::updateAllPositions() {
	for (int i = 0; i < _num_entities; i++)
		updatePosition(_transforms[i]);
}

void EntityManager::updateAllTextures() {
	for (int i = 0; i < _num_entities; i++)
		updateTexture(_sprites[i]);
}

void EntityManager::updatePosition(TransformComponent& transform) {
	transform.position.x += transform.speed.x;
	transform.position.y += transform.speed.y;
}

void EntityManager::updateTexture(const SpriteComponent& sprite) {
	const TransformComponent& transform = _transforms[sprite.entity];
	SDL2::blit(sprite.texture, _renderer, transform.position.x, transform.position.y, transform.width, transform.height);
}
