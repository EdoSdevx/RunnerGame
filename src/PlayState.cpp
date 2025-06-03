#include "PlayState.h"
#include "Player.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameOverState.h"
#include "Game.h"
#include "PauseState.h"
#include "Collision.h"
#include <ctime>
#include <iostream>
#include <math.h>


const std::string PlayState::m_playStateID = "PLAY";

PlayState::PlayState():m_player(nullptr)
{
    m_obstacles["chunk0"].push_back({0,176,48,16});
    m_obstacles["chunk0"].push_back({112,144,48,16});
    m_obstacles["chunk0"].push_back({192,112,48,16});
    m_obstacles["chunk0"].push_back({272,128,32,32});
    m_obstacles["chunk0"].push_back({288,144,16,16});
    m_obstacles["chunk0"].push_back({336,176,48,16});

    m_obstacles["chunk1"].push_back({0,176,64,16});
    m_obstacles["chunk1"].push_back({112,112,48,48});
    m_obstacles["chunk1"].push_back({192,176,64,16});
    m_obstacles["chunk1"].push_back({240,96,16,16});
    m_obstacles["chunk1"].push_back({320,64,16,16});
    m_obstacles["chunk1"].push_back({336,176,48,16});

    m_obstacles["chunk2"].push_back({0,176,80,16});
    m_obstacles["chunk2"].push_back({144,128,32,16});
    m_obstacles["chunk2"].push_back({208,80,32,32});
    m_obstacles["chunk2"].push_back({224,96,16,32});
    m_obstacles["chunk2"].push_back({240,96,32,32});
    m_obstacles["chunk2"].push_back({240,80,32,16});
    m_obstacles["chunk2"].push_back({224,64,32,16});
    m_obstacles["chunk2"].push_back({208,176,48,16});
    m_obstacles["chunk2"].push_back({304,176,16,16});
    m_obstacles["chunk2"].push_back({336,176,48,16});

    m_obstacles["chunk3"].push_back({0,176,48,16});
    m_obstacles["chunk3"].push_back({96,128,32,32});
    m_obstacles["chunk3"].push_back({112,144,16,16});
    m_obstacles["chunk3"].push_back({176,96,16,16});
    m_obstacles["chunk3"].push_back({240,80,16,16});
    m_obstacles["chunk3"].push_back({160,176,32,16});
    m_obstacles["chunk3"].push_back({240,160,32,32});
    m_obstacles["chunk3"].push_back({256,176,16,16});
    m_obstacles["chunk3"].push_back({288,48,48,48});
    m_obstacles["chunk3"].push_back({304,80,32,16});
    m_obstacles["chunk3"].push_back({320,64,16,16});
    m_obstacles["chunk3"].push_back({320,176,64,16});

    m_obstacles["chunk4"].push_back({0,176,48,16});
    m_obstacles["chunk4"].push_back({112,144,48,16});
    m_obstacles["chunk4"].push_back({192,176,16,16});
    m_obstacles["chunk4"].push_back({256,176,16,16});
    m_obstacles["chunk4"].push_back({208,80,48,16});
    m_obstacles["chunk4"].push_back({336,176,48,16});   

    m_obstacles["chunk5"].push_back({0,176,48,16});
    m_obstacles["chunk5"].push_back({112,144,32,32});
    m_obstacles["chunk5"].push_back({192,80,48,16});
    m_obstacles["chunk5"].push_back({192,96,16,32});
    m_obstacles["chunk5"].push_back({176,176,64,16});
    m_obstacles["chunk5"].push_back({304,64,16,16});
    m_obstacles["chunk5"].push_back({288,144,16,16});
    m_obstacles["chunk5"].push_back({336,176,48,16});

    m_obstacles["chunk6"].push_back({0,176,48,16});
    m_obstacles["chunk6"].push_back({112,144,16,16});
    m_obstacles["chunk6"].push_back({160,112,16,16});
    m_obstacles["chunk6"].push_back({224,80,16,48});
    m_obstacles["chunk6"].push_back({240,112,32,16});
    m_obstacles["chunk6"].push_back({192,176,48,16});
    m_obstacles["chunk6"].push_back({272,48,16,16});
    m_obstacles["chunk6"].push_back({256,176,16,16});
    m_obstacles["chunk6"].push_back({288,176,16,16});
    m_obstacles["chunk6"].push_back({320,176,64,16});

    m_obstacles["chunk7"].push_back({0,176,48,16});
    m_obstacles["chunk7"].push_back({112,128,32,32});
    m_obstacles["chunk7"].push_back({128,144,16,16});
    m_obstacles["chunk7"].push_back({176,96,32,32});
    m_obstacles["chunk7"].push_back({192,112,16,16});
    m_obstacles["chunk7"].push_back({208,176,64,16});
    m_obstacles["chunk7"].push_back({272,80,32,16});
    m_obstacles["chunk7"].push_back({336,48,16,16});
    m_obstacles["chunk7"].push_back({320,176,64,16});

    m_collectibles["chunk0"]["coin"].push_back({144, 128, 16, 16,false, "coin"});
    m_collectibles["chunk0"]["coin"].push_back({288, 112, 16, 16,false, "coin"});

    m_collectibles["chunk1"]["carrot"].push_back({320, 48, 16, 16,false, "carrot"});
    m_collectibles["chunk1"]["coin"].push_back({240, 80, 16, 16,false, "coin"});

    m_collectibles["chunk2"]["coin"].push_back({240, 48, 16, 16,false, "coin"});
    m_collectibles["chunk2"]["apple"].push_back({304, 160, 16, 16,false, "apple"});

    m_collectibles["chunk3"]["tomato"].push_back({304, 32, 16, 16,false, "tomato"});
    m_collectibles["chunk3"]["apple"].push_back({320, 160, 16, 16,false, "apple"});

    m_collectibles["chunk4"]["carrot"].push_back({256, 160, 16, 16,false, "carrot"});
    m_collectibles["chunk4"]["apple"].push_back({240, 64, 16, 16,false, "apple"});
    

    m_collectibles["chunk5"]["apple"].push_back({304, 48, 16, 16,false, "apple"});
    m_collectibles["chunk5"]["coin"].push_back({304, 80, 16, 16,false, "coin"});


    m_collectibles["chunk6"]["coin"].push_back({256, 96, 16, 16,false, "coin"});
    m_collectibles["chunk6"]["apple"].push_back({288, 160, 16, 16,false, "apple"});
    m_collectibles["chunk6"]["carrot"].push_back({272, 32, 16, 16,false, "carrot"});

    m_collectibles["chunk7"]["apple"].push_back({256, 160, 16, 16,false, "apple"});
    m_collectibles["chunk7"]["coin"].push_back({128, 112, 16, 16,false, "coin"});
    m_collectibles["chunk7"]["tomato"].push_back({336, 32, 16, 16,false, "tomato"});

    m_score = 0;
    m_font = TTF_OpenFont("assets/arial.ttf", 20);

    if (!m_font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }


}


