#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"

class TextRenderer {
private:
  struct TitleTextIds {
    int title;
    int subtitle;

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
  void showScore(unsigned int);

  void clearAllTexts();

  void clearCenterText();
  void clearScore();

private:
  void clearTexture(int);
};