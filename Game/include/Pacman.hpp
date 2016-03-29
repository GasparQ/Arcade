//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACPAC_HPP
#define CPP_ARCADE_PACPAC_HPP

#include <stack>
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
    PacmanState GetState() const;
    void SetState(PacmanState state);
    void ResetPosition();

    virtual void goUp(char map[31][51]);

    virtual void goDown(char map[31][51]);

    virtual void goLeft(char map[31][51]);

    virtual void goRight(char map[31][51]);

  virtual std::string const &getShape2D() const;

public:
    virtual Vector2<double> const& Move(char map[31][51], Vector2<double> pacmanPos = Vector2<double>(0, 0));

private:
  std::string		sprite[4];
    PacmanState m_state = MORTAL;
    std::stack<Direction> m_dir_stack;
    /// Max keys to remember
    const size_t m_max_key_buff = 1;
};


#endif //CPP_ARCADE_PACMAN_HPP
