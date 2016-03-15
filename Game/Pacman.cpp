//
// Created by veyrie_f on 3/15/16.
//

#include "Pacman.hpp"

Vector2<int> const&Pacman::Move(char m_map[31][51])
{
    Vector2<int> nextPos = m_pos;

    switch (m_dir)
    {
        case UP:
            if (m_map[m_pos.y - 1][m_pos.x] != 'X')
            {
                --m_pos.y;
            }
            break;
        case DOWN:
            if (m_map[m_pos.y + 1][m_pos.x] != 'X')
            {
                ++m_pos.y;
            }
            break;
        case LEFT:
            if (m_map[m_pos.y][m_pos.x - 1] != 'X')
            {
                --m_pos.x;
            }
            break;
        case RIGHT:
            if (m_map[m_pos.y][m_pos.x + 1] != 'X')
            {
                ++m_pos.x;
            }
            break;
    }
    return m_pos;
}

Pacman::Pacman() : PacmanCharacter(Vector2<int>(25, 29))
{

}

Pacman::~Pacman()
{

}
