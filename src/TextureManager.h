#pragma once

#include <string>
#include <map>
#include <vector>
#include <SDL2/SDL.h>



class TextureManager
{

    public:
        
        static TextureManager* Instance()
        {
            if(m_Instance == nullptr)
            {
                m_Instance = new TextureManager();
            }
            
            return m_Instance;
        }
        

        bool load( std::string fileName, std::string id, SDL_Renderer* t_Renderer );
        void draw( std::string id, int x, int y, int width, int height, SDL_Renderer* t_Renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void drawFrame(std::string id, int x, int y, int destX, int destY, int width, int height, SDL_Renderer* t_Renderer);
        void drawScrolling(std::string id, int x, int y, int width, int height, SDL_Renderer* t_Renderer);
        void drawInfiniteScrolling(const std::vector<std::string>& chunks, int cameraX, int y, int chunkWidth, int height, SDL_Renderer* t_Renderer);
        void drawStretch(std::string id, int x, int y, SDL_Renderer* t_Renderer);
        void clean();

        SDL_Texture* getTexture(const std::string& id)
        {
            return m_textureMap[id];
        }


    private:

        TextureManager(){}
        ~TextureManager();

        static TextureManager* m_Instance;

        std::map<std::string, SDL_Texture*> m_textureMap;

    

};