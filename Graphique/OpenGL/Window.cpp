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
    gluPerspective(70, (double) (900.0 / 600.0), 1, 1000);
    glEnable(GL_DEPTH_TEST);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    InitLighting();
}

// Vetical axis is (0, 1, 0)
void Window::RefreshImage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 3, -5, 0, 0, 0, 0, 1, 0);
    // Draw everything here
    DrawTerrain(10, 10);

    DrawSphere();
    DrawCube(0, 0, 0);
    //DrawCube(1, 0, 0);
    glFlush();
    SDL_GL_SwapWindow(m_window);
}

void Window::DrawSphere(double posX, double posY, double posZ,
                        double red, double green, double blue) const
{
    GLUquadric *param;

    glPushMatrix();
    glTranslated(-posX, -posY, -posZ);
    param = gluNewQuadric();
    glColor4d(red, green, blue, 1);
    gluSphere(param, 0.5, 10, 10);
    gluDeleteQuadric(param);
    glPopMatrix();
}

void Window::DrawCube(double posX, double posY, double posZ,
                      double red, double green, double blue) const
{
    glPushMatrix();
    //glLoadIdentity();
    glTranslated(-posX, -posY, -posZ);

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

// Handles lighting in the scene
void Window::InitLighting() const
{
    GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void Window::DrawTerrain(int sizeX, int sizeY) const
{
    for (double i = -(sizeX / 2.0); i < sizeX; ++i)
    {
        for (double j = -(sizeY / 2.0); j < sizeY; ++j)
        {
            DrawCube(i, 0, j);
        }
    }
}
