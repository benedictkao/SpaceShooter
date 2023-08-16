#include "EntityManager.h"
#include <iostream>

bool EntitySettings::hasComponents(int flags) const noexcept {
  return (_componentBitSet & flags) == flags;
}

void EntitySettings::addComponents(int flags) {
  _componentBitSet |= flags;
}

void EntitySettings::clear() {
  _componentBitSet = 0;
}

EntityManager::EntityManager() {
  int end = MAX_ENTITIES - 1;
  for (int i = end; i >= 0; i--)
    _freeStore.push(i);
}

EntityManager::EntityInitializer EntityManager::addEntity() {
  int entity = _freeStore.top();
  _activeEntities.insert(entity);
  _freeStore.pop();
  getComponent<EntitySettings>(entity).clear();
  EntityInitializer initializer(*this, entity);
  return initializer;
}

void EntityManager::scheduleRemoval(int entity) {
  _deadEntities.insert(entity);
}

void EntityManager::removeEntity(int id) {
  _activeEntities.erase(id);
  _freeStore.push(id);
  std::cout << "Entity " << id << " destroyed" << std::endl;
}

void EntityManager::removeDeadEntities() {
  for (int entity : _deadEntities)
    removeEntity(entity);
  _deadEntities.clear();
}

const EntityManager::EntitySet& EntityManager::getActive() {
  return _activeEntities;
}

EntityManager::EntityInitializer::EntityInitializer(EntityManager& em,
                                                    int            entity)
    : _em(em), _entity(entity) {}

int EntityManager::EntityInitializer::id() const noexcept {
  return _entity;
}