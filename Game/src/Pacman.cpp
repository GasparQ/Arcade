//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Pacman.hpp"

Vector2<double> const &Pacman::Move(char m_map[31][51], Vector2<double>)
{
    /// Side teleporters
    if (m_pos.x < 0 + velocity)
    {
        m_pos.x = 49;
    }
    else if (m_pos.x > 49 + velocity)
    {
        m_pos.x = 1;
    }

    /// We try to change direction if we are perfectly on the center of a square pos
    if (static_cast<int>(m_pos.x * 10.0) % 10 == 0 && static_cast<int>(m_pos.y * 10.0) % 10 == 0)
    {
        /// We check if we can pop the last input we saved
        if (!m_dir_stack.empty())
        {
            if (m_map[(int) floor(m_pos.y - velocity)][(int) round(m_pos.x)] != 'X' && m_dir_stack.top() == UP)
            {
                m_dir = m_dir_stack.top();
                m_dir_stack.pop();
            }
            else if (m_map[(int) ceil(m_pos.y + velocity)][(int) round(m_pos.x)] != 'X' && m_dir_stack.top() == DOWN)
            {
                m_dir = m_dir_stack.top();
                m_dir_stack.pop();
            }
            else if (m_map[(int) round(m_pos.y)][(int) floor(m_pos.x - velocity)] != 'X' && m_dir_stack.top() == LEFT)
            {
                m_dir = m_dir_stack.top();
                m_dir_stack.pop();
            }
            else if (m_map[(int) round(m_pos.y)][(int) ceil(m_pos.x + velocity)] != 'X' && m_dir_stack.top() == RIGHT)
            {
                m_dir = m_dir_stack.top();
                m_dir_stack.pop();
            }
        }
    }

    /// Then we try to move this little guy
    switch (m_dir)
    {
        case UP:
            if (m_map[(int)floor(m_pos.y - velocity)][(int)round(m_pos.x)] != 'X')
            {
                //--m_pos.y;
                m_pos.y -= velocity;
                m_pos.x = round(m_pos.x);
            }
            break;
        case DOWN:
            if (m_map[(int)ceil(m_pos.y + velocity)][(int)round(m_pos.x)] != 'X')
            {
                //++m_pos.y;
                m_pos.y += velocity;
                m_pos.x = round(m_pos.x);
            }
            break;
        case LEFT:
            if (m_map[(int)round(m_pos.y)][(int)floor(m_pos.x - velocity)] != 'X')
            {
                //--m_pos.x;
                m_pos.x -= velocity;
                m_pos.y = round(m_pos.y);
            }
            break;
        case RIGHT:
            if (m_map[(int)round(m_pos.y)][(int)ceil(m_pos.x + velocity)] != 'X')
            {
                //++m_pos.x;
                m_pos.x += velocity;
                m_pos.y = round(m_pos.y);

            }
            break;
    }
    _pacman_body = (_pacman_body + 0.2);
    return m_pos;
}

Pacman::Pacman() : PacmanCharacter(Vector2<double >(25, 18),
				   AComponent::ComponentColor::COLOR_YELLOW,
				   "sprites/pacman.bmp", " ", GameComponent::Shapes::SPHERE_LARGE)
{
  sprite[UP][0] = "sprites/closed.bmp";
  sprite[DOWN][0] = "sprites/closed.bmp";
  sprite[LEFT][0] = "sprites/closed.bmp";
  sprite[RIGHT][0] = "sprites/closed.bmp";

  sprite[UP][1] = "sprites/pacman_up.bmp";
  sprite[DOWN][1] = "sprites/pacman_down.bmp";
  sprite[LEFT][1] = "sprites/pacman_left.bmp";
  sprite[RIGHT][1] = "sprites/pacman_right.bmp";
  
  sprite[UP][2] = "sprites/open_up.bmp";
  sprite[DOWN][2] = "sprites/open_down.bmp";
  sprite[LEFT][2] = "sprites/open_left.bmp";
  sprite[RIGHT][2] = "sprites/open_right.bmp";

  sprite[UP][3] = "sprites/pacman_up.bmp";
  sprite[DOWN][3] = "sprites/pacman_down.bmp";
  sprite[LEFT][3] = "sprites/pacman_left.bmp";
  sprite[RIGHT][3] = "sprites/pacman_right.bmp";

  _pacman_body = OPEN;
}

Pacman::~Pacman()
{

}

Pacman::PacmanState Pacman::GetState() const
{
    return m_state;
}

std::string const &Pacman::getShape2D() const
{
  return (sprite[m_dir][static_cast<int>(_pacman_body) % 4]);
}

void Pacman::SetState(Pacman::PacmanState state)
{
    m_state = state;
}

void Pacman::ResetPosition()
{
    m_state = MORTAL;
    m_dir = LEFT;
    while (!m_dir_stack.empty())
    {
        m_dir_stack.pop();
    }
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
