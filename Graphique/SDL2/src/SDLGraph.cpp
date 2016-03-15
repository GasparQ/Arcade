//
// Created by gaspar_q on 3/11/16.
//

#include <unistd.h>
#include <errno.h>
#include "SDLGraph.hpp"
#include "../../../Commons/include/ArcadeSystem.hpp"
#include "../../../Commons/include/UIComponent.hpp"

const std::string SDLGraph::fontName = "./fonts/Minecraft.ttf"; //Snake_in_the_Boot

int SDLGraph::eventManagment()
{
    std::map<int, int>::const_iterator  it;
    int                                 key = -1;

    while (SDL_PollEvent(&event) == 1)
    {
        if (event.type == SDL_KEYDOWN)
        {
            key = event.key.keysym.sym;
            if ((it = keyCodeAssociation.find(event.key.keysym.scancode)) != keyCodeAssociation.end())
                return it->second;
        }
    }
    return key;
}

void SDLGraph::display(std::stack<AComponent *> stack)
{
    GameComponent   *gameComponent;
    UIComponent     *uiComponent;

    SDL_RenderClear(render);
    while (!stack.empty())
    {
        if ((gameComponent = dynamic_cast<GameComponent *>(stack.top())))
            drawGameComponent(gameComponent);
        else if ((uiComponent = dynamic_cast<UIComponent *>(stack.top())))
            drawUIComponent(uiComponent);
        stack.pop();
    }
    SDL_RenderPresent(render);
}

SDLGraph::SDLGraph()
{
    if (SDL_Init(0) != 0 ||
        (win = SDL_CreateWindow("Arcade", 0, 0, ArcadeSystem::winWidth * SDLGraph::scale, ArcadeSystem::winHeight * SDLGraph::scale, SDL_WINDOW_SHOWN)) == NULL ||
        (render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) == NULL ||
        TTF_Init() != 0 || (uifont = TTF_OpenFont(SDLGraph::fontName.c_str(), 24)) == NULL)
        throw std::runtime_error(SDL_GetError());
    uicolor.r = 255;
    uicolor.g = 255;
    uicolor.b = 255;
    keyCodeAssociation[SDL_SCANCODE_LEFT] = ArcadeSystem::ArrowLeft;
    keyCodeAssociation[SDL_SCANCODE_RIGHT] = ArcadeSystem::ArrowRight;
    keyCodeAssociation[SDL_SCANCODE_UP] = ArcadeSystem::ArrowUp;
    keyCodeAssociation[SDL_SCANCODE_DOWN] = ArcadeSystem::ArrowDown;
    keyCodeAssociation[SDL_SCANCODE_SPACE] = ArcadeSystem::Space;
    keyCodeAssociation[SDL_SCANCODE_2] = ArcadeSystem::PrevGraph;
    keyCodeAssociation[SDL_SCANCODE_3] = ArcadeSystem::NextGraph;
    keyCodeAssociation[SDL_SCANCODE_4] = ArcadeSystem::PrevGame;
    keyCodeAssociation[SDL_SCANCODE_5] = ArcadeSystem::NextGame;
    keyCodeAssociation[SDL_SCANCODE_8] = ArcadeSystem::Restart;
    keyCodeAssociation[SDL_SCANCODE_9] = ArcadeSystem::Home;
    keyCodeAssociation[SDL_SCANCODE_ESCAPE] = ArcadeSystem::Exit;
    keyCodeAssociation[SDL_SCANCODE_P] = ArcadeSystem::Pause;
    keyCodeAssociation[SDL_SCANCODE_RETURN] = ArcadeSystem::Enter;
    keyCodeAssociation[SDL_SCANCODE_BACKSPACE] = ArcadeSystem::Backspace;
}

SDLGraph::~SDLGraph()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

SDL_Texture     *SDLGraph::loadSprite(const std::string &file) throw(std::runtime_error)
{
    std::map<std::string, SDL_Texture*>::iterator   it;

    if ((it = spriteCache.find(file)) != spriteCache.end())
        return (it->second);

    SDL_Surface *surface;
    SDL_Texture *tex;

    if ((surface = SDL_LoadBMP(file.c_str())) == NULL ||
        (tex = SDL_CreateTextureFromSurface(render, surface)) == NULL)
        throw std::runtime_error(SDL_GetError());
    spriteCache[file] = tex;
    return tex;
}

void SDLGraph::displaySurface(AComponent *component, SDL_Texture *texture, Vector2<int> dim) throw(std::runtime_error)
{
    SDL_Rect    pos;

    pos.x = static_cast<int>(component->getPos().x * SDLGraph::scale);
    pos.y = static_cast<int>(component->getPos().y * SDLGraph::scale);
    pos.w = dim.x * static_cast<int>(SDLGraph::scale);
    pos.h = dim.y * static_cast<int>(SDLGraph::scale);
    if (SDL_RenderCopy(render, texture, NULL, &pos) != 0)
        throw std::runtime_error(SDL_GetError());
}

void SDLGraph::drawGameComponent(GameComponent *component) throw(std::runtime_error)
{
    SDL_Texture *texture = loadSprite(component->getSprite2D());

    displaySurface(component, texture);
}

void SDLGraph::drawUIComponent(UIComponent *component) throw(std::runtime_error)
{
    SDL_Surface *text;
    SDL_Texture *texture;

    if ((text = TTF_RenderText_Solid(uifont, component->getText().c_str(), uicolor)) == NULL ||
        (texture = SDL_CreateTextureFromSurface(render, text)) == NULL)
        throw std::runtime_error(SDL_GetError());
    displaySurface(component, texture, component->getDim());
}

extern "C" IGraph *loadLib()
{
    return (new SDLGraph());
}
