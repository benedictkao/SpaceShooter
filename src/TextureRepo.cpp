#include "TextureRepo.h"
#include <iostream>

void TextureRepo::setRenderer(SDL2::Renderer renderer) {
  _renderer = renderer;
}

SDL2::Texture TextureRepo::loadTexture(TextureParams params) {
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

SDL2::Texture TextureRepo::loadWithoutCache(const char* path) {
  return SDL2::loadTexture(path, _renderer);
}
