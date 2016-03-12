//
// Created by gaspar_q on 3/11/16.
//

#ifndef C_SDLGRAPH_HPP
#define C_SDLGRAPH_HPP

#include "../include/SDL.h"
#include "../../include/IGraph.hpp"

class   SDLGraph : public IGraph
{
public:
    SDLGraph();
    ~SDLGraph();

public:
    virtual int eventManagment();
    virtual void display(std::stack<AComponent *>);

private:
    SDL_Event       event;
    SDL_Window      *win;
    SDL_Renderer    *render;
};

#endif //C_SDLGRAPH_HPP
