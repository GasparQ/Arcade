//
// AComponent.hpp for AComonent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:22:30 2016 Victor Gouet
// Last update Fri Mar 11 17:33:55 2016 Victor Gouet
//

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

#include "../../Commons/include/Vector2.hpp"

class	AComponent
{
public:
  enum ComponentColor {COLOR_RED = 1,
		       COLOR_GREEN = 2,
		       COLOR_YELLOW = 3,
		       COLOR_BLUE = 4,
		       COLOR_MAGENTA = 5,
		       COLOR_CYAN = 6,
		       COLOR_WHITE = 7};

private:
  Vector2<int>		pos;
  enum ComponentColor	_color;
  
public:
  AComponent(int x, int y, enum ComponentColor color);
  AComponent(Vector2<int> const &pos, enum ComponentColor color);
  virtual ~AComponent();

public:
  Vector2<int> const &getPos() const;
  enum ComponentColor	getColor() const;
};

#endif
