#pragma once

namespace Repetitions {
  constexpr int INFINITE{ -1 };
}

struct AnimationComponent {
  unsigned int texId;
  unsigned int width;
  unsigned int height;
  unsigned int currPos;
  int          repetitions;

  static constexpr ComponentFlag FLAG{ ComponentFlag::ANIMATION };
};