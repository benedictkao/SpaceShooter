#include "PlayerController.h"
#include "Math.h"

static constexpr int PLAYER_SPEED{8};

PlayerController::PlayerController(EntityManager &em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void PlayerController::addPlayer(int x, int y) {
  _playerId = _em.addEntity();

  EntitySettings &settings = _em.settings[_playerId];
  settings.setComponents(ComponentFlag::SPRITE | ComponentFlag::TRANSFORM);

  // TODO: put this in a separate fun
  SpriteComponent &sprite = _em.sprites[_playerId];
  sprite.entity = _playerId;
  sprite.texture = SDL2::loadTexture("../../../res/spaceship.png", _renderer);

  // TODO: put this in a separate fun
  TransformComponent &transform = _em.transforms[_playerId];
  transform.entity = _playerId;
  transform.position.x = x;
  transform.position.y = y;
  transform.speed.x = 0;
  transform.speed.y = 0;
  transform.height = 32;
  transform.width = 32;
}

void PlayerController::movePlayerUp() {
  // 0 always refers to the player
  _em.transforms[0].speed.y = -PLAYER_SPEED;
}

void PlayerController::movePlayerDown() {
  // 0 always refers to the player
  _em.transforms[0].speed.y = PLAYER_SPEED;
}

void PlayerController::movePlayerLeft() {
  // 0 always refers to the player
  _em.transforms[0].speed.x = -PLAYER_SPEED;
}

void PlayerController::movePlayerRight() {
  // 0 always refers to the player
  _em.transforms[0].speed.x = PLAYER_SPEED;
}

void PlayerController::stopMovingPlayerUp() {
  int currYSpeed = _em.transforms[0].speed.y;
  _em.transforms[0].speed.y = max(currYSpeed, 0);
}

void PlayerController::stopMovingPlayerDown() {
  int currYSpeed = _em.transforms[0].speed.y;
  _em.transforms[0].speed.y = min(currYSpeed, 0);
}

void PlayerController::stopMovingPlayerLeft() {
  int currXSpeed = _em.transforms[0].speed.x;
  _em.transforms[0].speed.x = max(currXSpeed, 0);
}

void PlayerController::stopMovingPlayerRight() {
  int currXSpeed = _em.transforms[0].speed.x;
  _em.transforms[0].speed.x = min(currXSpeed, 0);
}