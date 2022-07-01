#include "Presenter.h"

#include "World.h"

extern World world;

SDL_Window* Presenter::m_main_window = nullptr;
SDL_Renderer* Presenter::m_main_renderer = nullptr;
unsigned int Presenter::m_SCREEN_WIDTH = 0;
unsigned int Presenter::m_SCREEN_HEIGHT = 0;

SDL_Renderer* Presenter::getRenderer()
{
    return m_main_renderer;
}

void Presenter::init()
{
    m_SCREEN_WIDTH = 1920;
    m_SCREEN_HEIGHT = 1080;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_main_window = SDL_CreateWindow("Chinese chess",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1366, 768, 0);
    m_main_renderer = SDL_CreateRenderer(m_main_window,
        -1, SDL_RENDERER_PRESENTVSYNC);
    improveRenderer();

    string cursorImg = IMG_FOLDER + MENU_FOLDER + "cursor.bmp";

    SDL_Surface* loadSurface = SDL_LoadBMP((cursorImg.c_str()));
    SDL_Cursor* cursor = SDL_CreateColorCursor(loadSurface, 10, 5);
    SDL_SetCursor(cursor);

    loadSurface = nullptr;
    cursor = nullptr;
}

void Presenter::improveRenderer()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    auto desktopWidth = DM.w;
    auto desktopHeight = DM.h;

    float2 mouseMultiply;
    mouseMultiply.x = (double)m_SCREEN_WIDTH / (double)desktopWidth;
    mouseMultiply.y = (double)m_SCREEN_HEIGHT / (double)desktopHeight;

    if (SDL_SetWindowFullscreen(m_main_window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
    {
        cout << "SDL_IMPROVE_RENDERER FAILED: %s\n" << SDL_GetError() << endl;
    }

    world.m_inputManager.setMouseMultiply(mouseMultiply);

    SDL_RenderSetLogicalSize(m_main_renderer, m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void Presenter::update()
{

}

void Presenter::draw()
{
    SDL_RenderPresent(m_main_renderer);

    SDL_RenderClear(m_main_renderer);
}

/*
* @param texture - the texture that will be drawn on the whole screen
*/
void Presenter::drawObject(SDL_Texture* texture)
{
    SDL_RenderCopy(m_main_renderer, texture, NULL, NULL);
}

void Presenter::drawObject(Drawable& drawable)
{
    SDL_RenderCopy(m_main_renderer, drawable.texture, NULL, &drawable.rect);
}

void Presenter::drawObject(DrawableWithOpacity& drawable)
{
    SDL_SetTextureAlphaMod(drawable.texture, drawable.opacity);
	
    SDL_RenderCopy(m_main_renderer, drawable.texture, NULL, &drawable.rect);
}