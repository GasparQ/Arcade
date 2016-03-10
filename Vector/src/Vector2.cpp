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

Vector2::Vector2(int x, int y) : x(x), y(y)
{
}

Vector2::~Vector2()
{
}

Vector2     Vector2::operator+(const Vector2 &vector2)
{
    return Vector2(x + vector2.x, y + vector2.y);
}

bool Vector2::operator==(const Vector2 &vector2)
{
    if (x == vector2.x && y == vector2.y)
        return true;
    return false;
}

Vector2 Vector2::invert()
{
    return Vector2(-x, -y);
}
