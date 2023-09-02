#pragma once

#include "SDLWrapper.h"
#include "TextureRepo.h"

class BackgroundManager {
private:
  TextureRepo&   _texRepo;
  SDL2::Renderer _renderer;
  unsigned int   _scrollOffset;

public:
  BackgroundManager(TextureRepo&);

  void setRenderer(SDL2::Renderer);
  void updateBackground();
};