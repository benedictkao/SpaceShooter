#include "EnemyManager.h"

EnemyManager::EnemyManager(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo) {}

void EnemyManager::addSimpleEnemy() {
  TransformComponent t;
  t.position = { 360, 100 };
  t.speed    = { 0, 0 };
  t.height   = 80;
  t.width    = 80;
  SpriteComponent s;
  s.texture = _texRepo.loadTexture(TextureId::ENEMY_SHIP);
  ColliderComponent c;
  c.health = 10;
  c.mass   = 5;
  GunComponent g;
  g.ammo      = AmmoTypes::ENEMY_DEFAULT;
  g.coolDown  = 36;
  g.direction = Direction::DOWN;
  g.isFiring  = true;
  _em.addEntity()
    .setEnemy(true)
    .add<TransformComponent>(t)
    .add<SpriteComponent>(s)
    .add<ColliderComponent>(c)
    .add<GunComponent>(g);
}
