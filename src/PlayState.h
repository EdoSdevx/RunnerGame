#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include "SDL2/SDL_ttf.h"


struct Collectible
{

    double x,y;
    int width,height;
    bool collected = false;
    std::string type;
};

class PlayState:public GameState
{

    public:

        PlayState();
        
        void update(double deltaTime) override;
        void render() override;

        bool onEnter() override;
        bool onExit() override;

        std::string getStateID() const { return m_playStateID; }

    private:

        TTF_Font* m_font;
        static const std::string m_playStateID;

        Player* m_player;

        int m_score;


        std::map<std::string, std::vector<Obstacle>> m_obstacles;
        std::vector<std::string> m_chunkIDs;
        std::vector<std::string> m_chunkSequence;
        std::map<std::string, std::map<std::string, std::vector<Collectible>>> m_collectibles;
        std::vector<std::map<std::string, std::vector<Collectible>>> m_collectibleSequence;






};