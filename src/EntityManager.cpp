#include "EntityManager.h"

bool EntitySettings::hasComponents(int flags) const noexcept {
  return _componentBitSet & flags == _componentBitSet;
}

void EntitySettings::setComponents(int flags) { _componentBitSet |= flags; }

int EntityManager::addEntity() { return num_entities++; }