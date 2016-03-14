//
// Vector2.cpp for Vector2 in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Vector
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 10:26:46 2016 Victor Gouet
// Last update Wed Mar  9 10:28:50 2016 Victor Gouet
//


#include "../include/Vector2.hpp"

template <class T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y)
{
}

template <class T>
Vector2<T>::~Vector2()
{
}

template <class T>
Vector2<T>     Vector2<T>::operator+(const Vector2<T> &vector2)
{
    return Vector2<T>(x + vector2.x, y + vector2.y);
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T> &vector2)
{
    return x == vector2.x && y == vector2.y;
}

template <class T>
Vector2<T> Vector2<T>::invert()
{
    return Vector2<T>(-x, -y);
}
