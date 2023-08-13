#pragma once

#include "SDLWrapper.h"
#include "component/Components.h"
#include <array>

constexpr int MAX_ENTITIES{5};

enum ComponentFlag { SPRITE = 1 << 0, TRANSFORM = 1 << 1 };

class EntitySettings {
private:
  int _componentBitSet;

public:
  bool hasComponents(int flags) const noexcept;
  void setComponents(int flags);
};

struct EntityManager {
  int num_entities = 0;
  std::array<EntitySettings, MAX_ENTITIES> settings;
  std::array<SpriteComponent, MAX_ENTITIES> sprites;
  std::array<TransformComponent, MAX_ENTITIES> transforms;

  int addEntity();
};