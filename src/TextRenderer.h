#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"
#include "TextureRepo.h"
#include <array>

class TextRenderer {
private:
  struct TitleTextIds {
    int                title;
    std::array<int, 3> subtitles;
    int                selectedOption;

    bool isEmpty() const;
    void clear();
  };

  EntityManager& _em;
  TextureRepo&   _texRepo;
  TitleTextIds   _textIds;
  int            _scoreId;

public:
  TextRenderer(EntityManager&, TextureRepo&);

  void showCenterText(const char* title, const char* subtitle);
  void showOptionText(const char*                title,
                      std::array<const char*, 3> options,
                      unsigned int               selection);
  void showEmptyScore();
  void updateScore(unsigned int) const;

  void clearAllTexts();

  void clearCenterText();
  void clearScore();

private:
  SDL2::TextureData getTitleTexData(const char*);
  SDL2::TextureData getSubtitleTexData(const char*);
  SDL2::TextureData getSelectedOptionTexData(const char*);
  void              clearTexture(int);
};