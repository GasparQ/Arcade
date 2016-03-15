//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMANCHARACTER_HPP
#define CPP_ARCADE_PACMANCHARACTER_HPP


class PacmanCharacter
{
public:
    PacmanCharacter();
    virtual ~PacmanCharacter();

protected:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Direction m_dir = LEFT;
    int m_pos;
};


#endif //CPP_ARCADE_PACMANCHARACTER_HPP
