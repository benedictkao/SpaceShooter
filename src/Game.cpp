#include "Game.h"
#include "utils/Math.h"

#if 0
#define TEST
#endif

#ifdef TEST
#include <chrono>
#include <iostream>
#endif

static constexpr auto WINDOW_TITLE{ "Shoot 'Em Up" };
static constexpr auto TARGET_FPS{ 40 };
static constexpr auto MILLIS_PER_FRAME{ 1000 / TARGET_FPS };
enum GAME_INIT_ERROR { SUBSYSTEM = 1, WINDOW, RENDERER };

Game::Game()
    : _playerController(_em, _texRepo)
    , _enemyManager(_em, _texRepo)
    , _keyboardManager(_playerController)
    , _systemManager(_em, _texRepo, _playerController) {}

int Game::run() {
  const int initResult = SDL2::init();
  if (initResult != SDL2::INIT_SUCCESS)
    return GAME_INIT_ERROR::SUBSYSTEM;

  SDL2::Window window = SDL2::createWindow(WINDOW_TITLE);
  if (!window)
    return GAME_INIT_ERROR::WINDOW;

  SDL2::Renderer renderer = SDL2::createRenderer(window);
  if (!renderer)
    return GAME_INIT_ERROR::RENDERER;

  _texRepo.setRenderer(renderer);
  _systemManager.setRenderer(renderer);

  _playerController.addPlayer(384, 500);
  _enemyManager.addSimpleEnemy();

  bool running = true;
  while (running) {
    // main game loop

#ifdef TEST
    auto start = std::chrono::high_resolution_clock::now();
#endif
    Uint64 frameStart = SDL2::elapsedTimeInMillis();

    SDL2::prepareScene(renderer, 28, 28, 28, 255);

    running = handleEvents(_keyboardManager);

    _systemManager.update();

    // ui render
    SDL2::presentScene(renderer);

#ifdef TEST
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_time =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
        .count();
    std::cout << elapsed_time << std::endl;
#endif

    Uint64 sleepTime = calculateSleepTime(frameStart);
    SDL2::delay(static_cast<Uint32>(sleepTime));
  }

  SDL2::close(window);
  return 0;
}

bool Game::handleEvents(KeyboardManager km) {
  SDL2::Event event;
  bool        isPressArrow = false;
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