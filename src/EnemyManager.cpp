#include "EnemyManager.h"

EnemyManager::EnemyManager(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo) {}

void EnemyManager::addSimpleEnemy() {
  // TransformComponent t;
  // t.position = { 360, 100 };
  // t.height   = 80;
  // t.width    = 80;
  // SpriteComponent s;
  // s.texture = _texRepo.loadTexture(TextureId::ENEMY_SHIP);
  // ColliderComponent c;
  // c.health    = 10;
  // c.damage    = 5;
  // c.deathAnim = AnimationId::DEFAULT_EXPLOSION;
  // GunComponent g;
  // g.ammo      = AmmoTypes::ENEMY_BOSS;
  // g.coolDown  = 36;
  // g.direction = Direction::DOWN;
  // g.isFiring  = true;
  //_em.addEntity()
  //   .add<TransformComponent>(t)
  //   .add<SpriteComponent>(s)
  //   .add<ColliderComponent>(c)
  //   .add<GunComponent>(g)
  //   .addFlags(ComponentFlag::ENEMY);
}

void EnemyManager::spawnEnemy(int spawnerId) {
  SpawnComponent&     spawner = _em.getComponent<SpawnComponent>(spawnerId);
  TransformComponent& parentTransform =
    _em.getComponent<TransformComponent>(spawnerId);
  if (--spawner.currCoolDown == 0) {
    TransformComponent t;
    t.position = parentTransform.position;
    t.height   = spawner.details->height;
    t.width    = spawner.details->width;

    SpeedComponent speed = spawner.details->speed;

    SpriteComponent sprite;
    sprite.texture = _texRepo.loadTexture(spawner.details->texId);

    ColliderComponent collider;
    collider.health = collider.damage = spawner.details->hp;
    collider.deathAnim                = AnimationId::DEFAULT_EXPLOSION;

    int enemyId = _em.addEntity()
                    .add<TransformComponent>(t)
                    .add<SpeedComponent>(speed)
                    .add<SpriteComponent>(sprite)
                    .add<ColliderComponent>(collider)
                    .addFlags(ComponentFlag::ENEMY)
                    .id();
    _activeEnemies.insert(enemyId);

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
