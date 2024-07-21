#include "Game.h"

int main() {
      Game *SpaceGame = new Game();
      SpaceGame->run_game();
      delete SpaceGame;
      SpaceGame = nullptr;
    
    return EXIT_SUCCESS;
}
