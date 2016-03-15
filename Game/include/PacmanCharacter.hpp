//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMANCHARACTER_HPP
#define CPP_ARCADE_PACMANCHARACTER_HPP

#include "../../Commons/include/Vector2.hpp"

class PacmanCharacter
{
public:
    PacmanCharacter(Vector2<int> pos);
    virtual ~PacmanCharacter();

public:
    virtual Vector2<int> const& Move(char map[31][51]) = 0;
    virtual void ResetPosition();
    Vector2<int> const& getPosition() const;
    
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
};


#endif //CPP_ARCADE_PACMANCHARACTER_HPP
