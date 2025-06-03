    #include <iostream>
    #include "TextureManager.h"
    #include "SDL2/SDL_image.h"

    TextureManager* TextureManager::m_Instance = nullptr;

    bool TextureManager::load( std::string fileName, std::string id, SDL_Renderer* t_Renderer)
    {
        SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

        if(tempSurface == nullptr)
        {
            std::cout<<"Image could not be loaded!\n";
            return false;
        }

        SDL_Texture* t_Texture = SDL_CreateTextureFromSurface(t_Renderer, tempSurface);

        SDL_FreeSurface(tempSurface);

        if(t_Texture != nullptr)
        {
            m_textureMap[id] = t_Texture;
            return true;
        }
        return false;
    }

    void TextureManager::drawFrame( std::string id, int x, int y, int destX, int destY, int width, int height, SDL_Renderer* t_Renderer)
    {

        SDL_Rect srcRect;
        SDL_Rect destRect;

        srcRect.x = x;
        srcRect.y = y;

        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;

        destRect.x = destX;
        destRect.y = destY;

        SDL_RenderCopyEx( t_Renderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
    }

    void TextureManager::draw( std::string id, int x, int y, int width, int height, SDL_Renderer* t_Renderer, SDL_RendererFlip flip)
    {

        SDL_Rect srcRect;
        SDL_Rect destRect;

        srcRect.x = 0;
        srcRect.y = 0;

        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;

        destRect.x = x;
        destRect.y = y;

        SDL_RenderCopyEx( t_Renderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
    }


    void TextureManager::drawScrolling(std::string id, int x, int y, int width, int height, SDL_Renderer* t_Renderer)
    {
        SDL_Rect srcRect;
        SDL_Rect destRect;

        srcRect.x = x;
        srcRect.y = y;
        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;

        destRect.x = destRect.y = 0;

        SDL_RenderCopyEx( t_Renderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
    }
    void TextureManager::drawInfiniteScrolling(const std::vector<std::string>& chunks, int cameraX, int y, int chunkWidth, int height, SDL_Renderer* t_Renderer)
    {
        int totalMapWidth = chunkWidth * chunks.size();
        int scrollX = cameraX % totalMapWidth;
        if (scrollX < 0) scrollX += totalMapWidth;

        int currentChunkIndex = scrollX / chunkWidth;
        int offsetInChunk = scrollX % chunkWidth;

        const std::string& firstChunk = chunks[currentChunkIndex];
        const std::string& secondChunk = chunks[currentChunkIndex + 1];

        SDL_Rect srcRect1 = { offsetInChunk, 0, chunkWidth - offsetInChunk, height };
        SDL_Rect destRect1 = { 0, y, chunkWidth - offsetInChunk, height };
        SDL_RenderCopy(t_Renderer, m_textureMap[firstChunk], &srcRect1, &destRect1);

        SDL_Rect srcRect2 = { 0, 0, offsetInChunk, height };
        SDL_Rect destRect2 = { chunkWidth - offsetInChunk, y, offsetInChunk, height };
        SDL_RenderCopy(t_Renderer, m_textureMap[secondChunk], &srcRect2, &destRect2);
    }

    void TextureManager::drawStretch(std::string id, int x, int y, SDL_Renderer* t_Renderer)
    {
        SDL_RenderCopy(t_Renderer, m_textureMap[id], nullptr, nullptr);
    }
    void TextureManager::clean()
    {
        for (auto& texture : m_textureMap)
        {
            SDL_DestroyTexture(texture.second);
        }
        m_textureMap.clear();
    }