bool PlayState::onEnter()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    m_player = new Player(0, 120, 20, 40);

    m_chunkIDs = { "chunk0", "chunk1", "chunk2", "chunk3", "chunk4", "chunk5", "chunk6", "chunk7" };
    m_chunkSequence.clear();
    m_collectibleSequence.clear();

    for (int i = 0; i < 100; ++i)
    {
        int randomIndex = rand() % m_chunkIDs.size();
        std::string chunkToUse = m_chunkIDs[randomIndex];
        
        m_chunkSequence.push_back(chunkToUse);
        m_collectibleSequence.push_back(m_collectibles[chunkToUse]);
    }


    return true;
}

void PlayState::update(double deltaTime)
{
    if(m_player->hasFailed())
    {
        Game::Instance()->getStateMachine()->pushState(new GameOverState(m_score));
    }
    

    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->getStateMachine()->pushState(new PauseState());
        return;
    }

    int currentChunkIndex = m_player->update(deltaTime, m_obstacles, m_chunkSequence);
    if (currentChunkIndex < 0 || currentChunkIndex >= (int)m_chunkSequence.size()) return;

    auto& collectibles = m_collectibleSequence[currentChunkIndex];
    double playerRelX = m_player->getRelX();

    for (auto& typePair : collectibles)
    {
        for (auto& obj : typePair.second)
        {
            if (!obj.collected &&
                checkCollision(playerRelX, m_player->getY(), m_player->getWidth(), m_player->getHeight(),
                               obj.x, obj.y, obj.width, obj.height))
            {
                obj.collected = true;
                if(obj.type == "coin")
                {
                    m_score += 1;
                }
                else if(obj.type == "apple")
                {
                    m_score += 3;
                }
                else if(obj.type == "carrot")
                {
                    m_player->setInvincible(true);
                    m_player->setInvincibleTime(5.0);
                }
                else if(obj.type == "tomato")
                {
                    m_player->setFly(true);
                    m_player->setFlyTime(4.0);
                }
            }
        }
    }

}

