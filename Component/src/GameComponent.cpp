//
// GameComponent.cpp for Component in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:31:48 2016 Victor Gouet
// Last update Wed Mar  9 15:50:47 2016 Victor Gouet
//


#include "../include/GameComponent.hpp"

GameComponent::GameComponent(Vector2 const &pos, void *sprite3D, std::string const &spriteText,
                             std::string const &sprite2D)
  : AComponent(pos), sprite3D(sprite3D), spriteText(spriteText), fileSprite2D(sprite2D)
{
}

GameComponent::~GameComponent()
{

}

std::string const	&GameComponent::getSpriteText() const
{
  return (this->spriteText);
}

std::string const	&GameComponent::getSprite2D() const
{
  return (this->fileSprite2D);
}

void			*GameComponent::getSprite3D() const
{
  return (this->sprite3D);
}
