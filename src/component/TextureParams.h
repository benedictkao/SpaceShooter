#pragma once

enum TextureKey { PLAYER_SPRITE, NORMAL_AMMO };

struct TextureParams {
  TextureKey  key;
  const char* path;
};