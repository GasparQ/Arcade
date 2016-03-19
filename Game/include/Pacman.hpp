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
    enum PacmanState
    {
        MORTAL = 1,
        IMMORTAL = 2
    };
    void UpdateState(PacmanState state);
    PacmanState GetState() const;
    void SetState(PacmanState state);

public:
    virtual Vector2<int> const& Move(char map[31][51], Vector2<int> pacmanPos = Vector2<int>(0, 0));

private:
    PacmanState m_state = MORTAL;
};


#endif //CPP_ARCADE_PACMAN_HPP
