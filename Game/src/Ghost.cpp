//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Ghost.hpp"
#include "../../Commons/Astar.hpp"

Ghost::Ghost(AComponent::ComponentColor color) : PacmanCharacter(Vector2<int>(25, 15), color, "", " ",
                                 GameComponent::Shapes::CUBE)
{

}

Ghost::~Ghost()
{

}

Vector2<int> const& Ghost::Move(char map[31][51])
{
    Astar as(map);
    std::string dir = as.pathFind(m_pos.x, m_pos.y, 1, 28);

    if (dir == "")
    {
        return m_pos;
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
    return m_pos;
}

void Ghost::goUp(char map[31][51])
{
    //PacmanCharacter::goUp(map);
}

void Ghost::goDown(char (*map)[51])
{
    //PacmanCharacter::goDown(map);
}

void Ghost::goLeft(char (*map)[51])
{
    //PacmanCharacter::goLeft(map);
}

void Ghost::goRight(char (*map)[51])
{
    //PacmanCharacter::goRight(map);
}
