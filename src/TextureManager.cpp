#include "TextureManager.h"

TextureManager::TextureManager(EntityManager &em, SDL2::Renderer renderer)
    : _em(em), _renderer(renderer) {}

void TextureManager::updateTextures() {
  for (int i = 0; i < _em.num_entities; i++)
    updateTexture(_em.sprites[i]);
}

void TextureManager::updateTexture(const SpriteComponent &sprite) {
  TransformComponent &transform = _em.transforms[sprite.entity];
  SDL2::blit(sprite.texture, _renderer, transform.position.x,
             transform.position.y, transform.width, transform.height);
}