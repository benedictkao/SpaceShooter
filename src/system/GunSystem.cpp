#include "GunSystem.h"
#include "utils/Math.h"

GunSystem::GunSystem(EntityManager& em, TextureRepo& textureRepo)
    : _em(em), _textureRepo(textureRepo) {}

void GunSystem::spawnProjectiles() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.getComponent<EntitySettings>(i).hasComponents(ComponentFlag::GUN)) {
      const TransformComponent& parentTransform =
        _em.getComponent<TransformComponent>(i);
      GunComponent& gun = _em.getComponent<GunComponent>(i);
      if (gun.coolDown == 0) {
        if (!gun.isFiring) {
          return;
        }
        createProjectile(gun, parentTransform);
        gun.coolDown = gun.ammo.coolDown;
      } else {
        --gun.coolDown;
      }
    }
  }
}

void GunSystem::createProjectile(const GunComponent&       gun,
                                 const TransformComponent& parent) {

  SpriteComponent sprite;
  sprite.texture = _textureRepo.loadTexture(gun.ammo.asset);

  TransformComponent transform;
  transform.height     = gun.ammo.height;
  transform.width      = gun.ammo.width;
  transform.position.x = parent.centerX() - transform.width / 2;
  transform.position.y = parent.position.y;
  transform.speed      = gun.direction * gun.ammo.speed;

  ColliderComponent collider;
  collider.health  = 1;
  collider.mass    = 1;
  collider.isEnemy = false; // TODO: this should be in a separate component

  _em.addEntity()
    .add<SpriteComponent>(sprite)
    .add<TransformComponent>(transform)
    .add<ColliderComponent>(collider);
}