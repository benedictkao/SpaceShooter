#include "Game.h"
#include "Constants.h"
#include "utils/Math.h"

#ifndef NDEBUG
#define TIME
#endif

#ifdef TIME
#include <chrono>
#include <iostream>
#endif

static constexpr auto TARGET_FPS{ 40 };
static constexpr auto MILLIS_PER_FRAME{ 1000 / TARGET_FPS };
enum GAME_INIT_ERROR { SUBSYSTEM = 1, WINDOW, RENDERER };

Game::Game()
    : _playerController(_em, _texRepo)
    , _textRenderer(_em, _texRepo)
    , _levelManager(_em,
                    _playerController,
                    _texRepo,
                    _textRenderer,
                    _musicManager)
    , _keyboardManager(_playerController, _levelManager, _musicManager)
    , _systemManager(_em,
                     _texRepo,
                     _playerController,
                     _textRenderer,
                     _levelManager,
                     _musicManager) {}

int Game::run() {
  const int initResult = SDL2::init();
  if (initResult != SDL2::INIT_SUCCESS)
    return GAME_INIT_ERROR::SUBSYSTEM;

  SDL2::Window window = SDL2::createWindow(Constants::GAME_NAME);
  if (!window)
    return GAME_INIT_ERROR::WINDOW;

  SDL2::Renderer renderer = SDL2::createRenderer(window);
  if (!renderer)
    return GAME_INIT_ERROR::RENDERER;

  _texRepo.init(renderer);
  _systemManager.init(renderer);

  bool running = true;
  while (running) {
    // main game loop

#ifdef TIME
    auto start = std::chrono::high_resolution_clock::now();
#endif
    Uint64 frameStart = SDL2::elapsedTimeInMillis();

    SDL2::prepareScene(renderer, 28, 28, 28, 255);

    running = handleEvents(_keyboardManager);

    _systemManager.update();

    // ui render
    SDL2::presentScene(renderer);

#ifdef TIME
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_time =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
        .count();
    std::cout << elapsed_time << std::endl;
#endif

    Uint64 sleepTime = calculateSleepTime(frameStart);
    SDL2::delay(static_cast<Uint32>(sleepTime));
  }

  _texRepo.clear();
  SDL2::close(window, renderer);
  return 0;
}

bool Game::handleEvents(KeyboardManager km) {
  SDL2::Event event;
  while (SDL2::pollEvent(&event)) {
    switch (event.type) { // add other events below here
      case SDL_QUIT:
        return false;
      case SDL_KEYDOWN:
        km.handleKeydownEvent(event);
        break;
      case SDL_KEYUP:
        km.handleKeyupEvent(event);
        break;
      default:
        break;
    }
  }
  return true;
}

Uint64 Game::calculateSleepTime(Uint64 frameStart) {
  Uint64 actualFrameTime = frameStart - SDL2::elapsedTimeInMillis();
  Uint64 sleepTime       = MILLIS_PER_FRAME - actualFrameTime;
  coercePositive(sleepTime);
  return sleepTime;
}