#include "PlayerController.h"
#include "utils/Math.h"

static constexpr int PLAYER_SPEED{8};
static constexpr auto PLAYER_SPRITE_PATH{"../../../res/player.png"};

PlayerController::PlayerController(EntityManager &em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void PlayerController::addPlayer(int x, int y) {
  _playerId = _em.addEntity();

  EntitySettings &settings = _em.settings[_playerId];
  settings.setComponents(ComponentFlag::GUN);
  initPlayerSprite();
  initPlayerTransform(x, y);
  initPlayerGun();
}

void PlayerController::initPlayerSprite() {
  SpriteComponent &sprite = _em.sprites[_playerId];
  sprite.texture = SDL2::loadTexture(PLAYER_SPRITE_PATH, _renderer);
}

void PlayerController::initPlayerTransform(int x, int y) {
  TransformComponent &transform = _em.transforms[_playerId];
  transform.position.x = x;
  transform.position.y = y;
  transform.speed.x = 0;
  transform.speed.y = 0;
  transform.height = 32;
  transform.width = 32;
}

void PlayerController::initPlayerGun() {
  GunComponent &gun = _em.guns[_playerId];
  gun.ammo = Ammo::Normal;
  gun.direction = {0, -1};
  gun.coolDown = 0;
  gun.isFiring = false;
}

void PlayerController::movePlayerUp() {
  _em.transforms[_playerId].speed.y = -PLAYER_SPEED;
}

void PlayerController::movePlayerDown() {
  _em.transforms[_playerId].speed.y = PLAYER_SPEED;
}

void PlayerController::movePlayerLeft() {
  _em.transforms[_playerId].speed.x = -PLAYER_SPEED;
}

void PlayerController::movePlayerRight() {
  _em.transforms[_playerId].speed.x = PLAYER_SPEED;
}

void PlayerController::stopMovingPlayerUp() {
  int currYSpeed = _em.transforms[_playerId].speed.y;
  _em.transforms[_playerId].speed.y = max(currYSpeed, 0);
}

void PlayerController::stopMovingPlayerDown() {
  int currYSpeed = _em.transforms[0].speed.y;
  _em.transforms[_playerId].speed.y = min(currYSpeed, 0);
}

void PlayerController::stopMovingPlayerLeft() {
  int currXSpeed = _em.transforms[0].speed.x;
  _em.transforms[_playerId].speed.x = max(currXSpeed, 0);
}

void PlayerController::stopMovingPlayerRight() {
  int currXSpeed = _em.transforms[0].speed.x;
  _em.transforms[_playerId].speed.x = min(currXSpeed, 0);
}

void PlayerController::shootGun() { _em.guns[_playerId].isFiring = true; }

void PlayerController::stopShootingGun() {
  _em.guns[_playerId].isFiring = false;
}