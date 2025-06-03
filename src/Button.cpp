#include "Button.h"
#include "InputHandler.h"


Button::Button(int x, int y, int width, int height, void(*callback)()):m_x(x),m_y(y),m_width(width),m_height(height),m_callback(callback)
{
    m_currentFrame = MOUSE_OUT;
}

void Button::draw( std::string id, SDL_Renderer* t_Renderer, SDL_RendererFlip flip)
{
    TextureManager::Instance()->draw(id, m_x, m_y, m_width, m_height, t_Renderer, flip);

}

void Button::update()
{

    SDL_FPoint tMousePos = InputHandler::Instance()->getMousePosition();

    if(tMousePos.x > m_x 
        && tMousePos.x < (m_x + m_width)
        && tMousePos.y > m_y
        && tMousePos.y < (m_y + m_height))
     {
        m_currentFrame = MOUSE_OVER;
        
        if(InputHandler::Instance()->getMouseButtonState(MOUSE_LEFT)
            && m_buttonReleased)
        {
            m_currentFrame = CLICKED;
            
            m_callback();
            
            m_buttonReleased = false;

        }
        else if (InputHandler::Instance()->getMouseButtonState(MOUSE_LEFT))
        {
            m_buttonReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
     }
     else
     {
        m_currentFrame = MOUSE_OUT;
     }

}