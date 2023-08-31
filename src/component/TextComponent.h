#pragma once

#include "ComponentFlag.h"

struct TextComponent {
  const char*  text;
  unsigned int fontSize;

  static constexpr ComponentFlag FLAG{ ComponentFlag::TEXT };
};