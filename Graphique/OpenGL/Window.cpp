//
// Created by veyrie_f on 3/10/16.
//

#include "Window.hpp"

Window::Window(int width, int height, const char *name)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        throw arcade::InitRenderException("OpenGL / SDL");
    }
    m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);
    if (m_window == NULL || m_glContext == NULL)
    {
        throw arcade::InitRenderException("OpenGL - Screen");
    }
    SetProjectionMode();
}

Window::~Window()
{
    if (m_window != NULL)
    {
        SDL_DestroyWindow(m_window);
    }
    if (m_glContext != NULL)
    {
        SDL_GL_DeleteContext(m_glContext);
    }
}

void Window::SetProjectionMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void Window::RefreshImage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Draw everything here
    DrawSphere();
    glFlush();
    SDL_GL_SwapWindow(m_window);
}

void Window::DrawSphere()
{
    GLUquadric    *param;

    glPushMatrix();
    param = gluNewQuadric();
    glColor4f(1, 1, 1, 1);
    gluSphere(param, 10, 30, 30);
    gluDeleteQuadric(param);
    glPopMatrix();
}
