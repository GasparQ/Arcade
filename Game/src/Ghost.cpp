//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Ghost.hpp"
#include "../../Commons/include/Astar.hpp"

Ghost::Ghost(AComponent::ComponentColor color, std::string const& shape2D) : PacmanCharacter(Vector2<double>(25, 15), color,
                                                                 shape2D, " ",
                                                                 GameComponent::Shapes::CUBE)
{
    m_color_original = m_color;
    m_default_sprite = shape2D;
}

Ghost::~Ghost()
{

}

Vector2<double> const &Ghost::Move(char map[31][51], Vector2<double> pacmanPos)
{
    Astar as(map);
    std::string dir;
    Vector2<double> target;

    // If the ghost is frozen, he cannot move
    if (m_state == FREEZE)
    {
        return m_pos;
    }

    if (m_state == HUNTING)
    {
        dir = as.pathFind((int) m_pos.x, (int) m_pos.y, (int) pacmanPos.x, (int) pacmanPos.y);
    }
    else if (m_state == SCARED)
    {
        target.x = (pacmanPos.x < 25) ? 48 : 1;
        target.y = (pacmanPos.y < 15) ? 28 : 1;
        dir = as.pathFind((int) m_pos.x, (int) m_pos.y, (int) target.x, (int) target.y);
    }
    else if (m_state == DEAD)
    {
        dir = as.pathFind((int) m_pos.x, (int) m_pos.y, 25, 16);
    }

    if (static_cast<int>(m_pos.x * 10.0) % 10 == 0 && static_cast<int>(m_pos.y * 10.0) % 10 == 0)
    {
        if (!dir.empty())
        {
            m_curr_dir = dir[0];
        }
        else
        {
            m_curr_dir = 0;
        }
    }

    /*switch (m_state)
    {
        case HUNTING:
            dir = as.pathFind(m_pos.x, m_pos.y, pacmanPos.x, pacmanPos.y);
            break;
        case SCARED:
            // We target the farthest corner from pacman
            target.x = (pacmanPos.x < 25) ? 48 : 1;
            target.y = (pacmanPos.y < 15) ? 28 : 1;
            dir = as.pathFind(m_pos.x, m_pos.y, target.x, target.y);

            dir[0] = (map[m_pos.y][m_pos.x - 1] != 'X' && dir[0] != '2') ? '2' :
                     (map[m_pos.y][m_pos.x + 1] != 'X' && dir[0] != '0') ? '0' :
                     (map[m_pos.y - 1][m_pos.x] != 'X' && dir[0] != '3') ? '3' :
                     (map[m_pos.y + 1][m_pos.x] != 'X' && dir[0] != '1') ? '1' : dir[0];
            break;
        case DEAD:
            dir = as.pathFind(m_pos.x, m_pos.y, 25, 17);
            break;
    }*/

    if (m_curr_dir == '0')
    {
        //++m_pos.x;
        m_pos.x += velocity;
    }
    else if (m_curr_dir == '1')
    {
        //++m_pos.y;
        m_pos.y += velocity;
    }
    else if (m_curr_dir == '2')
    {
        //--m_pos.x;
        m_pos.x -= velocity;
    }
    else if (m_curr_dir == '3')
    {
        //--m_pos.y;
        m_pos.y -= velocity;
    }

    // If the ghost is back to base, he can hunt again
    if (m_pos.x >= 24 && m_pos.x <= 28 && m_pos.y >= 13 && m_pos.y <= 16)
    {
        SetState(HUNTING);
    }
    return m_pos;
}

void Ghost::goUp(char [31][51])
{
    //PacmanCharacter::goUp(map);
}

void Ghost::goDown(char (*)[51])
{
    //PacmanCharacter::goDown(map);
}

void Ghost::goLeft(char (*)[51])
{
    //PacmanCharacter::goLeft(map);
}

void Ghost::goRight(char (*)[51])
{
    //PacmanCharacter::goRight(map);
}

void Ghost::SetState(GhostState state)
{
    m_state = state;
    if (m_state == DEAD)
    {
        m_shapeCurses = "\"";
        m_shape2D = "sprites/ghost_eyes.bmp";
        velocity = 0.250000000;
        if (static_cast<int>(m_pos.x * 100.0) % 25 != 0)
        {
            m_pos.x = round(m_pos.x);
        }
        if (static_cast<int>(m_pos.y * 100.0) % 25 != 0)
        {
            m_pos.y = round(m_pos.y);
        }
    }
    else if (m_state == SCARED)
    {
        m_color = AComponent::ComponentColor::COLOR_BLUE;
        m_shape2D = "sprites/feared_ghost.bmp";
        velocity = 0.100000;
        if (static_cast<int>(m_pos.x * 100.0) % 10 != 0)
        {
            m_pos.x = round(m_pos.x);
        }
        if (static_cast<int>(m_pos.y * 100.0) % 10 != 0)
        {
            m_pos.y = round(m_pos.y);
        }
    }
    else
    {
        m_shapeCurses = " ";
        m_color = m_color_original;
        m_shape2D = m_default_sprite;
        velocity = 0.250000000;
        if (static_cast<int>(m_pos.x * 100.0) % 25 != 0)
        {
            m_pos.x = round(m_pos.x);
        }
        if (static_cast<int>(m_pos.y * 100.0) % 25 != 0)
        {
            m_pos.y = round(m_pos.y);
        }
    }
}

Ghost::GhostState Ghost::GetState() const
{
    return m_state;
}

void Ghost::ResetPosition()
{
    m_state = FREEZE;
    PacmanCharacter::ResetPosition();
}
