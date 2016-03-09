//
// ObjectTerm.cpp for ObjectTerm in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:42:16 2016 Victor Gouet
// Last update Wed Mar  9 10:56:01 2016 Victor Gouet
//

#include "ObjectTerm.hpp"

ObjectTerm::ObjectTerm(char c, Vector2 const &coord, Vector2 const &dim) : Object(coord, dim)
{
  this->carac = c;
}

ObjectTerm::~ObjectTerm()
{

}

char ObjectTerm::getCaract() const
{
  return (this->carac);
}
