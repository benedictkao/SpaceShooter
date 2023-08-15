#include "PlayerController.h"
#include "utils/Math.h"

static constexpr int  PLAYER_SPEED{ 8 };
static constexpr int  PLAYER_HP{ 5 };
static constexpr auto PLAYER_SPRITE_PATH{ "../../../res/player.png" };

PlayerController::PlayerController(EntityManager& em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer), _playerId(0) {}

void PlayerController::addPlayer(int x, int y) {
  _playerId = _em.addEntity()
                .add<SpriteComponent>(createSprite())
                .add<TransformComponent>(createTransform(x, y))
                .add<GunComponent>(createGun())
                .add<ColliderComponent>(createCollider())
                .id();
}

SpriteComponent PlayerController::createSprite() const {
  SpriteComponent sprite;
  sprite.texture = SDL2::loadTexture(PLAYER_SPRITE_PATH, _renderer);
  return sprite;
}

TransformComponent PlayerController::createTransform(int x, int y) {
  TransformComponent transform;
  transform.position = { x, y };
  transform.speed    = { 0, 0 };
  transform.height   = 32;
  transform.width    = 32;
  return transform;
}

GunComponent PlayerController::createGun() {
  GunComponent gun;
  gun.ammo      = Ammo::Normal;
  gun.direction = Direction::UP;
  gun.coolDown  = 0;
  gun.isFiring  = false;
  return gun;
}

ColliderComponent PlayerController::createCollider() {
  ColliderComponent collider;
  collider.health  = PLAYER_HP;
  collider.mass    = Mass::INFINITE;
  collider.isEnemy = false;
  return collider;
}

void PlayerController::movePlayerUp() {
  _em.getComponent<TransformComponent>(_playerId).speed.y = -PLAYER_SPEED;
}

void PlayerController::movePlayerDown() {
  _em.getComponent<TransformComponent>(_playerId).speed.y = PLAYER_SPEED;
}

void PlayerController::movePlayerLeft() {
  _em.getComponent<TransformComponent>(_playerId).speed.x = -PLAYER_SPEED;
}

void PlayerController::movePlayerRight() {
  _em.getComponent<TransformComponent>(_playerId).speed.x = PLAYER_SPEED;
}

void PlayerController::stopMovingPlayerUp() {
  coercePositive(_em.getComponent<TransformComponent>(_playerId).speed.y);
}

void PlayerController::stopMovingPlayerDown() {
  coerceNegative(_em.getComponent<TransformComponent>(_playerId).speed.y);
}

void PlayerController::stopMovingPlayerLeft() {
  coercePositive(_em.getComponent<TransformComponent>(_playerId).speed.x);
}

void PlayerController::stopMovingPlayerRight() {
  coerceNegative(_em.getComponent<TransformComponent>(_playerId).speed.x);
}

void PlayerController::shootGun() {
  _em.getComponent<GunComponent>(_playerId).isFiring = true;
}

void PlayerController::stopShootingGun() {
  _em.getComponent<GunComponent>(_playerId).isFiring = false;
}