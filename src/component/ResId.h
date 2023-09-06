#pragma once

//#define RELEASE

namespace TextureId {
  constexpr unsigned int GREEN_SHIP{ 0 };
  constexpr unsigned int FIREBALL{ 1 };
  constexpr unsigned int YELLOW_BULLET{ 2 };
  constexpr unsigned int BLUE_BULLET{ 3 };
  constexpr unsigned int BOSS_ENEMY{ 4 };
  constexpr unsigned int EXPLOSION{ 5 };
  constexpr unsigned int BASIC_ENEMY{ 6 };
  constexpr unsigned int BACKGROUND{ 7 };
  constexpr unsigned int HEART{ 8 };

#ifdef RELEASE
  constexpr const char* PATHS[] = { "res/texture/player.png",
                                    "res/texture/red-fireball.png",
                                    "res/texture/yellow-fireball.png",
                                    "res/texture/blue-fireball.png",
                                    "res/texture/enemy-ship.png",
                                    "res/texture/explosion-pack.png",
                                    "res/texture/basic-enemy.png",
                                    "res/texture/scrolling-bg.png",
                                    "res/texture/heart.png" };
#else
  constexpr const char* PATHS[] = { "../../../res/texture/player.png",
                                    "../../../res/texture/red-fireball.png",
                                    "../../../res/texture/yellow-fireball.png",
                                    "../../../res/texture/blue-fireball.png",
                                    "../../../res/texture/enemy-ship.png",
                                    "../../../res/texture/explosion-pack.png",
                                    "../../../res/texture/basic-enemy.png",
                                    "../../../res/texture/scrolling-bg.png",
                                    "../../../res/texture/heart.png" };
#endif

  constexpr const char* getPath(unsigned int id) {
    return PATHS[id];
  }
} // namespace TextureId

namespace MusicId {
  constexpr auto NONE{ -1 };
  constexpr auto LOAD{ 0 };
  constexpr auto BOSS{ 1 };

#ifdef RELEASE
  constexpr const char* PATHS[] = { "res/audio/cruising.mp3",
                                    "res/audio/boss.mp3" };
#else
  constexpr const char* PATHS[] = { "../../../res/audio/cruising.mp3",
                                    "../../../res/audio/boss.mp3" };
#endif

  constexpr const char* getPath(unsigned int id) {
    return PATHS[id];
  }
} // namespace MusicId

namespace SoundId {
  constexpr auto NONE{ -1 };
  constexpr auto START{ 0 };
  constexpr auto EXPLODE{ 1 };
  constexpr auto SMALL_SHOT{ 2 };
  constexpr auto FIREBALL{ 3 };
  constexpr auto PLAYER_DAMAGE{ 4 };
  constexpr auto VICTORY{ 5 };
  constexpr auto FAIL{ 6 };
  constexpr auto LOUD_EXPLODE{ 7 };

#ifdef RELEASE
  constexpr const char* PATHS[] = {
    "res/audio/game-start.mp3",    "res/audio/explode.wav",
    "res/audio/pew.wav",           "res/audio/shoot-fire.mp3",
    "res/audio/player-damage.mp3", "res/audio/victory.mp3",
    "res/audio/fail.mp3",          "res/audio/explode.wav"
  };
#else
  constexpr const char* PATHS[] = {
    "../../../res/audio/game-start.mp3",    "../../../res/audio/explode.wav",
    "../../../res/audio/pew.wav",           "../../../res/audio/shoot-fire.mp3",
    "../../../res/audio/player-damage.mp3", "../../../res/audio/victory.mp3",
    "../../../res/audio/fail.mp3",          "../../../res/audio/explode.wav"
  };
#endif

  constexpr const char* getPath(unsigned int id) {
    return PATHS[id];
  }
} // namespace SoundId

const struct AnimationParams {
  unsigned int texId;
  unsigned int width;
  unsigned int height;
  int          soundId;
};

namespace AnimationId {
  constexpr int NONE{ -1 };
  constexpr int DEFAULT_EXPLOSION{ 0 };
  constexpr int LOUD_EXPLOSION{ 1 };

  constexpr AnimationParams PARAMS[] = {
    { TextureId::EXPLOSION, 32, 32, SoundId::EXPLODE },
    { TextureId::EXPLOSION, 32, 32, SoundId::LOUD_EXPLODE }
  };

  constexpr AnimationParams getParams(unsigned int id) {
    return PARAMS[id];
  }
} // namespace AnimationId

const struct TextParams {
  unsigned int  size;
  const char*   fontPath;
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

#ifdef RELEASE
constexpr auto RETRO_FONT_PATH{ "res/font/retro.ttf" };
#else
constexpr auto RETRO_FONT_PATH{ "../../../res/font/retro.ttf" };
#endif

namespace FontId {
  constexpr int TITLE{ 0 };
  constexpr int SUBTITLE{ 1 };
  constexpr int SUBTITLE_INVERSE{ 2 };
  constexpr int SCORE{ 3 };

  constexpr TextParams PARAMS[] = { { 48, RETRO_FONT_PATH, 204, 204, 0 },
                                    { 24, RETRO_FONT_PATH, 204, 204, 0 },
                                    { 24, RETRO_FONT_PATH, 6, 18, 33 },
                                    { 18, RETRO_FONT_PATH, 220, 220, 220 } };

  constexpr TextParams getParams(unsigned int id) {
    return PARAMS[id];
  }
} // namespace FontId