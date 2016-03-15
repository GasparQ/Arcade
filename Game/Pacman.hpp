//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMAN_HPP
#define CPP_ARCADE_PACMAN_HPP

#include "include/IGame.hpp"

class Pacman : public IGame
{
public:
    Pacman();

    virtual ~Pacman();

public:
    virtual std::stack<AComponent *> compute(int keycode);

    virtual void restart();

    typedef void (Pacman::*keyfunc)();

private:
    void InitGame();

private:
    char map[3][10] = {"XXXXXXXXXX",
                       "XooooooooX",
                       "XXXXXXXXXX"};
};


#endif //CPP_ARCADE_PACMAN_HPP
