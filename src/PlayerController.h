#pragma once

#include "EntityManager.h"
#include "TextureManager.h"

class PlayerController {
private:
  EntityManager& _em;
  TextureManager& _tm;
  int            _playerId;

public:
  PlayerController(EntityManager&, TextureManager&);

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
  SpriteComponent createSprite() const;
  static TransformComponent createTransform(int x, int y);
  static GunComponent createGun();
  static ColliderComponent  createCollider();
};