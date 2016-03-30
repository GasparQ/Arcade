//
// AnimationComponent.cpp for AnimationComponent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Commons
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Mar 18 12:07:28 2016 Victor Gouet
// Last update Fri Mar 18 14:05:48 2016 Victor Gouet
//

#include "../include/AnimationComponent.hpp"

AnimationComponent::AnimationComponent(int x, int y, enum ComponentColor color,
				       std::string const &file)
  : AComponent(x, y, color), file(file)
{
}

AnimationComponent::~AnimationComponent()
{
  
}

std::string const &AnimationComponent::getFileName() const
{
  return (file);
}

void AnimationComponent::setFileName(const std::string &string)
{
    file = string;
}
