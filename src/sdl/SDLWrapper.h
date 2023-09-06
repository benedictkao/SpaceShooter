#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

namespace SDL2 {

  typedef SDL_Window*   Window;
  typedef SDL_Renderer* Renderer;
  typedef SDL_Texture*  Texture;
  typedef SDL_Event     Event;
  typedef SDL_Rect      Rect;
  typedef SDL_Color     Color;

  typedef Mix_Music* Music;
  typedef Mix_Chunk* Sound;

  struct TextParams {
    const char*  text;
    unsigned int size;
    Color        color;
  };

  struct TextureData {
    Texture tex;
    int     width;
    int     height;
  };

  constexpr auto INIT_SUCCESS{ 0 };

  Uint32 init();

  Window createWindow(const char*);

  Renderer createRenderer(Window);

  Uint32 pollEvent(Event*);

  Texture loadTexture(const char*, Renderer);

  TextureData loadText(const char*  text,
                       const char*  fontPath,
                       unsigned int size,
                       const Color& textColor,
                       Renderer);

    TextureData loadTextWithBackground(const char*  text,
                       const char*  fontPath,
                       unsigned int size,
                       const Color& textColor,
                       const Color& bgColor,
                       Renderer);

  void blit(Texture, Renderer, const Rect& dest);

  void blit(Texture, Renderer, const Rect& src, const Rect& dest);

  void destroyTexture(Texture);

  void freeMusic(Music);

  void freeSound(Sound);

  bool hasIntersect(const Rect&, const Rect&);

  void prepareScene(Renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void presentScene(Renderer);

  Music loadMusic(const char*);

  Sound loadSound(const char*);

  void playMusic(Music);

  void playSound(Sound);

  void stopMusic();

  void stopSounds();

  int setMusicVolume(int);

  int setSoundVolume(Sound, int);

  int setSoundVolume(int);

  Uint64 elapsedTimeInMillis();

  void delay(Uint32);

  void quit();

  void close(Window, Renderer);
} // namespace SDL2