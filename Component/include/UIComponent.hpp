//
// UIComponent.hpp for UIComponent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:38:55 2016 Victor Gouet
// Last update Wed Mar  9 15:45:02 2016 Victor Gouet
//

#ifndef UICOMPONENT_HPP_
# define UICOMPONENT_HPP_

# include <iostream>
# include "AComponent.hpp"

class	UIComponent : public AComponent
{
private:
  Vector2 dim;
  std::string text;

public:
  UIComponent(std::string const &, Vector2 const &dim, Vector2 const &pos);
  virtual ~UIComponent();

public:
  Vector2 const &getDim() const;
  std::string const &getText() const;
};

#endif
