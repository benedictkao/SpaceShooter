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
  EntityInitializer initializer(*this, entity);
  return initializer;
}

void EntityManager::removeEntity(int id) {
  getComponent<EntitySettings>(id).clear();
  SDL2::Texture tex = getComponent<SpriteComponent>(id).texture;
  SDL2::destroyTexture(tex);
  _activeEntities.erase(id);
  _freeStore.push(id);
  std::cout << "Entity " << id << " destroyed" << std::endl;
}

void EntityManager::removeByCondition(remove_checker shouldRemove) {
  auto it = _activeEntities.begin();
  while (it != _activeEntities.end()) {
    if (shouldRemove(*it, *this)) {
      // TODO: put in separate fun
      _freeStore.push(*it);
      getComponent<EntitySettings>(*it).clear();
      SDL2::Texture tex = getComponent<SpriteComponent>(*it).texture;
      SDL2::destroyTexture(tex);
      std::cout << "Entity " << *it << " destroyed" << std::endl;
      it = _activeEntities.erase(it);
    } else {
      ++it;
    }
  }
}

const EntityManager::entity_set& EntityManager::getActive() {
  return _activeEntities;
}

EntityManager::EntityInitializer::EntityInitializer(EntityManager& em,
                                                    int            entity)
    : _em(em), _entity(entity) {}

int EntityManager::EntityInitializer::id() const noexcept {
  return _entity;
}