//
// Created by veyrie_f on 3/15/16.
//

#include "../include/PacmanCharacter.hpp"

PacmanCharacter::PacmanCharacter(Vector2<double > pos, AComponent::ComponentColor color, std::string const& shape2D,
                                 std::string const& shapeCurses, GameComponent::Shapes shape3D) :
        m_pos(pos),
        m_initPos(pos),
        m_color(color),
        m_shape2D(shape2D),
        m_shapeCurses(shapeCurses),
        m_shape3D(shape3D)
{

}

PacmanCharacter::~PacmanCharacter()
{

}

void PacmanCharacter::ResetPosition()
{
    m_pos = m_initPos;
}

Vector2<double> const &PacmanCharacter::getPosition() const
{
    return m_pos;
}

AComponent::ComponentColor PacmanCharacter::getColor() const
{
    return m_color;
}

GameComponent::Shapes PacmanCharacter::getShape3D() const
{
    return m_shape3D;
}

std::string const &PacmanCharacter::getShape2D() const
{
    return m_shape2D;
}

std::string const &PacmanCharacter::getShapeCurses() const
{
    return m_shapeCurses;
}
