//
// UIComponent.cpp for UICompoentn in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:38:49 2016 Victor Gouet
// Last update Wed Mar  9 15:51:10 2016 Victor Gouet
//

#include "UIComponent.hpp"

UIComponent::UIComponent(Vector2 const &pos, Vector2 const &dim, std::string const &text) :
  AComponent(pos), dim(dim), text(text) 
{

}

UIComponent::~UIComponent()
{

}

Vector2 const &UIComponent::getDim() const
{
  return (this->dim);
}

std::string const &UIComponent::getText() const
{
  return (this->text);
}
