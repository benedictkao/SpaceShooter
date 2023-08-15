#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"

class PlayerController {
private:
  EntityManager& _em;
  SDL2::Renderer _renderer;
  int            _playerId;

public:
  PlayerController(EntityManager&, SDL2::Renderer);

  void addPlayer(int x, int y);

  void movePlayerUp();
  void movePlayerDown();
  void movePlayerLeft();
  void movePlayerRight();

  void stopMovingPlayerUp();
  void stopMovingPlayerDown();
  void stopMovingPlayerLeft();
  void stopMovingPlayerRight();

  void shootGun();
  void stopShootingGun();

private:
  void initPlayerSprite();
  void initPlayerTransform(int x, int y);
  void initPlayerGun();
};