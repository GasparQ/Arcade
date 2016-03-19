//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Ghost.hpp"
#include "../../Commons/Astar.hpp"

Ghost::Ghost(AComponent::ComponentColor color) : PacmanCharacter(Vector2<int>(25, 15), color, "", " ",
                                                                 GameComponent::Shapes::CUBE)
{
    m_color_original = m_color;
}

Ghost::~Ghost()
{

}

Vector2<int> const &Ghost::Move(char map[31][51], Vector2<int> pacmanPos)
{
    Astar as(map);
    std::string dir;

    switch (m_state)
    {
        // The ghost follows pacman
        case HUNTING:
            dir = as.pathFind(m_pos.x, m_pos.y, pacmanPos.x, pacmanPos.y);
            break;
            // The ghost flees pacman
        case SCARED:
        {
            // We target the farthet corner from pacman
            Vector2<int> target;
            target.x = (pacmanPos.x < 25) ? 48 : 1;
            target.y = (pacmanPos.y < 15) ? 28 : 1;
            dir = as.pathFind(m_pos.x, m_pos.y, target.x, target.y);

            /*dir[0] = (map[m_pos.y][m_pos.x - 1] != 'X' && dir[0] != '2') ? '2' :
                     (map[m_pos.y][m_pos.x + 1] != 'X' && dir[0] != '0') ? '0' :
                     (map[m_pos.y - 1][m_pos.x] != 'X' && dir[0] != '3') ? '3' :
                     (map[m_pos.y + 1][m_pos.x] != 'X' && dir[0] != '1') ? '1' : dir[0];*/
            break;
            // The ghost goes to the spawn
        }
        case DEAD:
            dir = as.pathFind(m_pos.x, m_pos.y, 25, 17);
            break;
    }

    if (dir[0] == '0')
    {
        ++m_pos.x;
    }
    else if (dir[0] == '1')
    {
        ++m_pos.y;
    }
    else if (dir[0] == '2')
    {
        --m_pos.x;
    }
    else if (dir[0] == '3')
    {
        --m_pos.y;
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
    }
    else if (m_state == SCARED)
    {
        m_color = AComponent::ComponentColor::COLOR_BLUE;
    }
    else
    {
        m_shapeCurses = " ";
        m_color = m_color_original;
    }
}

Ghost::GhostState Ghost::GetState() const
{
    return m_state;
}
