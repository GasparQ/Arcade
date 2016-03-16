//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Ghost.hpp"

Ghost::Ghost(AComponent::ComponentColor color) : PacmanCharacter(Vector2<int>(25, 15), color, "", " ",
                                 GameComponent::Shapes::CUBE)
{

}

Ghost::~Ghost()
{

}

Vector2<int> const& Ghost::Move(char map[31][51])
{
    return m_pos;
}
