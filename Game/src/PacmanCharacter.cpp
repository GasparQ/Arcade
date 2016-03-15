//
// Created by veyrie_f on 3/15/16.
//

#include "../include/PacmanCharacter.hpp"

PacmanCharacter::PacmanCharacter(Vector2<int> pos) :
m_pos(pos),
m_initPos(pos)
{

}

PacmanCharacter::~PacmanCharacter()
{

}

void PacmanCharacter::ResetPosition()
{
    m_pos = m_initPos;
}

Vector2<int> const &PacmanCharacter::getPosition() const
{
    return m_pos;
}