//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Pacman.hpp"

Vector2<int> const &Pacman::Move(char m_map[31][51], Vector2<int>)
{
    if (m_pos.x == 0)
    {
        m_pos.x = 50;
    }
    else if (m_pos.x == 50)
    {
        m_pos.x = 0;
    }
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

Pacman::Pacman() : PacmanCharacter(Vector2<int>(25, 18), AComponent::ComponentColor::COLOR_YELLOW, "sprites/pacman.bmp", " ",
                                   GameComponent::Shapes::SPHERE_LARGE)
{

}

Pacman::~Pacman()
{

}

Pacman::PacmanState Pacman::GetState() const
{
    return m_state;
}

void Pacman::SetState(Pacman::PacmanState state)
{
    m_state = state;
}

void Pacman::ResetPosition()
{
    m_state = MORTAL;
    PacmanCharacter::ResetPosition();
}
