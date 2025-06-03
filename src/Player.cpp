#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Collision.h"
#include "GameOverState.h"
#include <cmath>

Player::Player(double xPos, double yPos, int width, int height)
    : GameObject(xPos, yPos, width, height)
{
    m_isGrounded = true;
    m_isJumping = false;
    m_velocityY = 220;
    m_worldX = 0;
    m_maxJumpTime = 0.35;
    m_gravity = 220;
    m_failed = false;
    m_score = 0;
    m_invincible = false;
    m_fly = false;
    m_invincibleTimeLeft = 0;
    m_flyTimeLeft = 0;
}

int Player::update(double deltaTime,
                    const std::map<std::string, std::vector<Obstacle>>& chunkObstacles,
                    const std::vector<std::string>& chunkSequence)
{
    if(m_invincible)
    {
        m_invincibleTimeLeft -= deltaTime;
        if(m_invincibleTimeLeft <= 0)
        {
            m_invincible = false;
            m_invincibleTimeLeft = 0;
        }
    }
    if(m_fly)
    {
        m_flyTimeLeft -= deltaTime;
        if(m_flyTimeLeft <= 0)
        {
            m_fly = false;
            m_flyTimeLeft = 0;
        }
    }
    double screenWidth = 384;
    double speed = 120;
    double nextX = m_worldX + speed * deltaTime;

    int chunkWidth = 384;
    int totalChunks = static_cast<int>(chunkSequence.size());
    currentChunkIndex = static_cast<int>(nextX / chunkWidth) % totalChunks;
    int nextChunkIndex = (currentChunkIndex + 1) % totalChunks;

    std::string currentChunkID = chunkSequence[currentChunkIndex];
    std::string nextChunkID = chunkSequence[nextChunkIndex];

    const auto& currentObstacles = chunkObstacles.at(currentChunkID);
    const auto& nextObstacles = chunkObstacles.at(nextChunkID);

    relXCurrent = nextX - (currentChunkIndex * chunkWidth);
    double relXNext = nextX - (nextChunkIndex * chunkWidth);

    if (m_x < screenWidth / 2.0)
    {
        m_x += speed * deltaTime;
    }
    else
    {
        Game::Instance()->setCameraPos(int(m_worldX - screenWidth / 2.0));
    }

    for (const auto& obs : currentObstacles)
    {
        if (checkCollision(relXCurrent, m_y, m_width, m_height,
                           obs.x, obs.y, obs.width, obs.height))
        {
            if (relXCurrent + m_width > obs.x &&
                m_worldX < (currentChunkIndex * chunkWidth + obs.x))
            {
                nextX = currentChunkIndex * chunkWidth + obs.x - m_width;
            }
        }
    }

    for (const auto& obs : nextObstacles)
    {
        if (checkCollision(relXNext, m_y, m_width, m_height,
                           obs.x, obs.y, obs.width, obs.height))
        {
            if (relXNext + m_width > obs.x &&
                m_worldX < (nextChunkIndex * chunkWidth + obs.x))
            {
                nextX = nextChunkIndex * chunkWidth + obs.x - m_width;
            }
        }
    }

    double nextY = m_y;

    if (m_isGrounded && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        m_isJumping = true;
        m_isGrounded = false;
        m_jumpTime = 0;
    }

    if (m_fly)
    {
        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            nextY -= m_velocityY * deltaTime;
        }
        else
        {
            nextY += m_gravity * deltaTime * 0.3;
        }
    }
    else if (m_isJumping)
    {
        nextY -= m_velocityY * deltaTime;
        m_jumpTime += deltaTime;
        if (m_jumpTime >= m_maxJumpTime)
        {
            m_isJumping = false;
            m_jumpTime = 0;
        }
    }
    else
    {
        nextY += m_gravity * deltaTime;
    }


    bool landed = false;
    for (const auto& obs : currentObstacles)
    {
        if (checkCollision(relXCurrent, nextY, m_width, m_height,
                           obs.x, obs.y, obs.width, obs.height))
        {
            if (m_y + m_height <= obs.y && nextY + m_height > obs.y)
            {
                nextY = obs.y - m_height;
                m_isJumping = false;
                m_isGrounded = true;
                m_jumpTime = 0;
                landed = true;
            }
            else if (m_y >= obs.y + obs.height && nextY <= obs.y + obs.height)
            {
                nextY = obs.y + obs.height;
                m_isJumping = false;
                m_jumpTime = 0;
            }
        }
    }

    for (const auto& obs : nextObstacles)
    {
        if (checkCollision(relXNext, nextY, m_width, m_height,
                           obs.x, obs.y, obs.width, obs.height))
        {
            if (m_y + m_height <= obs.y && nextY + m_height > obs.y)
            {
                nextY = obs.y - m_height;
                m_isJumping = false;
                m_isGrounded = true;
                m_jumpTime = 0;
                landed = true;
            }
            else if (m_y >= obs.y + obs.height && nextY <= obs.y + obs.height)
            {
                nextY = obs.y + obs.height;
                m_isJumping = false;
                m_jumpTime = 0;
            }
        }
    }

    if (!landed && !m_isJumping)
    {
        m_isGrounded = false;
    }

    m_worldX = nextX;
    m_y = nextY;

    if(m_y <= 0 )
    {
        m_y = 0;
    }

    if (m_y >= 168)
    {
        if (!m_invincible)
        {
            m_failed = true;
        }
        else
        {
            m_y = 168;
            m_isGrounded = true;
            m_isJumping = false;
            m_jumpTime = 0;
        }
    }

    return currentChunkIndex;
    
}


void Player::update(double deltaTime) {}

void Player::render() {}

int Player::render2()
{
    TextureManager::Instance()->draw("character", m_x, m_y, m_width, m_height, Game::Instance()->getRenderer());
    return currentChunkIndex;
}