void PlayState::render()
{
    TextureManager::Instance()->drawInfiniteScrolling(
        m_chunkSequence, Game::Instance()->getCameraPos(), 0, 384, 224, Game::Instance()->getRenderer());

    if (m_font)
    {
        SDL_Color white = {255, 255, 255};
        std::string scoreText = "Score: " + std::to_string(m_score);

        SDL_Surface* tempSurface = TTF_RenderText_Solid(m_font, scoreText.c_str(), white);
        if (tempSurface)
        {
            SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), tempSurface);
            if (tempTexture)
            {
                SDL_Rect textRect = {20, 10, tempSurface->w, tempSurface->h};
                SDL_RenderCopy(Game::Instance()->getRenderer(), tempTexture, nullptr, &textRect);
                SDL_DestroyTexture(tempTexture);
            }
            SDL_FreeSurface(tempSurface);
        }
        else
        {
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        }
    }

    if (m_font)
    {
        SDL_Color white = {255, 255, 255};
        
        if (m_player->isInvincible())
        {
            double timeLeft = m_player->getInvincibleTime();
            std::string invText = "Invincible: " + std::to_string(static_cast<int>(std::ceil(timeLeft))) + "s";

            SDL_Surface* invSurface = TTF_RenderText_Solid(m_font, invText.c_str(), white);
            if (invSurface)
            {
                SDL_Texture* invTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), invSurface);
                SDL_Rect invRect = {20, 30, invSurface->w, invSurface->h};
                SDL_RenderCopy(Game::Instance()->getRenderer(), invTexture, nullptr, &invRect);
                SDL_FreeSurface(invSurface);
                SDL_DestroyTexture(invTexture);
            }
        }

        if (m_player->isFlying())
        {
            double timeLeft = m_player->getFlyTime();
            std::string flyText = "Fly: " + std::to_string(static_cast<int>(std::ceil(timeLeft))) + "s";

            SDL_Surface* flySurface = TTF_RenderText_Solid(m_font, flyText.c_str(), white);
            if (flySurface)
            {
                SDL_Texture* flyTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), flySurface);
                SDL_Rect flyRect = {20, 50, flySurface->w, flySurface->h};
                SDL_RenderCopy(Game::Instance()->getRenderer(), flyTexture, nullptr, &flyRect);
                SDL_FreeSurface(flySurface);
                SDL_DestroyTexture(flyTexture);
            }
        }
    }


    int currentChunkIndex = m_player->render2();
    if (currentChunkIndex < 0 || currentChunkIndex >= (int)m_collectibleSequence.size()) return;


    auto& collectibles = m_collectibleSequence[currentChunkIndex];

    for (const auto& typePair : collectibles)
    {
        const std::string& textureID = typePair.first;

        for (const auto& obj : typePair.second)
        {
            if (!obj.collected)
            {
                int renderX = obj.x + (currentChunkIndex * 384) - Game::Instance()->getCameraPos();
                TextureManager::Instance()->draw(textureID, renderX, obj.y, obj.width, obj.height, Game::Instance()->getRenderer());
            }
        }
    }
}
bool PlayState::onExit()
{
    delete m_player;
    m_player =  nullptr;

    return true;
}