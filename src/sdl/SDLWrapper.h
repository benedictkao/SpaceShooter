#pragma once

#include <SDL.h>

namespace SDL2 {

  typedef SDL_Window*   Window;
  typedef SDL_Renderer* Renderer;
  typedef SDL_Texture*  Texture;
  typedef SDL_Event     Event;
  typedef SDL_Rect      Rect;

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

  TextureData loadText(const char*, int size, Renderer);

  void blit(Texture, Renderer, const Rect& dest);

  void blit(Texture, Renderer, const Rect& src, const Rect& dest);

  void destroyTexture(Texture);

  bool hasIntersect(const Rect&, const Rect&);

  void prepareScene(Renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void presentScene(Renderer);

  Uint64 elapsedTimeInMillis();

  void delay(Uint32);

  void close(Window);
} // namespace SDL2