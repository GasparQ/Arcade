//
// Object.cpp for Object in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:36:20 2016 Victor Gouet
// Last update Wed Mar  9 11:04:36 2016 Victor Gouet
//

#include "Object.hpp"

Object::~Object()
{
}

Object::Object(Vector2 const &newCoord, Vector2 const &newDim)
  : coord(newCoord), dim(newDim)
{
}

Vector2 const &Object::getCoord() const
{
  return (this->coord);
}

Vector2 const &Object::getDim() const
{
  return (this->dim);
}
