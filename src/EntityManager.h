#pragma once

#include "Components.h"
#include "SDLWrapper.h"
#include <array>
#include <stack>
#include <tuple>
#include <unordered_set>

constexpr int MAX_ENTITIES{ 50 };

class EntitySettings {
private:
  unsigned int _componentBitSet = 0;

public:
  bool hasComponents(unsigned int flags) const noexcept;
  void addComponents(unsigned int flags);
  void setComponents(unsigned int flags);
  void removeComponents(unsigned int flags);
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
                     ColliderComponent,
                     AnimationComponent,
                     SpawnComponent,
                     SpeedComponent>
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
      _em.addComponents(_entity, T::FLAG);
      _em.getComponent<T>(_entity) = component;
      return *this;
    }

    EntityInitializer& addFlags(unsigned int);

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
  bool              cancelRemoval(int entity);
  bool              isScheduledForRemoval(int entity) const;
  bool              isActive(int entity) const;
  void              removeDeadEntities();
  void              reset();
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

  bool hasComponents(int entity, unsigned int flags) const;
  void addComponents(int entity, unsigned int flags);
  void setComponents(int entity, unsigned int flags);
  void removeComponents(int entity, unsigned int flags);
};