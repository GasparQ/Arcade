//
// Object2D.hpp for Object2D in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:44:37 2016 Victor Gouet
// Last update Wed Mar  9 10:55:46 2016 Victor Gouet
//

#ifndef OBJECT2D_HPP_
# define OBJECT2D_HPP_

# include <iostream>
# include "Object.hpp"

class	Object2D : public Object
{
private:
  std::string	fileName;

public:
  Object2D(std::string const &newFileName,
	   Vector2 const &coord, Vector2 const &dim);
  virtual ~Object2D();
  
public:
  std::string const &getFileName() const;
};

#endif
