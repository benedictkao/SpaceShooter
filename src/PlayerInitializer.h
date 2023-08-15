#pragma once

#include "component/Components.h"
#include "SDLWrapper.h"

static constexpr int  PLAYER_SPEED{ 8 };
static constexpr auto PLAYER_SPRITE_PATH{ "../../../res/player.png" };

static void initSprite(SpriteComponent& sprite, SDL2::Renderer renderer) {
  sprite.texture = SDL2::loadTexture(PLAYER_SPRITE_PATH, renderer);
}

static void initTransform(TransformComponent& transform,
                          SDL2::Renderer      renderer) {
  transform.position = { 400, 450 };
  transform.speed    = { 0, 0 };
  transform.height   = 32;
  transform.width    = 32;
}

static void initGun(GunComponent& gun, SDL2::Renderer renderer) {
  gun.ammo      = Ammo::Normal;
  gun.direction = Direction::UP;
  gun.coolDown  = 0;
  gun.isFiring  = false;
}

static void initCollider(ColliderComponent& collider, SDL2::Renderer renderer) {
  collider.health  = 5;
  collider.mass    = Mass::INFINITE;
  collider.isEnemy = false;
}