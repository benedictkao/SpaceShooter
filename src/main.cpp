#include "Game.h"

// can't just use main() because SDL2main will look for the function with these
// parameters specifically
int main(int argc, char* argv[]) {
  Game* game   = new Game();
  int   result = game->run();
  return result;
}