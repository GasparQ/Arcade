//
// UIComponent.cpp for UICompoentn in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:38:49 2016 Victor Gouet
// Last update Fri Mar 11 17:25:08 2016 Victor Gouet
//

#include "../include/UIComponent.hpp"

UIComponent::UIComponent(Vector2<double> const &pos, enum ComponentColor color,
			 Vector2<double> const &dim, std::string const &text) :
  AComponent(pos, color), dim(dim), text(text) 
{

}

UIComponent::~UIComponent()
{

}

Vector2<double> const &UIComponent::getDim() const
{
  return (this->dim);
}

std::string const &UIComponent::getText() const
{
  return (this->text);
}
