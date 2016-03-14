//
// Vector2.hpp for Vector2 in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Vector
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:27:01 2016 Victor Gouet
// Last update Wed Mar  9 10:28:18 2016 Victor Gouet
//

#ifndef VECTOR2_HPP_
# define VECTOR2_HPP_

# include <cstdlib>

template <class T>
class	Vector2
{
public:
    T 	x;
    T     y;

public:
    Vector2(T x, T y);
    ~Vector2();
    Vector2     operator+(Vector2 const &);
    bool        operator==(Vector2 const &);
    Vector2     invert();
};

#endif
