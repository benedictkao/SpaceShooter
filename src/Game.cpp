#include "Game.h"
#include "EntityManager.h"
#include "Math.h"
#include "PlayerController.h"
#include "PositionManager.h"
#include "TextureManager.h"

static constexpr auto TARGET_FPS{40};
static constexpr auto MILLIS_PER_FRAME{1000 / TARGET_FPS};
enum GAME_INIT_ERROR { SUBSYSTEM = 1, WINDOW, RENDERER };

Game::Game() : _window(nullptr), _renderer(nullptr), _running(false) {}

int Game::run() {
  const int initResult = SDL2::init();
  if (initResult != SDL2::INIT_SUCCESS)
    return GAME_INIT_ERROR::SUBSYSTEM;

  _window = SDL2::createWindow("Shoot 'Em Up");
  if (!_window)
    return GAME_INIT_ERROR::WINDOW;

  _renderer = SDL2::createRenderer(_window);
  if (!_renderer)
    return GAME_INIT_ERROR::RENDERER;

  EntityManager entityManager;
  PositionManager positionManager(entityManager);
  PlayerController playerController(entityManager, _renderer);
  TextureManager textureManager(entityManager, _renderer);
  KeyboardManager keyboardManager(playerController);

  playerController.addPlayer(400, 450);

  _running = true;
  while (_running) {
    // main game loop

    Uint64 frameStart = SDL2::elapsedTimeInMillis();

    SDL2::prepareScene(_renderer, 28, 28, 28, 255);

    handleEvents(keyboardManager);

    positionManager.updatePositions();

    textureManager.updateTextures();

    // ui render
    SDL2::presentScene(_renderer);

    Uint64 sleepTime = calculateSleepTime(frameStart);
    SDL2::delay(sleepTime);
  }

  SDL2::close(_window);
  return 0;
}

void Game::handleEvents(KeyboardManager km) {
  SDL2::Event event;
  bool isPressArrow = false;
  while (SDL2::pollEvent(&event)) {
    switch (event.type) { // add other events below here
    case SDL_QUIT:
      _running = false;
      break;
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
}

Uint64 Game::calculateSleepTime(Uint64 frameStart) {
  Uint64 actualFrameTime = frameStart - SDL2::elapsedTimeInMillis();
  Uint64 sleepTime = maxUnsigned(MILLIS_PER_FRAME - actualFrameTime, 0);
  return sleepTime;
}