#pragma once

namespace TextureId {
  constexpr unsigned int GREEN_SHIP   = 0;
  constexpr unsigned int RED_BULLET   = 1;
  constexpr unsigned int GREEN_BULLET = 2;
  constexpr unsigned int BLUE_BULLET  = 3;
  constexpr unsigned int ENEMY_SHIP   = 4;
  constexpr unsigned int EXPLOSION    = 5;
  constexpr unsigned int BASIC_ENEMY  = 6;

  constexpr const char* PATHS[] = { "../../../res/texture/player.png",
                                    "../../../res/texture/red-dot.png",
                                    "../../../res/texture/green-dot.png",
                                    "../../../res/texture/blue-dot.png",
                                    "../../../res/texture/enemy-ship.png",
                                    "../../../res/texture/explosion-pack.png",
                                    "../../../res/texture/basic-enemy.png" };

  constexpr const char* getPath(unsigned int id) {
    return PATHS[id];
  }
} // namespace TextureId

const struct AnimationParams {
  unsigned int texId;
  unsigned int width;
  unsigned int height;
};

namespace AnimationId {
  constexpr int NONE              = -1;
  constexpr int DEFAULT_EXPLOSION = 0;

  constexpr AnimationParams PARAMS[] = { { TextureId::EXPLOSION, 32, 32 } };

  constexpr AnimationParams getParams(unsigned int id) {
    return PARAMS[id];
  }
} // namespace AnimationId