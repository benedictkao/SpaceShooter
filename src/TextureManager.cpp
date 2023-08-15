#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(EntityManager& em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void TextureManager::updateTextures() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities)
    updateTexture(i);
}

void TextureManager::updateTexture(int entity) {
  SDL2::Texture       tex = _em.getComponent<SpriteComponent>(entity).texture;
  TransformComponent& transform = _em.getComponent<TransformComponent>(entity);
  SDL2::blit(tex,
             _renderer,
             transform.position.x,
             transform.position.y,
             transform.width,
             transform.height);
}