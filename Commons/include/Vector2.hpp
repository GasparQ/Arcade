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
#include <iostream>

template <class T>
class	Vector2
{
public:
    T 	x;
    T     y;

public:
    Vector2(T x, T y) : x(x), y(y)
    {}
    Vector2() : x(0), y(0)
    {}
    ~Vector2()
    {}
    Vector2     operator+(Vector2 const &vector2)
    {
        return Vector2<T>(x + vector2.x, y + vector2.y);
    }
    Vector2     operator-(Vector2 const &vector2)
    {
        return Vector2<T>(x - vector2.x, y - vector2.y);
    }
    Vector2     <T>operator*(T i)
    {
        return (Vector2<T>(x * i, y * i));
    }
    bool        operator==(Vector2 const &vector2) const
    {
        return x == vector2.x && y == vector2.y;
    }
    bool        operator>(Vector2<double> const &vector2) const
    {
        return (x > vector2.x && y > vector2.y);
    }
    bool        operator<(Vector2<double> const &vector2) const
    {
        return (x < vector2.x && y < vector2.y);
    }
    bool        operator>=(Vector2<double> const &vector2) const
    {
        return (x >= vector2.x && y >= vector2.y);
    }
    bool        operator<=(Vector2<double> const &vector2) const
    {
        return (x <= vector2.x && y <= vector2.y);
    }
    Vector2     invert()
    {
        return Vector2<T>(-x, -y);
    }
    /// Equivalent to the == operator but can also take a range in account
    bool isEqual(Vector2<T> const& other, double delta) const
    {
        return (other.x - delta <= x && x <= other.x + delta
                && other.y - delta <= y && y <= other.y + delta);
    }
};

template <class T>
std::ostream & operator<<(std::ostream & stream, Vector2<T> const& v)
{
    return stream << "{" << v.x << ", " << v.y << "}" << std::endl;
}

#endif
