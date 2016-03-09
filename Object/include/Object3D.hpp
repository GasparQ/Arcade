//
// Object3D.hpp for Object3D in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:50:41 2016 Victor Gouet
// Last update Wed Mar  9 11:03:55 2016 Victor Gouet
//

#ifndef OBJECT3D_HPP_
# define OBJECT3D_HPP_

# include "Object.hpp"

class	Object3D : public Object
{
private:
  void *fptr;
  enum ShapeEnum {SPHERE, CUBE, PLAN, CONE, CYLINDER, DISK};
  enum ShapeEnum type;

public:
  Object3D(void *fptr, enum ShapeEnum type,
	   Vector2 const &coord, Vector2 const &dim);
  virtual ~Object3D();

public:
  void *getFptr() const;
  ShapeEnum getType() const;
};

#endif
