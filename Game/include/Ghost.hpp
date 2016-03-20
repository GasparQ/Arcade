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
    virtual Vector2<int> const& Move(char map[31][51], Vector2<int> pacmanPos);

    virtual void goUp(char map[31][51]);
    virtual void goDown(char map[31][51]);
    virtual void goLeft(char map[31][51]);
    virtual void goRight(char map[31][51]);

    virtual void ResetPosition();

public:
    /// Dead = goes to base
    /// Hunting : looks for pacman
    /// Scared : flees pacman
    enum GhostState
    {
        DEAD = 1,
        HUNTING = 2,
        SCARED = 3,
        FREEZE = 4
    };
    void SetState(GhostState state);
    GhostState GetState() const ;

private:
    GhostState m_state = FREEZE;
    AComponent::ComponentColor m_color_original;
};


#endif //CPP_ARCADE_GHOST_HPP
