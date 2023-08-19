#include "TextureSystem.h"

TextureSystem::TextureSystem(EntityManager& em)
    : _em(em) {}

void TextureSystem::setRenderer(SDL2::Renderer renderer) {
  _renderer = renderer;
}

void TextureSystem::updateTextures() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities)
    updateTexture(i);
}

void TextureSystem::updateTexture(int entity) {
  SDL2::Texture       tex = _em.getComponent<SpriteComponent>(entity).texture;
  TransformComponent& transform = _em.getComponent<TransformComponent>(entity);
  SDL2::blit(tex,
             _renderer,
             transform.position.x,
             transform.position.y,
             transform.width,
             transform.height);
}