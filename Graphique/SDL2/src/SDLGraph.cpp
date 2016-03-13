//
// Created by gaspar_q on 3/11/16.
//

#include "SDLGraph.hpp"
#include "../../../Arcade.hpp"

int SDLGraph::eventManagment()
{
    if (SDL_PollEvent(&event) == 1)
        return event.key.keysym.sym;
    return -1;
}

void SDLGraph::display(std::stack<AComponent *> stack)
{
    GameComponent   *gameComponent;

    SDL_RenderClear(render);
    while (!stack.empty())
    {
        if ((gameComponent = dynamic_cast<GameComponent *>(stack.top())))
            drawGameComponent(gameComponent);
        stack.pop();
    }
    SDL_RenderPresent(render);
}

SDLGraph::SDLGraph()
{
    if (SDL_Init(0) != 0 ||
        (win = SDL_CreateWindow("Arcade", 0, 0, arcade::winWidth * SDLGraph::scale, arcade::winHeight * SDLGraph::scale, SDL_WINDOW_SHOWN)) == NULL ||
        (render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) == NULL)
        throw std::runtime_error(SDL_GetError());
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

void *SDLGraph::drawGameComponent(GameComponent *component) throw(std::runtime_error)
{
    SDL_Texture *texture = loadSprite(component->getSprite2D());
    SDL_Rect    pos;

    pos.x = static_cast<int>(component->getPos().x * SDLGraph::scale);
    pos.y = static_cast<int>(component->getPos().y * SDLGraph::scale);
    pos.w = SDLGraph::scale;
    pos.h = SDLGraph::scale;
    if (SDL_RenderCopy(render, texture, NULL, &pos) != 0)
        throw std::runtime_error(SDL_GetError());
    return nullptr;
}

extern "C" IGraph *loadLib()
{
    return (new SDLGraph());
}