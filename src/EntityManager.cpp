#include "EntityManager.h"
#include <iostream>

bool EntitySettings::hasComponents(unsigned int flags) const noexcept {
  return (_componentBitSet & flags) == flags;
}

void EntitySettings::addComponents(unsigned int flags) {
  _componentBitSet |= flags;
}

void EntitySettings::removeComponents(unsigned int flags) {
  _componentBitSet &= ~flags;
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

bool EntityManager::hasComponents(int entity, unsigned int flags) const {
  return getComponent<EntitySettings>(entity).hasComponents(flags);
}

void EntityManager::addComponents(int entity, unsigned int flags) {
  getComponent<EntitySettings>(entity).addComponents(flags);
}

void EntityManager::removeComponents(int entity, unsigned int flags) {
  getComponent<EntitySettings>(entity).removeComponents(flags);
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

EntityManager::EntityInitializer&
EntityManager::EntityInitializer::setEnemy(bool isEnemy) {
  if (isEnemy)
    _em.addComponents(_entity, ComponentFlag::ENEMY);
  else
    _em.removeComponents(_entity, ComponentFlag::ENEMY);
  return *this;
}

int EntityManager::EntityInitializer::id() const noexcept {
  return _entity;
}