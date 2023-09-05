#include "GunSystem.h"
#include "utils/Math.h"

GunSystem::GunSystem(EntityManager& em,
                     TextureRepo&   textureRepo,
                     MusicManager&  musicManager)
    : _em(em), _textureRepo(textureRepo), _musicManager(musicManager) {}

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
  transform.position.x = parent.position.x;
  int sign             = gun.direction == Direction::DOWN ? 1 : -1;
  transform.position.y = parent.position.y + sign * parent.height / 2;

  SpeedComponent speed;
  speed.direction = gun.direction;
  speed.speed     = gun.ammo.speed;

  ColliderComponent collider;
  collider.health      = gun.ammo.damage;
  collider.damage      = gun.ammo.damage;
  collider.deathAnim   = AnimationId::NONE;
  collider.scorePoints = 0;

  unsigned int enemyFlag = isEnemy ? ComponentFlag::ENEMY : 0;

  _em.addEntity()
    .add<SpriteComponent>(sprite)
    .add<TransformComponent>(transform)
    .add<SpeedComponent>(speed)
    .add<ColliderComponent>(collider)
    .addFlags(enemyFlag);

  if (gun.ammo.soundId != SoundId::NONE)
    _musicManager.playSound(gun.ammo.soundId);
}