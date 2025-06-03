#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::m_Instance = nullptr;

InputHandler::InputHandler():m_keystates(nullptr)
{
    for(int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
}

void InputHandler::update()
{

    m_keystates = SDL_GetKeyboardState(nullptr);

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {

        switch(event.type)
        {
        case SDL_QUIT:
                Game::Instance()->stopTheGame();
                break;
        case SDL_MOUSEMOTION:
                onMouseMotion(event);
                break;
        case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event);
                break;
        case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event);
                break;
        case SDL_KEYDOWN:
                onKeyDown(event);
                break;  
        case SDL_KEYUP:
                m_pressedKey.erase(event.key.keysym.scancode);
                break;
        default:
                break;
        }
    }
}



bool InputHandler::isKeyDown(SDL_Scancode key)
{

    if(m_keystates != nullptr )
    {
        return m_keystates[key] == 1;
    }

    return false;
}

void InputHandler::onMouseButtonDown(SDL_Event event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[MOUSE_LEFT] = true;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MOUSE_MIDDLE] = true;
    }

    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[MOUSE_RIGHT] = true;
    }

}

void InputHandler::onMouseButtonUp(SDL_Event event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[MOUSE_LEFT] = false;
    }

    if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MOUSE_MIDDLE] = false;
    }

    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[MOUSE_RIGHT] = false;
    }

}

void InputHandler::onMouseMotion(SDL_Event event)
{
    m_mousePosition.x = event.motion.x;
    m_mousePosition.y = event.motion.y;

}

void InputHandler::onKeyDown(SDL_Event event)
{
    m_keystates = SDL_GetKeyboardState(nullptr);

    if(event.key.repeat == 0)
    {
        m_pressedKey.insert(event.key.keysym.scancode);
    }
}

bool InputHandler::wasKeyPressed(SDL_Scancode key)
{
    return m_pressedKey.find(key) != m_pressedKey.end();
}

void InputHandler::clearPressedKey()
{
    m_pressedKey.clear();
}

void InputHandler::reset()
{
    for(size_t i = 0; i < m_mouseButtonStates.size(); i++)
    {
        m_mouseButtonStates[i] = false;
    }
    
    m_mousePosition.x = 0;
    m_mousePosition.y = 0;
}

void InputHandler::clean()
{
    delete m_Instance;
    m_Instance = nullptr;
}