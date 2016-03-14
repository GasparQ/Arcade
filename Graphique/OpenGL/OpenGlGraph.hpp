//
// Created by veyrie_f on 3/10/16.
//

#ifndef CPP_ARCADE_WINDOW_HPP
#define CPP_ARCADE_WINDOW_HPP

#include <map>
#include <GL/gl.h>
#include <GL/glu.h>
#include "./include/glut.h"
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

public:
    virtual int eventManagment();

    virtual void display(std::stack<AComponent *>);

private:
    void DrawSphere(double posX = 0, double posY = 0, double posZ = 0,
                    double red = 255, double green = 255, double blue = 255) const;

    void DrawCube(Vector2<int> pos, AComponent::ComponentColor color, double posY = 0) const;

    void DrawTerrain(int sizeX, int sizeY) const;

    void InitLighting() const;

    void DrawBackground() const ;

    void RefreshImage() const;

    void Set2DMode();

    void Set3DMode();

    void DrawText(Vector2<int> pos, std::string const& text, AComponent::ComponentColor const& color);

private:
    enum RenderMode
    {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2
    };

private:
    SDL_Window *m_window = NULL;
    SDL_GLContext m_glContext = NULL;
    SDL_Event event;
    Vector2<double> m_win;
    std::map<int, int>  keyCodeAssociation;
    // RGBA
    SDL_Color colors[10] = {{0, 0, 0, 0}, // Black
                            {255, 0, 0, 255}, // red
                            {0, 255, 0, 255}, // green
                            {255, 255, 0, 255}, // yellow
                            {0, 0, 255, 255}, // blue
                            {255, 0, 255, 255}, // magenta
                            {0, 255, 255, 255}, // cyan
                            {255, 255, 255, 255}}; // white
    RenderMode m_render_mode = PERSPECTIVE;
};


#endif //CPP_ARCADE_WINDOW_HPP
