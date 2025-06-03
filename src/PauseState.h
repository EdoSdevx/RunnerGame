#pragma once

#include "GameState.h"
#include "Button.h"

class PauseState:public GameState
{
    public:

    
         void update(double deltaTime) override;
         void render() override;

         bool onEnter() override;
         bool onExit()  override;

         std::string getStateID() const { return m_pauseID; }
    
    private:

        static const std::string m_pauseID;

        Button* m_resumeButton;
        Button* m_mainButton;

        static void s_pauseToMain();
        static void s_pauseToResume();

};