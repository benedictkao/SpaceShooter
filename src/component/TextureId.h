#pragma once

namespace TextureId {
  constexpr unsigned int GREEN_SHIP  = 0;
  constexpr unsigned int RED_BULLET  = 1;
  constexpr unsigned int BLUE_BULLET = 2;
  constexpr unsigned int ENEMY_SHIP  = 3;
  constexpr unsigned int EXPLOSION   = 4;

  constexpr const char* PATHS[] = { "../../../res/player.png",
                                    "../../../res/red-dot.png",
                                    "../../../res/blue-dot.png",
                                    "../../../res/enemy-ship.png",
                                    "../../../res/explosion-pack.png" };

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