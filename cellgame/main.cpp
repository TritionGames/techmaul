#include"Game.h"

int main()
{
    Game game;

    // run the program as long as the window is open
    while (game.running)
    {
        game.update();
        game.render();
    }

    game.clear();

    return 0;
}