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
  void          setRenderer(SDL2::Renderer);
  SDL2::Texture loadTexture(unsigned int id);
  SDL2::Texture loadWithoutCache(unsigned int id);

  SDL2::TextureData loadText(const char*, int size);

  void clear();
};