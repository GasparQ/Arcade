//
// GameComponent.cpp for Component in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:31:48 2016 Victor Gouet
// Last update Fri Mar 11 17:22:15 2016 Victor Gouet
//


#include "../include/GameComponent.hpp"

GameComponent::GameComponent(
        Vector2<double> const &pos,
        AComponent::ComponentColor color,
        Shapes sprite3D,
        std::string const &spriteText,
        std::string const &sprite2D
) : AComponent(pos, color), sprite3D(sprite3D),
    spriteText(spriteText),
    fileSprite2D(sprite2D),
    dim(1, 1)
{
}

GameComponent::GameComponent(Vector2<double> const &pos, Vector2<double> const &size, AComponent::ComponentColor color,
                             char const &spriteText, std::string const &sprite2D, GameComponent::Shapes sprite3D) :
    AComponent(pos, color),
    sprite3D(sprite3D),
    spriteText(std::string("").insert(0, 1, spriteText)),
    fileSprite2D(sprite2D),
    dim(size)
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

GameComponent::Shapes GameComponent::getSprite3D() const
{
  return (this->sprite3D);
}

void GameComponent::setSpriteText(const char &spriteText)
{
    this->spriteText = spriteText;
}

void GameComponent::setSprite2D(const std::string &sprite2D)
{
    fileSprite2D = sprite2D;
}

void GameComponent::setSprite3D(GameComponent::Shapes sprite3D)
{
    this->sprite3D = sprite3D;
}

Vector2<double> const &GameComponent::getDim() const
{
    return dim;
}

void GameComponent::setSpriteText(const std::string &string)
{
    spriteText = string;

}
