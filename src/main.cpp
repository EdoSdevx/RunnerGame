#include "Game.h"
#include "InputHandler.h"
#undef main

int main(int argc, char* argv[])
{

    Game::Instance()->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1152, 672, SDL_WINDOW_SHOWN);

    Uint32 lastTime = SDL_GetTicks();
    double deltaTime = 0.0;

    while(Game::Instance()->isRunning())
    {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = double((currentTime - lastTime)) / 1000.0;
        lastTime = currentTime;

        InputHandler::Instance()->update();
        Game::Instance()->update(deltaTime);
        Game::Instance()->render();
        InputHandler::Instance()->clearPressedKey();

    }

    Game::Instance()->clean();
    InputHandler::Instance()->clean();
    return 0;
}