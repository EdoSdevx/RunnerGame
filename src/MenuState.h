#pragma once

#include "GameState.h"
#include "Button.h"

class MenuState:public GameState
{

    public:

        void update(double deltaTime) override;
	    void render() override;

	    bool onEnter() override;
	    bool onExit()  override;

        std::string getStateID() const { return m_menuID; }
        
    private:

        Button* m_menuButton;
        Button* m_exitButton;

        static void s_menuToPlay();
        static void s_menuToExit();

        static const std::string m_menuID;

};