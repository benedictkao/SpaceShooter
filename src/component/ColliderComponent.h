#pragma once

namespace Mass {
constexpr int INFINITE{-1};
}

struct ColliderComponent {
  int health;
  int mass;
  bool isEnemy;
};