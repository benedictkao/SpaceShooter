#include "TextRenderer.h"
#include "Constants.h"
#include <string>

TextRenderer::TextRenderer(EntityManager& em, TextureRepo& texRepo)
    : _em(em)
    , _texRepo(texRepo)
    , _textIds({ -1, { -1, -1, -1 }, 0 })
    , _scoreId(-1) {}

void TextRenderer::showCenterText(const char* title, const char* subtitle) {
  if (!_textIds.isEmpty())
    return;

  SDL2::TextureData tData = getTitleTexData(title);
  int               x     = Constants::WINDOW_WIDTH / 2;
  int               y     = Constants::WINDOW_HEIGHT / 3;

  TransformComponent t;
  t.position        = { x, y };
  t.height          = tData.height;
  t.width           = tData.width;
  SpriteComponent s = { tData.tex };
  _textIds.title =
    _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();

  SDL2::TextureData subData = getSubtitleTexData(subtitle);

  x = Constants::WINDOW_WIDTH / 2;
  y += tData.height + 20;
  t.position = { x, y };
  t.height   = subData.height;
  t.width    = subData.width;
  s.texture  = subData.tex;
  _textIds.subtitles[0] =
    _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();
}

// make sure that other center text is not showing or this will cause issues
void TextRenderer::showOptionText(const char*                title,
                                  std::array<const char*, 3> options,
                                  unsigned int               selection) {
  if (_textIds.isEmpty()) {
    SDL2::TextureData tData = getTitleTexData(title);
    int               x     = Constants::WINDOW_WIDTH / 2;
    int               y     = Constants::WINDOW_HEIGHT / 3;

    TransformComponent t;
    t.position        = { x, y };
    t.height          = tData.height;
    t.width           = tData.width;
    SpriteComponent s = { tData.tex };
    _textIds.title =
      _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();

    x = Constants::WINDOW_WIDTH / 2;
    y += tData.height + 20;

    for (int i = 0; i < 3; ++i) {
      SDL2::TextureData subData = i == selection ?
                                    getSelectedOptionTexData(options[i]) :
                                    getSubtitleTexData(options[i]);
      t.position                = { x, y };
      t.height                  = subData.height;
      t.width                   = subData.width;
      s.texture                 = subData.tex;
      _textIds.subtitles[i] =
        _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();
      y += subData.height + 20;
    }
  } else if (selection != _textIds.selectedOption) {
    // options is already showing, update existing texts;
    _textIds.selectedOption = selection;

    for (int i = 0; i < 3; ++i) {
      SpriteComponent& sprite =
        _em.getComponent<SpriteComponent>(_textIds.subtitles[i]);
      SDL2::destroyTexture(sprite.texture);
      SDL2::TextureData subData = i == selection ?
                                    getSelectedOptionTexData(options[i]) :
                                    getSubtitleTexData(options[i]);
      sprite.texture            = subData.tex;
    }
  }
}

void TextRenderer::showEmptyScore() {
  SDL2::TextureData  tData = _texRepo.loadText("0", FontId::SCORE);
  int                x     = 20 + tData.width / 2;
  int                y     = 600;
  TransformComponent t;
  t.position        = { x, y };
  t.height          = tData.height;
  t.width           = tData.width;
  SpriteComponent s = { tData.tex };
  _scoreId =
    _em.addEntity().add<TransformComponent>(t).add<SpriteComponent>(s).id();
}

// This is expensive!! Should create a texture sheet and cache it for long
// term solution
void TextRenderer::updateScore(unsigned int score) const {
  std::string       str   = std::to_string(score);
  SDL2::TextureData tData = _texRepo.loadText(str.c_str(), FontId::SCORE);
  int               x     = 20 + tData.width / 2;
  int               y     = 600;

  TransformComponent& t = _em.getComponent<TransformComponent>(_scoreId);
  t.width               = tData.width;
  t.position.x          = x;

  SpriteComponent& s = _em.getComponent<SpriteComponent>(_scoreId);
  SDL2::destroyTexture(s.texture);
  s.texture = tData.tex;
}

void TextRenderer::clearAllTexts() {
  clearCenterText();
  clearScore();
}

void TextRenderer::clearCenterText() {
  if (_textIds.title != -1)
    clearTexture(_textIds.title);
  for (int i : _textIds.subtitles)
    if (i != -1)
      clearTexture(i);
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

SDL2::TextureData TextRenderer::getTitleTexData(const char* text) {
  return _texRepo.loadText(text, FontId::TITLE);
}

SDL2::TextureData TextRenderer::getSubtitleTexData(const char* text) {
  return _texRepo.loadText(text, FontId::SUBTITLE);
}

SDL2::TextureData TextRenderer::getSelectedOptionTexData(const char* text) {
  return _texRepo.loadTextWithBackground(text,
                                         FontId::SUBTITLE_INVERSE,
                                         { 204, 204, 0 });
}

bool TextRenderer::TitleTextIds::isEmpty() const {
  return title == -1;
}

void TextRenderer::TitleTextIds::clear() {
  title          = -1;
  subtitles      = { -1, -1, -1 };
  selectedOption = 0;
}
