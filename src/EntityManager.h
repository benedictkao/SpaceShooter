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
using ArrayTuple = std::tuple<std::array<Types, MAX_ENTITIES>...>;

class EntityManager {

public:
  typedef ArrayTuple<EntitySettings,
                     SpriteComponent,
                     TransformComponent,
                     GunComponent,
                     ColliderComponent>
                                  ComponentArrays;
  typedef std::stack<int>         EntityStack;
  typedef std::unordered_set<int> EntitySet;

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
  EntityStack     _freeStore;
  EntitySet       _activeEntities;
  EntitySet       _deadEntities;
  ComponentArrays _componentData;

public:
  EntityManager();

  EntityInitializer addEntity();
  void              scheduleRemoval(int entity);
  void              removeDeadEntities();
  const EntitySet&  getActive();

private:
  void removeEntity(int id);

public:
  template <typename T>
  T& getComponent(int entity) {
    return std::get<std::array<T, MAX_ENTITIES>>(_componentData)[entity];
  }

  template <typename T>
  const T& getComponent(int entity) const {
    return std::get<std::array<T, MAX_ENTITIES>>(_componentData)[entity];
  }
};