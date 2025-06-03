#pragma once

#include <string>

enum game_states
{

    MENU = 0,
    PLAY = 1,
    GAMEOVER = 2
};


class GameState
{
    public:

        virtual ~GameState() {}

        virtual void update(double deltaTime) = 0;
        virtual void render() = 0;

        virtual bool onEnter() = 0;
        virtual bool onExit() = 0;

        virtual std::string getStateID() const = 0;
 
};