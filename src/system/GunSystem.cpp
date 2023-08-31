#include "GunSystem.h"
#include "utils/Math.h"

GunSystem::GunSystem(EntityManager& em, TextureRepo& textureRepo)
    : _em(em), _textureRepo(textureRepo) {}

void GunSystem::spawnProjectiles() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::GUN)) {
      const TransformComponent& parentTransform =
        _em.getComponent<TransformComponent>(i);
      GunComponent& gun = _em.getComponent<GunComponent>(i);
      if (gun.coolDown > 0) {
        --gun.coolDown;
      } else if (gun.isFiring) {
        bool isEnemy = _em.hasComponents(i, ComponentFlag::ENEMY);
        createProjectile(gun, parentTransform, isEnemy);
        gun.coolDown = gun.ammo.coolDown;
      }
    }
  }
}

void GunSystem::createProjectile(const GunComponent&       gun,
                                 const TransformComponent& parent,
                                 bool                      isEnemy) {

  SpriteComponent sprite;
  sprite.texture = _textureRepo.loadTexture(gun.ammo.assetId);

  TransformComponent transform;
  transform.height     = gun.ammo.height;
  transform.width      = gun.ammo.width;
  transform.position.x = parent.centerX() - transform.width / 2;
  int offsetY          = gun.direction == Direction::DOWN ? parent.height : 0;
  transform.position.y = parent.position.y + offsetY;

  SpeedComponent speed = static_cast<SpeedComponent>(gun.direction * gun.ammo.speed);

  ColliderComponent collider;
  collider.health    = gun.ammo.damage;
  collider.damage    = gun.ammo.damage;
  collider.deathAnim = AnimationId::NONE;

  unsigned int enemyFlag = isEnemy ? ComponentFlag::ENEMY : 0;

  _em.addEntity()
    .add<SpriteComponent>(sprite)
    .add<TransformComponent>(transform)
    .add<SpeedComponent>(speed)
    .add<ColliderComponent>(collider)
    .addFlags(enemyFlag);
}