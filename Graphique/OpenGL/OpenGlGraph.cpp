//
// Created by veyrie_f on 3/10/16.
//

#include <bits/unique_ptr.h>
#include "OpenGlGraph.hpp"
#include "../../Arcade.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"

// Ctor:
// Initializes Projection mode (3D by default) and Lighting
OpenGlGraph::OpenGlGraph(int width, int, const char *name) :
        m_size_coeff(width / arcade::winWidth),
        m_win(arcade::winWidth * m_size_coeff, arcade::winHeight * m_size_coeff)
{
    int ac = 1;
    glutInit(&ac, NULL);
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        throw arcade::InitRenderException("OpenGL / SDL");
    }
    m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int) m_win.x,
                                (int) m_win.y, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);
    if (m_window == NULL || m_glContext == NULL)
    {
        throw arcade::InitRenderException("OpenGL - Screen");
    }
    keyCodeAssociation[SDL_SCANCODE_LEFT] = ArcadeSystem::ArrowLeft;
    keyCodeAssociation[SDL_SCANCODE_RIGHT] = ArcadeSystem::ArrowRight;
    keyCodeAssociation[SDL_SCANCODE_UP] = ArcadeSystem::ArrowUp;
    keyCodeAssociation[SDL_SCANCODE_DOWN] = ArcadeSystem::ArrowDown;
    keyCodeAssociation[SDL_SCANCODE_SPACE] = ArcadeSystem::Space;
    keyCodeAssociation[SDL_SCANCODE_2] = ArcadeSystem::PrevGraph;
    keyCodeAssociation[SDL_SCANCODE_3] = ArcadeSystem::NextGraph;
    keyCodeAssociation[SDL_SCANCODE_4] = ArcadeSystem::PrevGame;
    keyCodeAssociation[SDL_SCANCODE_5] = ArcadeSystem::NextGame;
    keyCodeAssociation[SDL_SCANCODE_8] = ArcadeSystem::Restart;
    keyCodeAssociation[SDL_SCANCODE_9] = ArcadeSystem::Home;
    keyCodeAssociation[SDL_SCANCODE_ESCAPE] = ArcadeSystem::Exit;
    keyCodeAssociation[SDL_SCANCODE_P] = ArcadeSystem::Pause;

    Set3DMode();
    InitLighting();
}

// Dtor :
// Destroys window and context
OpenGlGraph::~OpenGlGraph()
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

// Handles lighting in the scene
void OpenGlGraph::InitLighting() const
{
    GLfloat lightAmbient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[] = {50.0, 100.0, 50.0, 0.0};

    // Enables material to be impacted by light
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

// Vetical axis is (0, 1, 0)
void OpenGlGraph::RefreshImage() const
{
    glFlush();
    SDL_GL_SwapWindow(m_window);
}

void OpenGlGraph::DrawBackground() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // We set the eye to see 3/4 view, the center on Vector.zero and y as up axis
    //static float i = 0;
    //gluLookAt(0, 34, -48, 0, 0, 0, 0, 1, 0);
    gluLookAt(0, 34, -28, 0, 0, -15, 0, 1, 0);
    // then we translate to center
    glTranslated(arcade::winWidth / 2.0, 0, 0);
    DrawTerrain(arcade::winWidth, arcade::winHeight);
}

void OpenGlGraph::DrawSphere(Vector2<int> pos, AComponent::ComponentColor color) const
{
    GLUquadric *param;

    glPushMatrix();
    glTranslated(-pos.x, 0, -pos.y);
    param = gluNewQuadric();
    glColor4d(colors[color].r, colors[color].g, colors[color].b, 1);
    gluSphere(param, 0.5, 20, 20);
    gluDeleteQuadric(param);
    glPopMatrix();
}

void OpenGlGraph::DrawCube(Vector2<int> pos, AComponent::ComponentColor color, double posY) const
{
    glPushMatrix();
    glTranslated(-pos.x, -posY, -pos.y);

    // Byte color
    glColor3ub(colors[color].r, colors[color].g, colors[color].b);

    glutSolidCube(1);

    glPopMatrix();
}

void OpenGlGraph::DrawTerrain(int sizeX, int sizeY) const
{
    for (int i = -1; i <= sizeX; ++i)
    {
        for (int j = -1; j <= sizeY; ++j)
        {
            if (i == -1 || j == -1 || i == sizeX || j == sizeY)
            {
                DrawCube(Vector2<int>(i, j), AComponent::COLOR_YELLOW);
            }
            DrawCube(Vector2<int>(i, j), AComponent::COLOR_BLUE, 1);
        }
    }
}

// Returns key pressed
int OpenGlGraph::eventManagment()
{
    std::map<int, int>::const_iterator it;

    while (SDL_PollEvent(&event) == 1)
    {
        if (event.type == SDL_KEYDOWN &&
            (it = keyCodeAssociation.find(event.key.keysym.scancode)) != keyCodeAssociation.end())
            return it->second;
    }
    return -1;
}

// Handles data display
void OpenGlGraph::display(std::stack<AComponent *> stack)
{
    GameComponent *gc;
    UIComponent *uic;
    HighScoreComponent *hsc;

    Set3DMode();
    DrawBackground();
    while (!stack.empty())
    {
        if ((gc = dynamic_cast<GameComponent *>(stack.top())) != nullptr)
        {
            if (m_render_mode == ORTHOGRAPHIC)
            {
                Set3DMode();
            }
            switch (gc->getSprite3D())
            {
                case GameComponent::Shapes::SPHERE:
                    DrawSphere(gc->getPos(), gc->getColor());
                    break;
                case GameComponent::Shapes::CUBE:
                    DrawCube(gc->getPos(), gc->getColor());
                    break;
            }
        }
        else if ((uic = dynamic_cast<UIComponent *>(stack.top())) != nullptr)
        {
            if (m_render_mode == PERSPECTIVE)
            {
                Set2DMode();
            }
            DrawText(uic->getPos(), uic->getText(), uic->getColor());
        }
        else if ((hsc = dynamic_cast<HighScoreComponent *>(stack.top())) != nullptr)
        {
            if (m_render_mode == PERSPECTIVE)
            {
                Set2DMode();
            }
            const UIComponent *const *var = hsc->getComponentsToDisplay();
            for (int i = 0; var && var[i]; i++)
            {
                DrawText(var[i]->getPos(), var[i]->getText(), var[i]->getColor());
            }
        }
        stack.pop();
    }
    RefreshImage();
}

extern "C" IGraph *loadLib()
{
    return new OpenGlGraph();
}

void OpenGlGraph::Set2DMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0f, m_win.x, m_win.y, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    m_render_mode = ORTHOGRAPHIC;
}

void OpenGlGraph::Set3DMode()
{
    glViewport(0, 0, (int) m_win.x, (int) m_win.y);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(70, m_win.x / m_win.y, 1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    m_render_mode = PERSPECTIVE;
}

// Drw text on viewport
void OpenGlGraph::DrawText(Vector2<int> pos, std::string const &text, AComponent::ComponentColor const &color)
{
    // IMPORTANT : change the color before rasterizing !!
    glColor3ub(colors[color].r, colors[color].g, colors[color].b);

    glRasterPos2d(pos.x * m_size_coeff + (7 * (text.size())), (pos.y) * m_size_coeff);
    for (unsigned int i = 0; i < text.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}
