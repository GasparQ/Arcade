//
// Object2D.cpp for Object in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:46:38 2016 Victor Gouet
// Last update Wed Mar  9 10:55:36 2016 Victor Gouet
//

#include "Object2D.hpp"

Object2D::Object2D(std::string const &newFileName,
	 Vector2 const &coord, Vector2 const &dim) : Object(coord, dim)
{
  this->fileName = newFileName;
}

Object2D::~Object2D()
{
}

std::string const &Object2D::getFileName() const
{
  return (this->fileName);
}
