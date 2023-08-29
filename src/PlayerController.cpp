#include "PlayerController.h"
#include "../utils/Math.h"
#include "Constants.h"

static constexpr int  PLAYER_SPEED{ 8 };
static constexpr int  PLAYER_HP{ 5 };
static constexpr auto PLAYER_SPRITE_PATH{ "../../../res/player.png" };

PlayerController::PlayerController(EntityManager& em, TextureRepo& textureRepo)
    : _em(em), _textureRepo(textureRepo), _playerId(-1) {}

void PlayerController::addPlayer(int x, int y) {
  _playerId = _em.addEntity()
                .add<SpriteComponent>(createSprite())
                .add<TransformComponent>(createTransform(x, y))
                .add<GunComponent>(createGun())
                .add<ColliderComponent>(createCollider())
                .id();
}

bool PlayerController::isPlayer(int id) const {
  return id == _playerId;
}

int PlayerController::getPlayerId() const {
  return _playerId;
}

void PlayerController::keepWithinWindow() {
  TransformComponent& transform =
    _em.getComponent<TransformComponent>(_playerId);
  coerceBetween(transform.position.x,
                0,
                Constants::WINDOW_WIDTH - transform.width);
  coerceBetween(transform.position.y,
                0,
                Constants::WINDOW_HEIGHT - transform.height);
}

bool PlayerController::checkPlayerDead() {
  return _em.isScheduledForRemoval(_playerId);
}

SpriteComponent PlayerController::createSprite() const {
  SpriteComponent sprite;
  sprite.texture = _textureRepo.loadWithoutCache(TextureId::GREEN_SHIP);
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
  gun.ammo      = AmmoTypes::PLAYER_DEFAULT;
  gun.direction = Direction::UP;
  gun.coolDown  = 0;
  gun.isFiring  = false;
  return gun;
}

ColliderComponent PlayerController::createCollider() {
  ColliderComponent collider;
  collider.health    = PLAYER_HP;
  collider.damage    = Mass::INFINITE;
  collider.deathAnim = AnimationId::DEFAULT_EXPLOSION;
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

void PlayerController::stopMovingPlayer() {
  _em.getComponent<TransformComponent>(_playerId).speed = { 0, 0 };
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