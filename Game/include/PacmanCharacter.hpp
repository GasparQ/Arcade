//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMANCHARACTER_HPP
#define CPP_ARCADE_PACMANCHARACTER_HPP

#include "../../Commons/include/Vector2.hpp"
#include "../../Commons/include/AComponent.hpp"
#include "../../Commons/include/GameComponent.hpp"

class PacmanCharacter
{
public:
    PacmanCharacter(Vector2<int> pos, AComponent::ComponentColor color, std::string const &shape2D,
                    std::string const &shapeCurses, GameComponent::Shapes shape3D);

    virtual ~PacmanCharacter();

public:
    virtual Vector2<int> const &Move(char map[31][51]) = 0;

    virtual void ResetPosition();

    Vector2<int> const &getPosition() const;

    AComponent::ComponentColor getColor() const;

    GameComponent::Shapes getShape3D() const;

    std::string const &getShape2D() const;

    std::string const &getShapeCurses() const;

    inline void goUp()
    {
        m_dir = UP;
    }

    inline void goDown()
    {
        m_dir = DOWN;
    }

    inline void goLeft()
    {
        m_dir = LEFT;
    }

    inline void goRight()
    {
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
    Vector2<int> m_pos;
    Vector2<int> m_initPos;

private:
    AComponent::ComponentColor m_color;
    std::string m_shape2D;
    std::string m_shapeCurses;
    GameComponent::Shapes m_shape3D;
};


#endif //CPP_ARCADE_PACMANCHARACTER_HPP
