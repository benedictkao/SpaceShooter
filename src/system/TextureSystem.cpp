#include "TextureSystem.h"

TextureSystem::TextureSystem(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo) {}

void TextureSystem::setRenderer(SDL2::Renderer renderer) {
  _renderer = renderer;
}


void TextureSystem::updateAnimations() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::ANIMATION)) {
      AnimationComponent& animation = _em.getComponent<AnimationComponent>(i);
      TransformComponent& transform = _em.getComponent<TransformComponent>(i);
      SDL2::Texture       tex       = _texRepo.loadTexture(animation.texId);
    }
  }
}

void TextureSystem::updateSprites() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities)
    updateSprite(i);
}

void TextureSystem::updateSprite(int entity) {
  SDL2::Texture       tex = _em.getComponent<SpriteComponent>(entity).texture;
  TransformComponent& transform = _em.getComponent<TransformComponent>(entity);
  SDL2::blit(tex,
             _renderer,
             transform.position.x,
             transform.position.y,
             transform.width,
             transform.height);
}