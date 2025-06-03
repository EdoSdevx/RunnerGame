#pragma once

#include "SDL2/SDL.h"
#include <vector>
#include <set>

enum mouse_buttons
{
    MOUSE_LEFT = 0,
    MOUSE_MIDDLE = 1,
    MOUSE_RIGHT = 2
};

class InputHandler
{
public:

    static InputHandler* Instance()
    {
        if (m_Instance == nullptr)
        {
            m_Instance = new InputHandler();
        }
        return m_Instance;
    }

    void update();
    void reset();
    void clean();

    bool isKeyDown(SDL_Scancode key);
    bool wasKeyPressed(SDL_Scancode key);
    void clearPressedKey();

    bool getMouseButtonState(int buttonNumber)
    {
        return m_mouseButtonStates[buttonNumber];
    }

    SDL_FPoint getMousePosition()
    {
        return m_mousePosition;
    }

private:
    InputHandler();
    ~InputHandler() {}

    static InputHandler* m_Instance;

    void onMouseButtonDown(SDL_Event event);
    void onMouseButtonUp(SDL_Event event);
    void onMouseMotion(SDL_Event event);
    void onKeyDown(SDL_Event event);

    const Uint8* m_keystates;
    SDL_FPoint m_mousePosition;
    std::vector<bool> m_mouseButtonStates;
    std::set<SDL_Scancode> m_pressedKey;
    

};
