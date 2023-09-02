#include "TextRenderer.h"
#include "Constants.h"

TextRenderer::TextRenderer(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo), _textIds({ -1, -1 }) {}

void TextRenderer::showCenterText(const char* title, const char* subtitle) {
  if (!_textIds.isEmpty())
    return;

  SDL2::TextureData tData = _texRepo.loadText(title, 48);
  int               x     = Constants::WINDOW_WIDTH / 2;
  int               y     = Constants::WINDOW_HEIGHT / 3;

  TransformComponent t;
  t.position        = { x, y };
  t.height          = tData.height;
  t.width           = tData.width;
  SpriteComponent s = { tData.tex };
  _textIds.title =
    _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();

  if (subtitle) {
    SDL2::TextureData subData = _texRepo.loadText(subtitle, 24);

    x = Constants::WINDOW_WIDTH / 2;
    y += tData.height + 20;
    t.position = { x, y };
    t.height   = subData.height;
    t.width    = subData.width;
    s.texture  = subData.tex;
    _textIds.subtitle =
      _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();
  }
}

void TextRenderer::clearCenterText() {
  clearTexture(_textIds.title);
  clearTexture(_textIds.subtitle);
  _textIds.clear();
}

void TextRenderer::clearTexture(int entity) {
  SpriteComponent& s = _em.getComponent<SpriteComponent>(entity);
  SDL2::destroyTexture(s.texture);
  _em.scheduleRemoval(entity);
}

bool TextRenderer::TextIds::isEmpty() const {
  return title == -1;
}

void TextRenderer::TextIds::clear() {
  title = -1;
}
