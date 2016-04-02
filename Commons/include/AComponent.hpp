//
// AComponent.hpp for AComonent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:22:30 2016 Victor Gouet
// Last update Fri Mar 11 17:33:55 2016 Victor Gouet
//

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

#include "Vector2.hpp"

class AComponent
{
public:
    enum ComponentColor
    {
        COLOR_BLACK = 0,
        COLOR_RED = 1,
        COLOR_GREEN = 2,
        COLOR_YELLOW = 3,
        COLOR_BLUE = 4,
        COLOR_MAGENTA = 5,
        COLOR_CYAN = 6,
        COLOR_WHITE = 7
    };

private:
    Vector2<double> pos;
    enum ComponentColor _color;

public:
    AComponent(int x, int y, enum ComponentColor color);

    AComponent(Vector2<double> const &pos, enum ComponentColor color);

    virtual ~AComponent();

public:
    Vector2<double> const &getPos() const;

    enum ComponentColor getColor() const;

    void setColor(ComponentColor color);

    void setPos(const Vector2<double> & pos);
};

#endif
