//
// Created by veyrie_f on 3/15/16.
//

#include "../include/Ghost.hpp"

Ghost::Ghost() : PacmanCharacter(Vector2<int>(25, 15), AComponent::ComponentColor::COLOR_GREEN, "", " ",
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
