//
// Created by veyrie_f on 3/10/16.
//

#include "OpenGlGraph.hpp"
#include "../../Arcade.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"
#include "../../Commons/include/DualTextComponent.hpp"
#include "../../Commons/include/AnimationComponent.hpp"
#include "../SDL2_mixer/SDL_mixer.h"
#include "../../Commons/AudioComponent.hpp"

// Ctor:
// Initializes Projection mode (3D by default) and Lighting
OpenGlGraph::OpenGlGraph(int width, int, const char *name) :
        m_size_coeff(width / ArcadeSystem::winWidth),
        m_win(ArcadeSystem::winWidth * m_size_coeff, ArcadeSystem::winHeight * m_size_coeff)
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

    // Key binds
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
    keyCodeAssociation[SDL_SCANCODE_RETURN] = ArcadeSystem::Enter;
    keyCodeAssociation[SDL_SCANCODE_BACKSPACE] = ArcadeSystem::Backspace;

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

    // activates alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    glTranslated(ArcadeSystem::winWidth / 2.0, 0, 0);
    DrawTerrain(ArcadeSystem::winWidth, ArcadeSystem::winHeight);
}

void OpenGlGraph::DrawSphere(Vector2<double> pos, AComponent::ComponentColor color, double size, double posZ) const
{
    GLUquadric *param;

    glPushMatrix();
    glTranslated(-pos.x, -posZ, -pos.y);
    param = gluNewQuadric();
    glColor4d(colors[color].r, colors[color].g, colors[color].b, 1);
    gluSphere(param, size, 20, (size >= 1) ? 20 : (size >= 0.5) ? 10 : 5);
    gluDeleteQuadric(param);
    glPopMatrix();
}

void OpenGlGraph::DrawCube(Vector2<double> pos, AComponent::ComponentColor color, double size, double posY) const
{
    glPushMatrix();
    glTranslated(-pos.x, -posY, -pos.y);

    // Byte color
    glColor3ub(colors[color].r, colors[color].g, colors[color].b);

    glutSolidCube(size);

    glPopMatrix();
}

void OpenGlGraph::DrawCube(Vector2<double> pos, GLubyte r, GLubyte g, GLubyte b, double posY) const
{
    glPushMatrix();
    glTranslated(-pos.x, -posY, -pos.y);

    // Byte color
    //glColor3ub(r, g, b);
    glColor4ub(r, g, b, 255);

    glutSolidCube(1);

    glPopMatrix();
}

void OpenGlGraph::DrawTerrain(int sizeX, int sizeY) const
{
    for (int i = 0; i < sizeX; ++i)
    {
        for (int j = 0; j < sizeY; ++j)
        {
            if (i == -1 || j == -1 || i == sizeX || j == sizeY)
            {
                //DrawCube(Vector2<double>(i, j), AComponent::COLOR_YELLOW);
            }
            DrawCube(Vector2<double>(i, j), 152, 152, 152, 1);
        }
    }
}

// Returns key pressed
int OpenGlGraph::eventManagment()
{
    std::map<int, int>::const_iterator  it;
    int                                 key = -1;

    while (SDL_PollEvent(&event) == 1)
    {
        if (event.type == SDL_KEYDOWN)
        {
            key = event.key.keysym.sym;
            if ((it = keyCodeAssociation.find(event.key.keysym.scancode)) != keyCodeAssociation.end())
                return it->second;
        }
    }
    return key;
}

