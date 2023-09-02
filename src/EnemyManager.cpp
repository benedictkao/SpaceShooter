#include "EnemyManager.h"
#include <utility>

EnemyManager::EnemyManager(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo) {}

void EnemyManager::spawnEnemy(int spawnerId) {
  SpawnComponent&     spawner = _em.getComponent<SpawnComponent>(spawnerId);
  TransformComponent& parentTransform =
    _em.getComponent<TransformComponent>(spawnerId);
  if (--spawner.currCoolDown == 0) {
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
    if (_em.isActive(*it))
      ++it;
    else
      it = _activeEnemies.erase(it);
  }
}

bool EnemyManager::allEnemiesDead() const {
  return _activeEnemies.empty();
}

void EnemyManager::spawnBasic(const Point& pos) {
  TransformComponent t;
  t.position = pos;
  t.height   = 42;
  t.width    = 42;

  SpeedComponent speed;
  speed.direction = { 0, 1 };
  speed.speed     = 3;

  SpriteComponent sprite;
  sprite.texture = _texRepo.loadTexture(TextureId::BASIC_ENEMY);

  ColliderComponent collider;
  collider.health = collider.damage = 1;
  collider.deathAnim                = AnimationId::DEFAULT_EXPLOSION;

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
  t.position = pos;
  t.height   = 80;
  t.width    = 80;

  PathComponent path;
  path.points.push_back({ 400, 100 });
  path.points.push_back({ 100, 100 });
  path.points.push_back({ 700, 100 });
  path.current    = 0;
  path.repeatFrom = 1;

  SpeedComponent speed;
  speed.direction = { 0, 0 };
  speed.speed     = 2;

  SpriteComponent sprite;
  sprite.texture = _texRepo.loadTexture(TextureId::BOSS_ENEMY);

  ColliderComponent collider;
  collider.health = collider.damage = 20;
  collider.deathAnim                = AnimationId::DEFAULT_EXPLOSION;

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
