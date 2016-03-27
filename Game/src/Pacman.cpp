//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Pacman.hpp"

Vector2<double> const &Pacman::Move(char m_map[31][51], Vector2<double>)
{
    /// Side teleporters
    if (m_pos.x == 0)
    {
        m_pos.x = 50;
    }
    else if (m_pos.x == 50)
    {
        m_pos.x = 0;
    }

    /// We check if we can pop the last input we saved
    if (!m_dir_stack.empty())
    {
        if (m_map[(int)m_pos.y - 1][(int)m_pos.x] != 'X' && m_dir_stack.top() == UP)
        {
            m_dir = m_dir_stack.top();
            m_dir_stack.pop();
        }
        else if (m_map[(int)m_pos.y + 1][(int)m_pos.x] != 'X' && m_dir_stack.top() == DOWN)
        {
            m_dir = m_dir_stack.top();
            m_dir_stack.pop();
        }
        else if (m_map[(int)m_pos.y][(int)m_pos.x - 1] != 'X' && m_dir_stack.top() == LEFT)
        {
            m_dir = m_dir_stack.top();
            m_dir_stack.pop();
        }
        else if (m_map[(int)m_pos.y][(int)m_pos.x + 1] != 'X' && m_dir_stack.top() == RIGHT)
        {
            m_dir = m_dir_stack.top();
            m_dir_stack.pop();
        }
    }

    /// Then we try to move this little guy
    switch (m_dir)
    {
        case UP:
            if (m_map[(int)m_pos.y - 1][(int)m_pos.x] != 'X')
            {
                --m_pos.y;
            }
            break;
        case DOWN:
            if (m_map[(int)m_pos.y + 1][(int)m_pos.x] != 'X')
            {
                ++m_pos.y;
            }
            break;
        case LEFT:
            if (m_map[(int)m_pos.y][(int)m_pos.x - 1] != 'X')
            {
                --m_pos.x;
            }
            break;
        case RIGHT:
            if (m_map[(int)m_pos.y][(int)m_pos.x + 1] != 'X')
            {
                ++m_pos.x;
            }
            break;
    }
    return m_pos;
}

Pacman::Pacman() : PacmanCharacter(Vector2<double >(25, 18), AComponent::ComponentColor::COLOR_YELLOW, "sprites/pacman.bmp", " ",
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

void Pacman::goUp(char [31][51])
{
    if (m_pos.y - 1 < 0)
        return;
    if (!m_dir_stack.empty() || m_dir_stack.size() >= m_max_key_buff)
    {
        m_dir_stack.pop();
    }
    m_dir_stack.push(UP);
}

void Pacman::goDown(char [31][51])
{
    if (m_pos.y + 1 >= 31)
        return;
    if (!m_dir_stack.empty() || m_dir_stack.size() >= m_max_key_buff)
    {
        m_dir_stack.pop();
    }
    m_dir_stack.push(DOWN);
}

void Pacman::goLeft(char [31][51])
{
    if (m_pos.x - 1 < 0)
        return;
    if (!m_dir_stack.empty() || m_dir_stack.size() >= m_max_key_buff)
    {
        m_dir_stack.pop();
    }
    m_dir_stack.push(LEFT);
}

void Pacman::goRight(char [31][51])
{
    if (m_pos.x + 1 >= 51)
        return;
    if (!m_dir_stack.empty() || m_dir_stack.size() >= m_max_key_buff)
    {
        m_dir_stack.pop();
    }
    m_dir_stack.push(RIGHT);
}