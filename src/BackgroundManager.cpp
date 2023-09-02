#include "BackgroundManager.h"
#include "Constants.h"

BackgroundManager::BackgroundManager(TextureRepo& texRepo)
    : _texRepo(texRepo)
    , _renderer(0)
    , _scrollOffset(Constants::WINDOW_HEIGHT) {}

void BackgroundManager::setRenderer(SDL2::Renderer renderer) {
  _renderer = renderer;
}

void BackgroundManager::updateBackground() {
  SDL2::Texture tex = _texRepo.loadTexture(TextureId::BACKGROUND);
  SDL2::Rect    dest;
  dest.w = Constants::WINDOW_WIDTH;
  dest.h = Constants::WINDOW_HEIGHT;
  dest.x = 0;
  dest.y = 0;
  SDL2::Rect src;
  src.w = Constants::WINDOW_WIDTH;
  src.h = Constants::WINDOW_HEIGHT;
  src.x = 0;
  src.y = _scrollOffset;
  SDL2::blit(tex, _renderer, src, dest);

  if (_scrollOffset == 0)
    _scrollOffset = Constants::WINDOW_HEIGHT;
  else
    --_scrollOffset;
}