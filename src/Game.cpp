#include "Game.h"
#include "TextureManager.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include "MenuState.h"

Game* Game::m_Instance = nullptr;

Game::Game():m_Window(nullptr),m_Renderer(nullptr),m_Running(false)
{
}

bool Game::init(const char* title, int windowPosX, int windowPosY, int screenWidth,
                int screenHeight, Uint32 flag)
{

    if(SDL_Init( SDL_INIT_EVERYTHING ) != 0)
    {
        std::cout<<"SDL could not be initialized! SDL_Error: "<<SDL_GetError()<<std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow(title, windowPosX, windowPosY, screenWidth, screenHeight, flag);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    TTF_Init();
    
    if(m_Window == nullptr)
    {
        std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;
        return false;
    }

    
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(m_Renderer == nullptr)
    {
        std::cout<<"Renderer could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;
        return false;
    }
    SDL_RenderSetLogicalSize(m_Renderer, 384, 224);
    SDL_RenderSetIntegerScale(m_Renderer, SDL_TRUE);
    m_Running = true;

    TextureManager::Instance()->load("assets/map1.png", "chunk0", m_Renderer);
    TextureManager::Instance()->load("assets/map2.png", "chunk1", m_Renderer);
    TextureManager::Instance()->load("assets/map3.png", "chunk2", m_Renderer);
    TextureManager::Instance()->load("assets/map4.png", "chunk3", m_Renderer);
    TextureManager::Instance()->load("assets/map5.png", "chunk4", m_Renderer);
    TextureManager::Instance()->load("assets/map6.png", "chunk5", m_Renderer);
    TextureManager::Instance()->load("assets/map7.png", "chunk6", m_Renderer);
    TextureManager::Instance()->load("assets/map8.png", "chunk7", m_Renderer);
    TextureManager::Instance()->load("assets/idle.png", "character", m_Renderer);
    TextureManager::Instance()->load("assets/den.png", "menuu", m_Renderer);
    TextureManager::Instance()->load("assets/pause.png", "pause", m_Renderer);
    TextureManager::Instance()->load("assets/coin.png", "coin", m_Renderer);
    TextureManager::Instance()->load("assets/apple.png", "apple", m_Renderer);
    TextureManager::Instance()->load("assets/carrot.png", "carrot", m_Renderer);
    TextureManager::Instance()->load("assets/tomato.png", "tomato", m_Renderer);
    TextureManager::Instance()->load("assets/gameover.png", "gameover", m_Renderer);
    
    m_cameraX = 0;



    m_StateMachine = new GameStateMachine();
    m_StateMachine->changeState(new MenuState());
    
    return true;
}

void Game::update(double deltaTime)
{
    m_StateMachine->update(deltaTime);
}

void Game::render()
{

    SDL_RenderClear(m_Renderer);

    m_StateMachine->render();
    SDL_RenderPresent(m_Renderer);

}

void Game::clean()
{
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;

    SDL_Quit();
    TTF_Quit();
}