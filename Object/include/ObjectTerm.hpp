//
// ObjectTerm.hpp for Object in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Object
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:39:20 2016 Victor Gouet
// Last update Wed Mar  9 10:56:25 2016 Victor Gouet
//

#ifndef OBJECTTERM_HPP_
# define OBJECTTERM_HPP_

# include "Object.hpp"

class	ObjectTerm : public Object
{
private:
  char	carac;

public:
  ObjectTerm(char c, Vector2 const &coord, Vector2 const &dim);
  virtual ~ObjectTerm();

public:
  char getCaract() const;
};

#endif
