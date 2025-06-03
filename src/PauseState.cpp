#include "PauseState.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuState.h"

const std::string PauseState::m_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{

    Game::Instance()->getStateMachine()->changeState( new MenuState());

}

void PauseState::s_pauseToResume()
{

    Game::Instance()->getStateMachine()->popState();

}

bool PauseState::onEnter()
{

    m_resumeButton = new Button(176, 64, 16, 16, s_pauseToResume);
    m_mainButton = new Button(176, 136, 16, 16, s_pauseToMain);
    return true;
}



bool PauseState::onExit()
{
    delete m_resumeButton;
    delete m_mainButton;

    InputHandler::Instance()->reset();
    return true;
}

void PauseState::update(double deltaTime)
{
    m_resumeButton->update();
    m_mainButton->update();

}

void PauseState::render()
{
    TextureManager::Instance()->draw("pause", 0, 0, 384, 224, Game::Instance()->getRenderer());
    

}