#include "EntityManager.h"
#include <iostream>

bool EntitySettings::hasComponents(int flags) const noexcept {
  return (_componentBitSet & flags) == flags;
}

void EntitySettings::addComponents(int flags) {
  _componentBitSet |= flags;
}

int EntityManager::addEntity() {
  return num_entities++;
}

void EntityManager::removeEntity(int id) {
  if (id >= num_entities)
    return;

  --num_entities;

  if (id < num_entities) {
    settings[id]   = settings[num_entities];
    sprites[id]    = sprites[num_entities];
    transforms[id] = transforms[num_entities];
    guns[id]       = guns[num_entities];
    colliders[id]  = colliders[num_entities];
  }
  std::cout << "Entity " << id << " destroyed\n";
}