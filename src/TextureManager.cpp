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

SDL2::Texture TextureManager::loadTexture(TextureParams params) {
  auto it = _textureMap.find(params.key);
  if (it == _textureMap.end()) {
    SDL2::Texture tex       = SDL2::loadTexture(params.path, _renderer);
    _textureMap[params.key] = tex;
    return tex;
  } else {
    std::cout << "Texture " << params.path << " loaded from cache" << std::endl;
    return it->second;
  }
}

SDL2::Texture TextureManager::loadWithoutCache(const char* path) {
  return SDL2::loadTexture(path, _renderer);
}