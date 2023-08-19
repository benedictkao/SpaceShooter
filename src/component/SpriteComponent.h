#pragma once

#include "SDLWrapper.h"
#include "ComponentFlag.h"

struct SpriteComponent {
  SDL2::Texture texture;

  static constexpr ComponentFlag FLAG{ ComponentFlag::SPRITE };
};