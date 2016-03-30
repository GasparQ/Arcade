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

//TODO
//  -   Trucs par défauts au lieu de throw des exceptions #imagesToColorSquare #basicFont
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
    SDL_Event                           event;
    SDL_Window                          *win;
    SDL_Renderer                        *render;
    std::map<int, int>                  keyCodeAssociation;
    std::map<std::string, SDL_Texture*> spriteCache;
    TTF_Font                            *uifont;
    std::map<AComponent::ComponentColor, SDL_Color> colors;

private:
    SDL_Texture *loadSprite(std::string const &)                                                            throw(std::runtime_error);
    void        drawGameComponent(GameComponent const *)                                                    throw(std::runtime_error);
    void        drawUIComponent(UIComponent const *)                                                        throw(std::runtime_error);
    void        drawHighScoreComponent(HighScoreComponent const *)                                          throw(std::runtime_error);
    void        displaySurface(SDL_Texture *, Vector2<double> pos, Vector2<double> dim = Vector2<double>(1, 1))    throw(std::runtime_error);
    void        drawText(std::string const&, Vector2<double> pos, Vector2<double> dim = Vector2<double>(1, 1), AComponent::ComponentColor color = AComponent::ComponentColor::COLOR_WHITE);
    void        addColor(AComponent::ComponentColor index, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
};

#endif //C_SDLGRAPH_HPP
