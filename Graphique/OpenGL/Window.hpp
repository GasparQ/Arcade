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

class Window
{
public:
    Window(int width = 900, int height = 600, const char *name = "OpenGL Win");

    virtual ~Window();

    void RefreshImage();

private:
    void SetProjectionMode();

    void DrawSphere(double posX = 0, double posY = 0, double posZ = 0,
                    double red = 255, double green = 255, double blue = 255) const;

    void DrawCube(double posX = 0, double posY = 0, double posZ = 0,
                  double red = 1, double green = 1, double blue = 1) const;

    void DrawTerrain(int sizeX, int sizeY) const;

    void InitLighting() const;

private:
    SDL_Window *m_window = NULL;
    SDL_GLContext m_glContext = NULL;
};


#endif //CPP_ARCADE_WINDOW_HPP
