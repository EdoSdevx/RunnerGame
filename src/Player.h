#pragma once

#include "GameObject.h"
#include "SDL2/SDL.h"
#include <vector>
#include <map>
#include <string>

class Player:public GameObject
{

    public:

        Player(double xPos, double yPos, int width, int height);

        void update(double deltaTime) override;
        int update(double deltaTime, const std::map<std::string, std::vector<Obstacle>>& m_chunkObstacles,const std::vector<std::string>& chunkSequence);
        void render() override;
        int render2();
        double getWorldX() { return m_worldX;}
        double getRelX() { return relXCurrent;}
        bool hasFailed() { return m_failed;}
        void setInvincible(bool value) { m_invincible = value; }
        void setFly(bool value) { m_fly = value;}
        void setInvincibleTime( double seconds) { m_invincibleTimeLeft = seconds;}
        void setFlyTime(double seconds) { m_flyTimeLeft = seconds;}
        bool isInvincible() { return m_invincible;}
        bool isFlying() { return m_fly; }
        double getInvincibleTime() { return m_invincibleTimeLeft;}
        double getFlyTime() { return m_flyTimeLeft;}


    private:

        int currentChunkIndex;
        int m_score;

        bool m_invincible;
        bool m_fly;

        bool m_isGrounded;
        bool m_isJumping;
        bool m_failed;

        double m_velocityY;
        double m_gravity;
        double m_jumpTime;
        double m_maxJumpTime;
        double relXCurrent;
        double m_invincibleTimeLeft;
        double m_flyTimeLeft;

        double m_worldX;
        double m_totalX;



};