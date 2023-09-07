#pragma once

#include "../EntityManager.h"
#include "TextureRepo.h"
#include <stack>

class PlayerController {
private:
  EntityManager&  _em;
  TextureRepo&    _textureRepo;
  int             _playerId;
  std::stack<int> _hpIds;

public:
  PlayerController(EntityManager&, TextureRepo&);

  void addPlayer(int x, int y);
  bool isPlayer(int) const;
  int  getPlayerId() const;
  int  getHp() const;
  bool updateHp();
  void keepWithinWindow();
  void reset();

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

  SpriteComponent    createSprite() const;
  TransformComponent createTransform(int x, int y);

private:
  GunComponent      createGun();
  ColliderComponent createCollider();
};