#include "PlayerController.h"
#include "../utils/Math.h"
#include "Constants.h"

static constexpr int  PLAYER_SPEED{ 8 };
static constexpr int  PLAYER_HP{ 3 };
static constexpr auto PLAYER_SIZE{ 32 };
static constexpr auto PLAYER_SPRITE_PATH{ "../../../res/player.png" };

static constexpr auto HP_SIZE{ 24 };
static constexpr auto HP_GAP{ 5 };
static constexpr auto HP_BAR_Y_POS{ 570 };

PlayerController::PlayerController(EntityManager& em, TextureRepo& textureRepo)
    : _em(em), _textureRepo(textureRepo), _playerId(-1) {}

void PlayerController::addPlayer(int x, int y) {
  _playerId = _em.addEntity()
                .add<SpriteComponent>(createSprite())
                .add<TransformComponent>(createTransform(x, y))
                .add<GunComponent>(createGun())
                .add<ColliderComponent>(createCollider())
                .add<SpeedComponent>({ { 0, 0 }, PLAYER_SPEED })
                .id();

  SpriteComponent hpSprite;
  hpSprite.texture = _textureRepo.loadTexture(TextureId::HEART);

  TransformComponent hpTransform;
  hpTransform.position = { 0, HP_BAR_Y_POS };
  hpTransform.height   = HP_SIZE;
  hpTransform.width    = HP_SIZE;
  for (int i = 0; i < PLAYER_HP; ++i) {
    hpTransform.position.x += HP_SIZE + HP_GAP;
    int id = _em.addEntity()
               .add<TransformComponent>(hpTransform)
               .add<SpriteComponent>(hpSprite)
               .id();
    _hpIds.push(id);
  }
}

bool PlayerController::isPlayer(int id) const {
  return id == _playerId;
}

int PlayerController::getPlayerId() const {
  return _playerId;
}

int PlayerController::getHp() const {
  return _hpIds.size();
}

bool PlayerController::updateHp() {
  int currentHp = _em.getComponent<ColliderComponent>(_playerId).health;
  coercePositive(currentHp);
  int displayHp = _hpIds.size();
  while (displayHp > currentHp) {
    _em.scheduleRemoval(_hpIds.top());
    _hpIds.pop();
    --displayHp;
  }
  return currentHp > 0;
}

void PlayerController::keepWithinWindow() {
  TransformComponent& transform =
    _em.getComponent<TransformComponent>(_playerId);
  int halfWidth  = transform.width / 2;
  int halfHeight = transform.height / 2;
  coerceBetween(transform.position.x,
                0 + halfWidth,
                Constants::WINDOW_WIDTH - halfWidth);
  coerceBetween(transform.position.y,
                0 + halfHeight,
                Constants::WINDOW_HEIGHT - halfHeight);
}

void PlayerController::reset() {
  _playerId = -1;
  while (!_hpIds.empty())
    _hpIds.pop();
}

SpriteComponent PlayerController::createSprite() const {
  SpriteComponent sprite;
  sprite.texture = _textureRepo.loadTexture(TextureId::GREEN_SHIP);
  return sprite;
}

TransformComponent PlayerController::createTransform(int x, int y) {
  TransformComponent transform;
  transform.position.x = x;
  transform.position.y = y;
  transform.height     = PLAYER_SIZE;
  transform.width      = PLAYER_SIZE;
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
  collider.health = collider.damage = PLAYER_HP;
  collider.deathAnim                = AnimationId::DEFAULT_EXPLOSION;
  collider.scorePoints              = 0;
  return collider;
}

void PlayerController::movePlayerUp() {
  _em.getComponent<SpeedComponent>(_playerId).direction.y = -1;
}

void PlayerController::movePlayerDown() {
  _em.getComponent<SpeedComponent>(_playerId).direction.y = 1;
}

void PlayerController::movePlayerLeft() {
  _em.getComponent<SpeedComponent>(_playerId).direction.x = -1;
}

void PlayerController::movePlayerRight() {
  _em.getComponent<SpeedComponent>(_playerId).direction.x = 1;
}

void PlayerController::stopMovingPlayer() {
  _em.getComponent<SpeedComponent>(_playerId).direction = { 0, 0 };
}

void PlayerController::stopMovingPlayerUp() {
  coercePositive(_em.getComponent<SpeedComponent>(_playerId).direction.y);
}

void PlayerController::stopMovingPlayerDown() {
  coerceNegative(_em.getComponent<SpeedComponent>(_playerId).direction.y);
}

void PlayerController::stopMovingPlayerLeft() {
  coercePositive(_em.getComponent<SpeedComponent>(_playerId).direction.x);
}

void PlayerController::stopMovingPlayerRight() {
  coerceNegative(_em.getComponent<SpeedComponent>(_playerId).direction.x);
}

void PlayerController::shootGun() {
  _em.getComponent<GunComponent>(_playerId).isFiring = true;
}

void PlayerController::stopShootingGun() {
  _em.getComponent<GunComponent>(_playerId).isFiring = false;
}