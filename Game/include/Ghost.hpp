//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_GHOST_HPP
#define CPP_ARCADE_GHOST_HPP

#include "PacmanCharacter.hpp"

class Ghost : public PacmanCharacter
{
public:
    Ghost(AComponent::ComponentColor color);
    virtual ~Ghost();

public:
    virtual Vector2<int> const& Move(char map[31][51]);
};


#endif //CPP_ARCADE_GHOST_HPP
