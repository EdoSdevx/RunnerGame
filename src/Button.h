#pragma once

#include "TextureManager.h"

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class Button
{

    public:

        Button(int x, int y, int width, int height, void (*callback)());
        void draw(std::string id, SDL_Renderer* t_Renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void update();
        int getCurrentFrame() { return m_currentFrame; }

    private:

        int m_x;
        int m_y;
        int m_width;
        int m_height;

        int m_currentFrame;
        bool m_buttonReleased;

        void (*m_callback)();

};