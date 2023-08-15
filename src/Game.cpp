#include "Game.h"
#include "ColliderSystem.h"
#include "EntityCleaner.h"
#include "EntityManager.h"
#include "GunManager.h"
#include "PlayerController.h"
#include "PositionManager.h"
#include "TextureManager.h"
#include "utils/Math.h"

#if 1
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

Game::Game() : _window(nullptr), _renderer(nullptr), _running(false) {}

int Game::run() {
  const int initResult = SDL2::init();
  if (initResult != SDL2::INIT_SUCCESS)
    return GAME_INIT_ERROR::SUBSYSTEM;

  _window = SDL2::createWindow(WINDOW_TITLE);
  if (!_window)
    return GAME_INIT_ERROR::WINDOW;

  _renderer = SDL2::createRenderer(_window);
  if (!_renderer)
    return GAME_INIT_ERROR::RENDERER;

  EntityManager    entityManager;
  EntityCleaner    cleaner(entityManager);
  PositionManager  positionManager(entityManager);
  PlayerController playerController(entityManager, _renderer);
  TextureManager   textureManager(entityManager, _renderer);
  GunManager       gunManager(entityManager, _renderer);
  ColliderSystem   colliderSystem(entityManager);
  KeyboardManager  keyboardManager(playerController);

  playerController.addPlayer(400, 450);

  // TODO: put in separate class
  TransformComponent t;
  t.position = { 300, 100 };
  t.speed    = { 0, 0 };
  t.height   = 50;
  t.width    = 50;
  SpriteComponent s;
  s.texture = SDL2::loadTexture("../../../res/red-dot.png", _renderer);
  ColliderComponent c;
  c.health  = 10;
  c.mass    = 5;
  c.isEnemy = true;
  entityManager.addEntity()
    .add<TransformComponent>(t)
    .add<SpriteComponent>(s)
    .add<ColliderComponent>(c);

  _running = true;
  while (_running) {
    // main game loop

#ifdef TEST
    auto start = std::chrono::high_resolution_clock::now();
#endif
    Uint64 frameStart = SDL2::elapsedTimeInMillis();

    SDL2::prepareScene(_renderer, 28, 28, 28, 255);

    handleEvents(keyboardManager);

    positionManager.updatePositions();

    colliderSystem.calculateCollisions();

    gunManager.shootProjectiles();

    textureManager.updateTextures();

    // ui render
    SDL2::presentScene(_renderer);

    cleaner.removeDeadEntities();

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

  SDL2::close(_window);
  return 0;
}

void Game::handleEvents(KeyboardManager km) {
  SDL2::Event event;
  bool        isPressArrow = false;
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
  Uint64 sleepTime       = MILLIS_PER_FRAME - actualFrameTime;
  coercePositive(sleepTime);
  return sleepTime;
}