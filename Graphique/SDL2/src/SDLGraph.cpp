//
// Created by gaspar_q on 3/11/16.
//

#include "SDLGraph.hpp"
#include "../../../Arcade.hpp"

int SDLGraph::eventManagment()
{
    if (SDL_PollEvent(&event) == 0)
        return event.key.keysym.sym;
    return -1;
}

void SDLGraph::display(std::stacgk<AComponent *> stack)
{

}

SDLGraph::SDLGraph()
{
    if (SDL_Init(0) != 0 ||
        (win = SDL_CreateWindow("Arcade", 0, 0, arcade::winWidth, arcade::winHeight, SDL_WINDOW_SHOWN)) == NULL ||
        (render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) == NULL)
        throw std::runtime_error(SDL_GetError());
}

SDLGraph::~SDLGraph()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
