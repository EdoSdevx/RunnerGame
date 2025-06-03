#pragma once

#include "GameState.h"
#include "Button.h"
#include "SDL2/SDL_ttf.h"

class GameOverState:public GameState
{
    public:

        GameOverState(int score);
        
        void update(double deltaTime) override;
        void render() override;

        bool onEnter() override;
        bool onExit() override;

        std::string getStateID() const { return m_gameOverID; }

    private:

        TTF_Font* m_font;

        int finalScore;

        Button* m_exitButton;
        Button* m_menuButton;

        static int restartDelay;

        static void s_gameOverToExit();
        static void s_gameOverToMain();

        static const std::string m_gameOverID;
};