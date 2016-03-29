//
// Created by veyrie_f on 3/10/16.
//

#ifndef CPP_ARCADE_WINDOW_HPP
#define CPP_ARCADE_WINDOW_HPP

#include <map>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "./include/glut.h"
#include "../SDL2/include/SDL_surface.h"
#include "../SDL2/include/SDL.h"
#include "../../Exception/LoadException.hpp"
#include "../SDL2/include/SDL_opengl.h"
#include "../include/IGraph.hpp"
#include "../../Commons/include/GameComponent.hpp"
#include "../../Commons/include/UIComponent.hpp"

class OpenGlGraph : public IGraph
{
public:
    OpenGlGraph(int width = 1280, int height = 720, const char *name = "OpenGL Win");

    virtual ~OpenGlGraph();

public:
    virtual int eventManagment();

    virtual void display(std::stack<AComponent *>);

private:
    void DrawSphere(Vector2<double> pos, AComponent::ComponentColor color, double size, double posZ = 0) const;

    void DrawCube(Vector2<double> pos, AComponent::ComponentColor color, double size = 1, double posY = 0) const;

    void DrawCube(Vector2<double> pos, GLubyte r, GLubyte g, GLubyte b, double posY = 0) const;

    void DrawTerrain(int sizeX, int sizeY) const;

    void InitLighting() const;

    void DrawBackground() const ;

    void DrawBackgroundMenu();

    void RefreshImage() const;

    void Set2DMode();

    void Set3DMode();

    void DrawText(Vector2<double> pos, std::string const& text, AComponent::ComponentColor const& color);

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
    // Stores the coeff to resize
    double m_size_coeff;
    Vector2<double> m_win;
    std::map<int, int>  keyCodeAssociation;
    // RGBA
    SDL_Color colors[10] = {{0, 0, 0, 0}, // black
                            {255, 0, 0, 255}, // red
                            {0, 255, 0, 255}, // green
                            {255, 255, 0, 255}, // yellow
                            {0, 0, 255, 255}, // blue
                            {255, 0, 255, 255}, // magenta
                            {0, 255, 255, 255}, // cyan
                            {255, 255, 255, 255}}; // white
    RenderMode m_render_mode = PERSPECTIVE;

private:
    class SphereMenu
    {
    public:
        SphereMenu()
        {
            m_pos = Vector2<double>(rand() % 100 - 50, rand() % 100);
            m_color = static_cast<AComponent::ComponentColor>(rand() % 7 + 1);
            m_pos_z = rand() % 100 - 50;

            double dirX = m_pos.x;
            double dirZ = m_pos_z;
            while (pow(m_pos.x, 2) + pow(m_pos_z, 2) < pow(30, 2))
            {
                m_pos.x += dirX;
                m_pos_z += dirZ;
            }
            /*if (m_pos.x >= 0 && m_pos.x <= 30 && m_pos_z >= -30 && m_pos_z <= 30)
            {
                m_pos.x += 30;
                m_pos_z += 30;
            }
            if (m_pos.x >= -30 && m_pos.x <= 0 && m_pos_z >= -30 && m_pos_z <= 30)
            {
                m_pos.x -= 30;
                m_pos_z -= 30;
            }*/
        }

        ~SphereMenu()
        {}

        Vector2<double> const& GetPos() const
        {
            return m_pos;
        }

        double GetPosZ() const
        {
            return m_pos_z;
        }

        AComponent::ComponentColor GetColor() const
        {
            return m_color;
        }

        void Update()
        {
            m_pos.y += m_vel;
            if (m_pos.y <= 0)
            {
                m_pos.y = 100;
            }
        }

    private:
        AComponent::ComponentColor m_color;
        Vector2<double> m_pos;
        double m_pos_z;
        double m_vel = -0.2;
    };

    std::vector<SphereMenu> m_spheres;
    double ang = 0;
};


#endif //CPP_ARCADE_WINDOW_HPP
