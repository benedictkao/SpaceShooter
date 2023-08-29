#pragma once

#include "EntityManager.h"
#include "TextureRepo.h"

class TextRenderer {
private:
  struct TextIds {
    int title;
    int subtitle;

    bool isEmpty() const;
    void clear();
  };

  EntityManager& _em;
  TextureRepo&   _texRepo;
  TextIds        _textIds;

public:
  TextRenderer(EntityManager&, TextureRepo&);

  void showCenterText(const char* title, const char* subtitle);
  void clearCenterText();

private:
  void clearTexture(int);
};