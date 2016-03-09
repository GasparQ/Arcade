//
// AComponent.cpp for Component in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:24:16 2016 Victor Gouet
// Last update Wed Mar  9 15:44:39 2016 Victor Gouet
//


#include "../include/AComponent.hpp"

AComponent::AComponent(int x, int y) : pos(Vector2(x, y))
{
}

AComponent::AComponent(Vector2 const &pos) : pos(pos)
{
}

AComponent::~AComponent()
{
}

Vector2 const &AComponent::getPos() const
{
  return (this->pos);
}
