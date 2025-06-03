#include "GameOverState.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "MenuState.h"
#include "iostream"

const std::string GameOverState::m_gameOverID = "GAMEOVER";


GameOverState::GameOverState(int score)
{
    finalScore = score;
    m_font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 35);
}

bool GameOverState::onEnter()
{


    m_exitButton = new Button(93, 174, 198, 34, s_gameOverToExit);
    m_menuButton = new Button(93, 132, 198, 34, s_gameOverToMain);

    return true;

}

bool GameOverState::onExit()
{
    delete m_exitButton;
    delete m_menuButton;

    InputHandler::Instance()->reset();
    return true;
}

void GameOverState::update(double deltaTime)
{
    m_exitButton->update();
    m_menuButton->update();
}

void GameOverState::render()
{
    TextureManager::Instance()->draw("gameover", 0, 0, 384, 224, Game::Instance()->getRenderer());

    if (!m_font) return;

    SDL_Color white = {255, 0, 255};
    std::string scoreText = "Final Score: " + std::to_string(finalScore);

    SDL_Surface* tempSurface = TTF_RenderText_Solid(m_font, scoreText.c_str(), white);
    if (!tempSurface) return;

    SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), tempSurface);
    if (!tempTexture)
    {
        SDL_FreeSurface(tempSurface);
        return;
    }

    SDL_Rect textRect = {40, 0, tempSurface->w, tempSurface->h};
    SDL_RenderCopy(Game::Instance()->getRenderer(), tempTexture, nullptr, &textRect);

    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
}

void GameOverState::s_gameOverToExit()
{
    Game::Instance()->stopTheGame();

}

void GameOverState::s_gameOverToMain()
{

    Game::Instance()->getStateMachine()->changeState( new MenuState());

}


