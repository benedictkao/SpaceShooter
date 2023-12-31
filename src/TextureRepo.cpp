#include "TextureRepo.h"

void TextureRepo::init(SDL2::Renderer renderer) {
  _renderer = renderer;

  // add this here for now - remove in future if adding multiple levels
  // pre-load common textures
  loadTexture(TextureId::FIREBALL);
  loadTexture(TextureId::BOSS_ENEMY);
  loadTexture(TextureId::EXPLOSION);
  loadTexture(TextureId::BASIC_ENEMY);
  loadTexture(TextureId::BLUE_BULLET);
  loadTexture(TextureId::HEART);
  loadTexture(TextureId::GREEN_SHIP);
  loadTexture(TextureId::BACKGROUND);
}

SDL2::Texture TextureRepo::loadTexture(unsigned int id) {
  auto        it   = _textureMap.find(id);
  const char* path = TextureId::getPath(id);
  if (it == _textureMap.end()) {
    SDL2::Texture tex = SDL2::loadTexture(path, _renderer);
    _textureMap[id]   = tex;
    return tex;
  } else {
    return it->second;
  }
}

SDL2::Texture TextureRepo::loadWithoutCache(unsigned int id) const {
  return SDL2::loadTexture(TextureId::getPath(id), _renderer);
}

SDL2::TextureData TextureRepo::loadText(const char*  text,
                                        unsigned int id) const {
  const TextParams& params = FontId::getParams(id);
  return SDL2::loadText(text,
                        params.fontPath,
                        params.size,
                        { params.r, params.g, params.b },
                        _renderer);
}

SDL2::TextureData
TextureRepo::loadTextWithBackground(const char*  text,
                                    unsigned int id,
                                    SDL2::Color  bgColor) const {
  const TextParams& params = FontId::getParams(id);
  return SDL2::loadTextWithBackground(text,
                                      params.fontPath,
                                      params.size,
                                      { params.r, params.g, params.b },
                                      bgColor,
                                      _renderer);
}

void TextureRepo::clear() {
  for (const auto& pair : _textureMap)
    SDL2::destroyTexture(pair.second);
  _textureMap.clear();
}
