#include "PlayerController.h"
#include "utils/Math.h"

static constexpr int  PLAYER_SPEED{ 8 };
static constexpr auto PLAYER_SPRITE_PATH{ "../../../res/player.png" };

PlayerController::PlayerController(EntityManager& em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void PlayerController::addPlayer(int x, int y) {
  _playerId = _em.addEntity();

  EntitySettings& settings = _em.settings[_playerId];
  settings.addComponents(ComponentFlag::GUN | ComponentFlag::COLLIDER);
  initPlayerSprite();
  initPlayerTransform(x, y);
  initPlayerGun();
  // put in separate fun
  ColliderComponent& collider = _em.colliders[_playerId];
  collider.health             = 5;
  collider.mass               = Mass::INFINITE;
  collider.isEnemy            = false;
}

void PlayerController::initPlayerSprite() {
  SpriteComponent& sprite = _em.sprites[_playerId];
  sprite.texture          = SDL2::loadTexture(PLAYER_SPRITE_PATH, _renderer);
}

void PlayerController::initPlayerTransform(int x, int y) {
  TransformComponent& transform = _em.transforms[_playerId];
  transform.position            = { x, y };
  transform.speed               = { 0, 0 };
  transform.height              = 32;
  transform.width               = 32;
}

void PlayerController::initPlayerGun() {
  GunComponent& gun = _em.guns[_playerId];
  gun.ammo          = Ammo::Normal;
  gun.direction     = Direction::UP;
  gun.coolDown      = 0;
  gun.isFiring      = false;
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
  coercePositive(_em.transforms[_playerId].speed.y);
}

void PlayerController::stopMovingPlayerDown() {
  coerceNegative(_em.transforms[_playerId].speed.y);
}

void PlayerController::stopMovingPlayerLeft() {
  coercePositive(_em.transforms[_playerId].speed.x);
}

void PlayerController::stopMovingPlayerRight() {
  coerceNegative(_em.transforms[_playerId].speed.x);
}

void PlayerController::shootGun() {
  _em.guns[_playerId].isFiring = true;
}

void PlayerController::stopShootingGun() {
  _em.guns[_playerId].isFiring = false;
}