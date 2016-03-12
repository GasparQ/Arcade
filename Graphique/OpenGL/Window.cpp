//
// Created by veyrie_f on 3/10/16.
//

#include <ostream>
#include <iostream>
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
    gluPerspective(70, (double) (900.0 / 600.0), 1, 1000);
    glEnable(GL_DEPTH_TEST);
}

// Vetical axis is (0, 1, 0)
void Window::RefreshImage()
{
    static double i = 0;
    static double z = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, -5, 0, 0, 0, 0, 1, 0);
    // Draw everything here
    //DrawSphere();
    DrawCube(0, 1, 0);
    DrawCube(0, 0, 0);
    glFlush();
    SDL_GL_SwapWindow(m_window);
}

void Window::DrawSphere(double posX, double posY, double posZ,
                        double red, double green, double blue) const
{
    GLUquadric *param;

    glPushMatrix();
    glTranslated(posX, posY, posZ);
    param = gluNewQuadric();
    glColor4f(1, 0, 1, 1);
    gluSphere(param, 1, 10, 10);
    gluDeleteQuadric(param);
    glPopMatrix();
}

void Window::DrawCube(double posX, double posY, double posZ,
                      double red, double green, double blue) const
{
    glPushMatrix();
    //glLoadIdentity();
    glTranslated(posX, posY, posZ);

    glBegin(GL_QUADS);

    glColor3ub(red, green, blue); //face 1
    glVertex3d(0.5, 0.5, 0.5);
    glVertex3d(0.5, 0.5, -0.5);
    glVertex3d(-0.5, 0.5, -0.5);
    glVertex3d(-0.5, 0.5, 0.5);
    glColor3ub(red, green, blue); //face 2
    glVertex3d(0.5, -0.5, 0.5);
    glVertex3d(0.5, -0.5, -0.5);
    glVertex3d(0.5, 0.5, -0.5);
    glVertex3d(0.5, 0.5, 0.5);
    glColor3ub(red, green, blue); //face 3
    glVertex3d(-0.5, -0.5, 0.5);
    glVertex3d(-0.5, -0.5, -0.5);
    glVertex3d(0.5, -0.5, -0.5);
    glVertex3d(0.5, -0.5, 0.5);
    glColor3ub(red, green, blue); //face 4
    glVertex3d(-0.5, 0.5, 0.5);
    glVertex3d(-0.5, 0.5, -0.5);
    glVertex3d(-0.5, -0.5, -0.5);
    glVertex3d(-0.5, -0.5, 0.5);
    glColor3ub(red, green, blue); //face 5
    glVertex3d(0.5, 0.5, -0.5);
    glVertex3d(0.5, -0.5, -0.5);
    glVertex3d(-0.5, -0.5, -0.5);
    glVertex3d(-0.5, 0.5, -0.5);
    glColor3ub(red, green, blue); //face 6
    glVertex3d(0.5, -0.5, 0.5);
    glVertex3d(0.5, 0.5, 0.5);
    glVertex3d(-0.5, 0.5, 0.5);
    glVertex3d(-0.5, -0.5, 0.5);

    glEnd();
    glPopMatrix();
}
