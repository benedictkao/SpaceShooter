#include "GunManager.h"
#include "utils/Math.h"

GunManager::GunManager(EntityManager& em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void GunManager::shootProjectiles() {
  for (int i = 0; i < _em.num_entities; i++) {
    if (_em.settings[i].hasComponents(ComponentFlag::GUN)) {
      const TransformComponent& parentTransform = _em.transforms[i];
      GunComponent&             gun             = _em.guns[i];
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

void GunManager::createProjectile(const GunComponent&       gun,
                                  const TransformComponent& parent) {
  int             projectileId = _em.addEntity();
  EntitySettings& settings     = _em.settings[projectileId];
  settings.addComponents(ComponentFlag::COLLIDER);

  SpriteComponent& sprite = _em.sprites[projectileId];
  sprite.texture          = SDL2::loadTexture(gun.ammo.asset, _renderer);

  TransformComponent& transform = _em.transforms[projectileId];
  transform.height              = gun.ammo.height;
  transform.width               = gun.ammo.width;
  transform.position.x          = parent.centerX() - transform.width / 2;
  transform.position.y          = parent.position.y;
  transform.speed               = gun.direction * gun.ammo.speed;

  ColliderComponent& collider = _em.colliders[projectileId];
  collider.health             = 1;
  collider.mass               = 1;
  collider.isEnemy = false; // TODO: this should be in a separate component
}