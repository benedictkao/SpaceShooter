#include "EnemyManager.h"
#include <iostream>
#include <utility>

static constexpr auto BASIC_ENEMY_SIZE{ 42 };
static constexpr auto BASIC_ENEMY_SPEED{ 3 };
static constexpr auto BASIC_ENEMY_HP{ 1 };
static constexpr auto BASIC_ENEMY_POINTS{ 10 };

static constexpr auto SHOOTER_SIZE{ 42 };
static constexpr auto SHOOTER_SPEED{ 2 };
static constexpr auto SHOOTER_HP{ 10 };
static constexpr auto SHOOTER_POINTS{ 0 };

static constexpr auto BOSS_SIZE{ 72 };
static constexpr auto BOSS_SPEED{ 2 };
static constexpr auto BOSS_HP{ 60 };
static constexpr auto BOSS_POINTS{ 60 };

EnemyManager::EnemyManager(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo) {}

void EnemyManager::updateSpawner(int spawnerId) {
  SpawnComponent&     spawner = _em.getComponent<SpawnComponent>(spawnerId);
  TransformComponent& parentTransform =
    _em.getComponent<TransformComponent>(spawnerId);
  if (--spawner.currCoolDown <= 0) {
    switch (spawner.type) {
      case EnemyType::BASIC:
        spawnBasic(parentTransform.position);
        break;
      case EnemyType::BOSS:
        spawnBoss(parentTransform.position);
        break;
    }
    spawner.currCoolDown = spawner.coolDown;
    if (--spawner.spawnCount <= 0)
      _em.scheduleRemoval(spawnerId);
  }
}

void EnemyManager::updateActiveEnemies() {
  auto& it = _activeEnemies.begin();
  while (it != _activeEnemies.end()) {
    if (_em.isScheduledForRemoval(*it))
      it = _activeEnemies.erase(it);
    else
      ++it;
  }
}

bool EnemyManager::allEnemiesDead() const {
  // std::cout << "num enemies: " << _activeEnemies.size() << std::endl;
  return _activeEnemies.empty();
}

void EnemyManager::reset() {
  _activeEnemies.clear();
}

void EnemyManager::spawnBasic(const Point& pos) {
  TransformComponent t;
  t.height = t.width = BASIC_ENEMY_SIZE;
  t.position.x       = pos.x;
  t.position.y       = pos.y - t.height / 2;

  SpeedComponent speed;
  speed.direction = { 0, 1 };
  speed.speed     = BASIC_ENEMY_SPEED;

  SpriteComponent sprite;
  sprite.texture = _texRepo.loadTexture(TextureId::BASIC_ENEMY);

  ColliderComponent collider;
  collider.health = collider.damage = BASIC_ENEMY_HP;
  collider.deathAnim                = AnimationId::DEFAULT_EXPLOSION;
  collider.scorePoints              = BASIC_ENEMY_POINTS;

  int enemyId = _em.addEntity()
                  .add<TransformComponent>(t)
                  .add<SpeedComponent>(speed)
                  .add<SpriteComponent>(sprite)
                  .add<ColliderComponent>(collider)
                  .addFlags(ComponentFlag::ENEMY)
                  .id();
  _activeEnemies.insert(enemyId);
}

void EnemyManager::spawnShooter(const Point& pos) {
  TransformComponent t;
  t.height = t.width = BASIC_ENEMY_SIZE;
  t.position.x       = pos.x;
  t.position.y       = pos.y - t.height / 2;

  SpeedComponent speed;
  speed.direction = { 0, 1 };
  speed.speed     = BASIC_ENEMY_SPEED;

  SpriteComponent sprite;
  sprite.texture = _texRepo.loadTexture(TextureId::BASIC_ENEMY);

  ColliderComponent collider;
  collider.health = collider.damage = BASIC_ENEMY_HP;
  collider.deathAnim                = AnimationId::DEFAULT_EXPLOSION;
  collider.scorePoints              = BASIC_ENEMY_POINTS;

  int enemyId = _em.addEntity()
                  .add<TransformComponent>(t)
                  .add<SpeedComponent>(speed)
                  .add<SpriteComponent>(sprite)
                  .add<ColliderComponent>(collider)
                  .addFlags(ComponentFlag::ENEMY)
                  .id();
  _activeEnemies.insert(enemyId);
}

void EnemyManager::spawnBoss(const Point& pos) {
  TransformComponent t;
  t.height = t.width = BOSS_SIZE;
  t.position.x       = pos.x;
  t.position.y       = pos.y - t.height / 2;

  PathComponent path;
  path.points.push_back({ 400, 200 });
  path.points.push_back({ 100, 200 });
  path.points.push_back({ 100, 100 });
  path.points.push_back({ 400, 100 });
  path.points.push_back({ 400, 200 });
  path.points.push_back({ 700, 200 });
  path.points.push_back({ 700, 100 });
  path.points.push_back({ 400, 100 });
  path.current    = 0;
  path.repeatFrom = 0;

  SpeedComponent speed;
  speed.direction = { 0, 0 };
  speed.speed     = BOSS_SPEED;

  SpriteComponent sprite;
  sprite.texture = _texRepo.loadTexture(TextureId::BOSS_ENEMY);

  ColliderComponent collider;
  collider.health = collider.damage = BOSS_HP;
  collider.deathAnim                = AnimationId::LOUD_EXPLOSION;
  collider.scorePoints              = BOSS_POINTS;

  GunComponent g;
  g.ammo      = AmmoTypes::ENEMY_BOSS;
  g.coolDown  = g.ammo.coolDown;
  g.direction = Direction::DOWN;
  g.isFiring  = true;

  int enemyId = _em.addEntity()
                  .add<TransformComponent>(t)
                  .add<PathComponent>(std::move(path))
                  .add<SpeedComponent>(speed)
                  .add<SpriteComponent>(sprite)
                  .add<ColliderComponent>(collider)
                  .add<GunComponent>(g)
                  .addFlags(ComponentFlag::ENEMY)
                  .id();
  _activeEnemies.insert(enemyId);
}