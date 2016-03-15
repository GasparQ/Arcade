//
// Created by gaspar_q on 3/11/16.
//

#ifndef C_SDLGRAPH_HPP
#define C_SDLGRAPH_HPP

#include <string>
#include <map>
#include "../include/SDL.h"
#include "../include/SDL_ttf.h"
#include "../../include/IGraph.hpp"
#include "../../../Commons/include/GameComponent.hpp"
#include "../../../Commons/include/UIComponent.hpp"
#include "../../../Commons/include/HighScoreComponent.hpp"

class   SDLGraph : public IGraph
{
public:
    SDLGraph();
    ~SDLGraph();
    static const size_t scale = 25;
    static const std::string fontName;

public:
    virtual int eventManagment();
    virtual void display(std::stack<AComponent *>);

private:
    SDL_Event           event;
    SDL_Window          *win;
    SDL_Renderer        *render;
    std::map<int, int>  keyCodeAssociation;
    std::map<std::string, SDL_Texture*> spriteCache;
    TTF_Font            *uifont;
    SDL_Color           uicolor;

private:
    SDL_Texture *loadSprite(std::string const &) throw(std::runtime_error);
    void        drawGameComponent(GameComponent const *) throw(std::runtime_error);
    void        drawUIComponent(UIComponent const *) throw(std::runtime_error);
    void        drawHighScoreComponent(HighScoreComponent const *) throw(std::runtime_error);
    void        displaySurface(AComponent const *, SDL_Texture *, Vector2<int> dim = Vector2<int>(1, 1)) throw(std::runtime_error);
};

#endif //C_SDLGRAPH_HPP
