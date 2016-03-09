//
// Object3D.cpp for Object3D in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:50:32 2016 Victor Gouet
// Last update Wed Mar  9 11:03:59 2016 Victor Gouet
//

#include "Object3D.hpp"


Object3D::Object3D(void *fptr, enum ShapeEnum type,
	 Vector2 const &coord, Vector2 const &dim) : Object(coord, dim)
{
  this->fptr = fptr;
  this->type = type;
}

Object3D::~Object3D()
{
}

void *Object3D::getFptr() const
{
  return (this->fptr);
}

Object3D::ShapeEnum Object3D::getType() const
{
  return (this->type);
}
