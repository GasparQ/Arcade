//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMANCHARACTER_HPP
#define CPP_ARCADE_PACMANCHARACTER_HPP

#include <cmath>
#include "../../Commons/include/Vector2.hpp"
#include "../../Commons/include/AComponent.hpp"
#include "../../Commons/include/GameComponent.hpp"

class PacmanCharacter
{
public:
    PacmanCharacter(Vector2<double > pos, AComponent::ComponentColor color, std::string const &shape2D,
                    std::string const &shapeCurses, GameComponent::Shapes shape3D);

    virtual ~PacmanCharacter();

public:
    virtual Vector2<double> const &Move(char map[31][51], Vector2<double> pacmanPos = Vector2<double>(0, 0)) = 0;

    virtual void ResetPosition();

    Vector2<double> const &getPosition() const;

    AComponent::ComponentColor getColor() const;

    GameComponent::Shapes getShape3D() const;

    virtual std::string const &getShape2D() const;

    std::string const &getShapeCurses() const;

    virtual void goUp(char map[31][51])
    {
        if (m_pos.y - 1 < 0)
            return;
        if (map[(int)m_pos.y - 1][(int)m_pos.x] != 'X')
            m_dir = UP;
    }

    virtual void goDown(char map[31][51])
    {
        if (m_pos.y + 1 >= 31)
            return;
        if (map[(int)m_pos.y + 1][(int)m_pos.x] != 'X')
            m_dir = DOWN;
    }

    virtual void goLeft(char map[31][51])
    {
        if (m_pos.x - 1 < 0)
            return;
        if (map[(int)m_pos.y][(int)m_pos.x - 1] != 'X')
            m_dir = LEFT;
    }

    virtual void goRight(char map[31][51])
    {
        if (m_pos.x + 1 >= 51)
            return;
        if (map[(int)m_pos.y][(int)m_pos.x + 1] != 'X')
            m_dir = RIGHT;
    }

protected:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Direction m_dir = LEFT;
    Vector2<double> m_pos;
    Vector2<double> m_initPos;

protected:
    AComponent::ComponentColor m_color;
    std::string m_shape2D;
    std::string m_shapeCurses;
    GameComponent::Shapes m_shape3D;
    double velocity = 0.2500000000;
};


#endif //CPP_ARCADE_PACMANCHARACTER_HPP
