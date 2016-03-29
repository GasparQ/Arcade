//
// AComponent.cpp for Component in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:24:16 2016 Victor Gouet
// Last update Tue Mar 29 01:11:09 2016 Victor Gouet
//


#include "../include/AComponent.hpp"

AComponent::AComponent(int x, int y,
		       enum AComponent::ComponentColor color)
  : pos(Vector2<double>(x, y)), _color(color)
{
}

AComponent::AComponent(Vector2<double> const &pos,
		       enum AComponent::ComponentColor color)
  : pos(pos), _color(color)
{
}

AComponent::~AComponent()
{
}

Vector2<double> const &AComponent::getPos() const
{
  return (this->pos);
}

enum AComponent::ComponentColor	AComponent::getColor() const
{
  return (this->_color);
}

void AComponent::setColor(AComponent::ComponentColor color)
{
    _color = color;
}

void AComponent::setPos(const Vector2<double> &_pos)
{
    pos = _pos;
}
