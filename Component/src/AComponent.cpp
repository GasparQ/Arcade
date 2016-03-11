//
// AComponent.cpp for Component in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:24:16 2016 Victor Gouet
// Last update Fri Mar 11 17:29:18 2016 Victor Gouet
//


#include "../include/AComponent.hpp"

AComponent::AComponent(int x, int y,
		       enum AComponent::ComponentColor color)
  : pos(Vector2(x, y)), _color(color)
{
}

AComponent::AComponent(Vector2 const &pos,
		       enum AComponent::ComponentColor color)
  : pos(pos), _color(color)
{
}

AComponent::~AComponent()
{
}

Vector2 const &AComponent::getPos() const
{
  return (this->pos);
}

enum AComponent::ComponentColor	AComponent::getColor() const
{
  return (this->_color);
}