// Handles data display
void OpenGlGraph::display(std::stack<AComponent *> stack)
{
    GameComponent *gc;
    UIComponent *uic;
    HighScoreComponent *hsc;
    AnimationComponent *ac;
    AudioComponent *auc;
    bool bIsBackrgoundDrawn = false;

    Set3DMode();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    while (!stack.empty())
    {
        if ((gc = dynamic_cast<GameComponent *>(stack.top())) != nullptr)
        {
            if (m_render_mode == ORTHOGRAPHIC)
            {
                Set3DMode();
            }
            if (!bIsBackrgoundDrawn)
            {
                bIsBackrgoundDrawn = true;
                DrawBackground();
            }
            switch (gc->getSprite3D())
            {
                case GameComponent::Shapes::SPHERE_LARGE:
                    DrawSphere(gc->getPos(), gc->getColor(), 0.5);
                    break;
                case GameComponent::Shapes::SPHERE_MEDIUM:
                    DrawSphere(gc->getPos(), gc->getColor(), 0.30);
                    break;
                case GameComponent::Shapes::SPHERE_SMALL:
                    DrawSphere(gc->getPos(), gc->getColor(), 0.20);
                    break;
                case GameComponent::Shapes::CUBE_LARGE:
                    DrawCube(gc->getPos(), gc->getColor(), 1);
                    break;
                case GameComponent::Shapes::CUBE_MEDIUM:
                    DrawCube(gc->getPos(), gc->getColor(), 0.5);
                    break;
                case GameComponent::Shapes::CUBE_SMALL:
                    DrawCube(gc->getPos(), gc->getColor(), 0.25);
                    break;
            }
        }
        else if ((auc = dynamic_cast<AudioComponent*>(stack.top())) != nullptr)
        {
            m_sound.PlaySound(auc->getSoundPath(), auc->getLoop(), auc->getOverlap(), auc->getStop());
        }
        else if ((uic = dynamic_cast<UIComponent *>(stack.top())) != nullptr)
        {
            if (m_render_mode == PERSPECTIVE)
            {
                Set2DMode();
            }
            DualTextComponent *dtc;
            if ((dtc = dynamic_cast<DualTextComponent*>(stack.top())) != nullptr)
            {
                DrawText(dtc->getPos(), dtc->getText(), dtc->getColor(), dtc->getDim());
                DrawText(dtc->getSubPos(), dtc->getSubTitle(), dtc->getColor(), dtc->getSubDim());
            }
            else
            {
                DrawText(uic->getPos(), uic->getText(), uic->getColor(), uic->getDim());
            }
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
                DrawText(var[i]->getPos(), var[i]->getText(), var[i]->getColor(), var[i]->getDim());
            }
        }
        else if ((ac = dynamic_cast<AnimationComponent *>(stack.top())) != nullptr)
        {
            /// If we have an anim component that means we are on the menu. So we DO NOT display the terrain
            if (m_render_mode == ORTHOGRAPHIC)
            {
                Set3DMode();
            }
            DrawBackgroundMenu();
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

// Draw text on viewport
void OpenGlGraph::DrawText(Vector2<double> pos, std::string const &text, AComponent::ComponentColor const &color, Vector2<double> dim)
{
    // IMPORTANT : change the color before rasterizing !!
    glColor3ub(colors[color].r, colors[color].g, colors[color].b);

    //glRasterPos2d(pos.x * m_size_coeff /*+ (7 * (text.size()))*/, (pos.y) * m_size_coeff);
    glRasterPos2d((pos.x + dim.x / 2.0) * 20.0,
                  (pos.y + dim.y / 2.0) * 25.0);
    for (unsigned int i = 0; i < text.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void OpenGlGraph::DrawBackgroundMenu()
{
    unsigned int i;

    glRotated(ang += 0.25, 0, 0, 1);
    // To avoid overflow
    if (static_cast<int>(ang * 10) % 10 == 0 && static_cast<int>(ang) % 360 == 0)
    {
        ang = 0;
    }
    for (i = 0; m_spheres.size() < 2500; ++i)
    {
        m_spheres.push_back(SphereMenu());
    }
    for (i = 0; i < m_spheres.size(); ++i)
    {
        DrawSphere(m_spheres[i].GetPos(), m_spheres[i].GetColor(), 0.5, m_spheres[i].GetPosZ());
        m_spheres[i].Update();
    }
}

/**
 * \brief Setting the title of the window
 *
 * \param title The title of the new Window
 */
void OpenGlGraph::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(m_window, title.c_str());
}