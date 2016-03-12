//
// Created by veyrie_f on 3/10/16.
//

#ifndef CPP_ARCADE_WINDOW_HPP
#define CPP_ARCADE_WINDOW_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include "../SDL2/include/SDL_surface.h"
#include "../SDL2/include/SDL.h"
#include "../../Exception/LoadException.hpp"
#include "../SDL2/include/SDL_opengl.h"
#include "../include/IGraph.hpp"
#include "../../Component/include/GameComponent.hpp"
#include "../../Component/include/UIComponent.hpp"

class OpenGlGraph : public IGraph
{
public:
    OpenGlGraph(int width = 900, int height = 800, const char *name = "OpenGL Win");

    virtual ~OpenGlGraph();

    void DrawBackground();

    void RefreshImage();

public:
    virtual int eventManagment();

    virtual void display(std::stack<AComponent *>);

private:
    void SetProjectionMode();

    void DrawSphere(double posX = 0, double posY = 0, double posZ = 0,
                    double red = 255, double green = 255, double blue = 255) const;

    void DrawCube(Vector2 pos, AComponent::ComponentColor color) const;

    void DrawTerrain(int sizeX, int sizeY) const;

    void InitLighting() const;

private:
    SDL_Window *m_window = NULL;
    SDL_GLContext m_glContext = NULL;
    // RGBA
    SDL_Color colors[10] = {{0, 0, 0, 0},
                            {255, 0, 0, 255},
                            {0, 255, 0, 255},
                            {255, 0, 255, 255},
                            {0, 0, 255, 255},
                            {255, 255, 0, 255},
                            {255, 0, 255, 255},
                            {255, 255, 255, 255}};
};


#endif //CPP_ARCADE_WINDOW_HPP
