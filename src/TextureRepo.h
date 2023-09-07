#pragma once

#include "Components.h"
#include "SDLWrapper.h"
#include <unordered_map>

class TextureRepo {
public:
  typedef std::unordered_map<int, SDL2::Texture> TextureMap;

private:
  SDL2::Renderer _renderer;
  TextureMap     _textureMap;


public:
  void          init(SDL2::Renderer);
  SDL2::Texture loadTexture(unsigned int id);
  SDL2::Texture loadWithoutCache(unsigned int id) const;

  SDL2::TextureData loadText(const char* text, unsigned int id) const;
  SDL2::TextureData loadTextWithBackground(const char*  text,
                                           unsigned int id,
                                           SDL2::Color  bgColor) const;

  void clear();
};