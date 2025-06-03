#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "iostream"

const std::string MenuState::m_menuID = "MENU";

bool MenuState::onEnter()
{


    m_menuButton = new Button(128, 56, 128, 40, s_menuToPlay);
    m_exitButton = new Button(128, 134, 128, 40, s_menuToExit);

    return true;

}

bool MenuState::onExit()
{
    delete m_menuButton;
    delete m_exitButton;

    InputHandler::Instance()->reset();
    return true;
}

void MenuState::update(double deltaTime)
{
    m_menuButton->update();
    m_exitButton->update();
}

void MenuState::render()
{
    TextureManager::Instance()->draw("menuu", 0, 0, 384, 224, Game::Instance()->getRenderer());
}
void MenuState::s_menuToPlay()
{
    Game::Instance()->getStateMachine()->changeState( new PlayState ());

}

void MenuState::s_menuToExit()
{

    Game::Instance()->stopTheGame();

}