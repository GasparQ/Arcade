//
// AComponent.hpp for AComonent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:22:30 2016 Victor Gouet
// Last update Wed Mar  9 15:26:16 2016 Victor Gouet
//

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

#include "../../Vector/include/Vector2.hpp"

class	AComponent
{
private:
  Vector2	pos;
  
public:
  AComponent(int x, int y);
  AComponent(Vector2 const &pos);
  virtual ~AComponent();

public:
  Vector2 const &getPos() const;
};

#endif
