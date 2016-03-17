//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACPAC_HPP
#define CPP_ARCADE_PACPAC_HPP

#include "PacmanCharacter.hpp"

class Pacman : public PacmanCharacter
{
public:
    Pacman();
    virtual ~Pacman();

public:
    virtual Vector2<int> const& Move(char map[31][51], Vector2<int> pacmanPos = Vector2<int>(0, 0));
};


#endif //CPP_ARCADE_PACMAN_HPP
