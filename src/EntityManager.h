#pragma once

#include "SDLWrapper.h"
#include "component/Components.h"
#include <array>
#include <stack>
#include <tuple>
#include <unordered_set>

constexpr int MAX_ENTITIES{ 50 };

class EntitySettings {
private:
  int _componentBitSet = 0;

public:
  bool hasComponents(int flags) const noexcept;
  void addComponents(int flags);
  void clear();
};

template <typename... Types>
using array_tuple = std::tuple<std::array<Types, MAX_ENTITIES>...>;

class EntityManager {

public:
  typedef array_tuple<EntitySettings,
                      SpriteComponent,
                      TransformComponent,
                      GunComponent,
                      ColliderComponent>
                                  component_arrays;
  typedef std::stack<int>         entity_stack;
  typedef std::unordered_set<int> entity_set;
  typedef bool (*remove_checker)(int, EntityManager&);

  class EntityInitializer {
  private:
    EntityManager& _em;
    int            _entity;

  public:
    EntityInitializer(EntityManager&, int entity);

    template <typename T>
    EntityInitializer& add(const T& component) {
      EntitySettings& settings = _em.getComponent<EntitySettings>(_entity);
      settings.addComponents(T::FLAG);
      _em.getComponent<T>(_entity) = component;
      return *this;
    }

    int id() const noexcept;
  };

private:
  entity_stack     _freeStore;
  entity_set       _activeEntities;
  component_arrays _componentData;

public:
  EntityManager();

  EntityInitializer addEntity();
  void              removeEntity(int id);
  void              removeByCondition(remove_checker);
  const entity_set& getActive();

  template <typename T>
  T& getComponent(int entity) {
    return std::get<std::array<T, MAX_ENTITIES>>(_componentData)[entity];
  }

  template <typename T>
  const T& getComponent(int entity) const {
    return std::get<std::array<T, MAX_ENTITIES>>(_componentData)[entity];
  }
};