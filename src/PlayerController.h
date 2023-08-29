#pragma once

#include "../EntityManager.h"
#include "TextureRepo.h"

class PlayerController {
private:
  EntityManager& _em;
  TextureRepo&   _textureRepo;
  int            _playerId;

public:
  PlayerController(EntityManager&, TextureRepo&);

  void addPlayer(int x, int y);
  bool isPlayer(int) const;
  int  getPlayerId() const;
  void keepWithinWindow();
  bool checkPlayerDead();

  void movePlayerUp();
  void movePlayerDown();
  void movePlayerLeft();
  void movePlayerRight();

  void stopMovingPlayer();
  void stopMovingPlayerUp();
  void stopMovingPlayerDown();
  void stopMovingPlayerLeft();
  void stopMovingPlayerRight();

  void shootGun();
  void stopShootingGun();

private:
  SpriteComponent           createSprite() const;
  static TransformComponent createTransform(int x, int y);
  static GunComponent       createGun();
  static ColliderComponent  createCollider();
};