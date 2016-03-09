//
// Vector3.hpp for Vector in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Vector
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:21:52 2016 Victor Gouet
// Last update Wed Mar  9 10:24:49 2016 Victor Gouet
//

#ifndef VECTOR3_HPP_
# define VECTOR3_HPP_

# include <cstdlib>

class	Vector3
{
public:
  size_t	x;
  size_t	y;
  size_t	z;

public:
  Vector3(size_t x, size_t y, size_t z);
  ~Vector3();
};

#endif
