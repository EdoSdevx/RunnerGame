#pragma once

#include "SDL2/SDL.h"
#include "GameStateMachine.h"
#include "PlayState.h"

class Game 
{
   public:

        static Game* Instance()
        {
            if(m_Instance == nullptr)
            {
                m_Instance = new Game();
            }
            return m_Instance;
            
        }
        bool init(const char* title, int windowPosX, int windowPosY, int screenWidth,
                  int screenHeight, Uint32 flag);

        bool isRunning() { return m_Running; }
        
        void update(double deltaTime);
        void render();
        void clean();
        void stopTheGame() { m_Running = false; }

        int getCameraPos() { return m_cameraX; }
        void setCameraPos(int val) { m_cameraX = val; } 

        GameStateMachine* getStateMachine() { return m_StateMachine; }
    
        SDL_Renderer* getRenderer() { return m_Renderer; }
    

   private:

        Game();
        ~Game();

        static Game* m_Instance;

        SDL_Window*   m_Window;
        SDL_Renderer* m_Renderer;
        bool m_Running;

        GameStateMachine* m_StateMachine;

        int m_cameraX;


        


};