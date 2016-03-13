//
// Created by gaspar_q on 3/11/16.
//

#ifndef C_SDLGRAPH_HPP
#define C_SDLGRAPH_HPP

#include <string>
#include <map>
#include "../include/SDL.h"
#include "../../include/IGraph.hpp"
#include "../../../Component/include/GameComponent.hpp"

class   SDLGraph : public IGraph
{
public:
    SDLGraph();
    ~SDLGraph();
    static const size_t scale = 25;

public:
    virtual int eventManagment();
    virtual void display(std::stack<AComponent *>);

private:
    SDL_Event           event;
    SDL_Window          *win;
    SDL_Renderer        *render;
    std::map<int, int>  keyCodeAssociation;
    std::map<std::string, SDL_Texture*> spriteCache;

private:
    SDL_Texture *loadSprite(std::string const &) throw(std::runtime_error);
    void        *drawGameComponent(GameComponent *) throw(std::runtime_error);
};

#endif //C_SDLGRAPH_HPP
