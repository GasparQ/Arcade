//
// Created by gaspar_q on 3/11/16.
//

#include "SDLGraph.hpp"
#include "../../../Commons/include/ArcadeSystem.hpp"

int SDLGraph::eventManagment()
{
    std::map<int, int>::const_iterator  it;

    if (SDL_PollEvent(&event) == 1 && (it = keyCodeAssociation.find(event.key.keysym.scancode)) != keyCodeAssociation.end())
        return it->second;
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
        (win = SDL_CreateWindow("Arcade", 0, 0, ArcadeSystem::winWidth * SDLGraph::scale, ArcadeSystem::winHeight * SDLGraph::scale, SDL_WINDOW_SHOWN)) == NULL ||
        (render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) == NULL)
        throw std::runtime_error(SDL_GetError());
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