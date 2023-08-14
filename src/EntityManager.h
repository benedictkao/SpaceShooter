#pragma once

#include "SDLWrapper.h"
#include "component/Components.h"
#include <array>

constexpr int MAX_ENTITIES{50};

enum ComponentFlag { GUN = 1 << 0 };

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
  std::array<GunComponent, MAX_ENTITIES> guns;

  int addEntity();
  void removeEntity(int id);
};