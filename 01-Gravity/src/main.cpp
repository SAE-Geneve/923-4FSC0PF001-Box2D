#include <iostream>

#include "../include/game.h"

int main()
{
    Game game;
    
    // Initiate the game
    game.Init();

    // Then loop for ever
    game.Loop();

    return EXIT_SUCCESS;
}
