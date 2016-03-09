//
// Object.hpp for Objecy in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:33:34 2016 Victor Gouet
// Last update Wed Mar  9 10:38:02 2016 Victor Gouet
//

#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include "Vector2.hpp"

class	Object
{
public:
  Object(Vector2 const &newCoord, Vector2 const &newDim);
  virtual ~Object();

public:
  Vector2 const &getCoord() const;
  Vector2 const &getDim() const;

protected:
  Vector2	coord;
  Vector2	dim;
};

#endif
