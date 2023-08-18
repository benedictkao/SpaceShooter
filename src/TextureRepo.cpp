#include "TextureRepo.h"
#include <iostream>

void TextureRepo::setRenderer(SDL2::Renderer renderer) {
  _renderer = renderer;
}

SDL2::Texture TextureRepo::loadTexture(unsigned int id) {
  auto        it   = _textureMap.find(id);
  const char* path = TextureId::getPath(id);
  if (it == _textureMap.end()) {
    SDL2::Texture tex = SDL2::loadTexture(path, _renderer);
    _textureMap[id]   = tex;
    return tex;
  } else {
    std::cout << "Texture " << path << " loaded from cache" << std::endl;
    return it->second;
  }
}

SDL2::Texture TextureRepo::loadWithoutCache(unsigned int id) {
  return SDL2::loadTexture(TextureId::getPath(id), _renderer);
}
