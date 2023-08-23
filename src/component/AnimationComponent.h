#pragma once

#include "ComponentFlag.h"
#include "SDLWrapper.h"

namespace Repetitions {
  constexpr int INFINITE{ -1 };
}

struct AnimationComponent {
  SDL2::Texture tex;
  unsigned int  width;
  unsigned int  height;
  unsigned int  currFrame;

  static constexpr ComponentFlag FLAG{ ComponentFlag::ANIMATION };
};