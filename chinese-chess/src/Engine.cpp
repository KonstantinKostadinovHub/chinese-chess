#include "Engine.h"

SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer)
{
    SDL_Texture* texture = nullptr;

    try
    {
        configFile = IMG_FOLDER + configFile;

        SDL_Surface* loadingSurface = SDL_LoadBMP(configFile.c_str());

        texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

        SDL_FreeSurface(loadingSurface);

        if (texture == nullptr)
        {
            throw (-1);
        }
    }
    catch (int i)
    {
        if (i < 0)
        {
            cout << "NO TEXTURE LOADED: " << configFile << endl;

            configFile = IMG_FOLDER + "textureNotLoaded.bmp";

            SDL_Surface* loadingSurface = SDL_LoadBMP(configFile.c_str());
            texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
            SDL_FreeSurface(loadingSurface);
        }
    }

    return texture;
}

bool MouseIsInRect(int2 coor, SDL_Rect rect)
{
    if (coor.x >= rect.x && coor.x <= rect.x + rect.w && coor.y >= rect.y && coor.y <= rect.y + rect.h)
    {
        return true;
    }

    return false;
}