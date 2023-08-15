#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(EntityManager& em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void TextureManager::updateTextures() {
  for (int i = 0; i < _em.num_entities; i++)
    updateTexture(i);
}

void TextureManager::updateTexture(int entity) {
  SDL2::Texture       tex       = _em.sprites[entity].texture;
  TransformComponent& transform = _em.transforms[entity];
  SDL2::blit(tex,
             _renderer,
             transform.position.x,
             transform.position.y,
             transform.width,
             transform.height);
}