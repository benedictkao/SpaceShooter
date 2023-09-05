#include "TextRenderer.h"
#include "Constants.h"
#include <string>

TextRenderer::TextRenderer(EntityManager& em, TextureRepo& texRepo)
    : _em(em), _texRepo(texRepo), _textIds({ -1, -1 }), _scoreId(-1) {}

void TextRenderer::showCenterText(const char* title, const char* subtitle) {
  if (!_textIds.isEmpty())
    return;

  SDL2::TextureData tData = _texRepo.loadText(title, FontId::TITLE);
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
    SDL2::TextureData subData = _texRepo.loadText(subtitle, FontId::SUBTITLE);

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

void TextRenderer::showScore(unsigned int score) {
  std::string       str   = std::to_string(score);
  SDL2::TextureData tData = _texRepo.loadText(str.c_str(), FontId::SCORE);
  int               x     = 20 + tData.width / 2;
  int               y     = 600;

  if (_scoreId == -1) {
    TransformComponent t;
    t.position        = { x, y };
    t.height          = tData.height;
    t.width           = tData.width;
    SpriteComponent s = { tData.tex };
    _scoreId =
      _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();
  } else {
    TransformComponent& t = _em.getComponent<TransformComponent>(_scoreId);
    t.width               = tData.width;
    t.position.x          = x;

    SpriteComponent& s = _em.getComponent<SpriteComponent>(_scoreId);
    SDL2::destroyTexture(s.texture);
    s.texture = tData.tex;
  }
}

void TextRenderer::clearAllTexts() {
  clearCenterText();
  clearScore();
}

void TextRenderer::clearCenterText() {
  clearTexture(_textIds.title);
  clearTexture(_textIds.subtitle);
  _textIds.clear();
}

void TextRenderer::clearScore() {
  if (_scoreId != -1) {
    clearTexture(_scoreId);
    _scoreId = -1;
  }
}

void TextRenderer::clearTexture(int entity) {
  SpriteComponent& s = _em.getComponent<SpriteComponent>(entity);
  SDL2::destroyTexture(s.texture);
  _em.scheduleRemoval(entity);
}

bool TextRenderer::TitleTextIds::isEmpty() const {
  return title == -1;
}

void TextRenderer::TitleTextIds::clear() {
  title = -1;
}
