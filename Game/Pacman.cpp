//
// Created by veyrie_f on 3/15/16.
//

#include "Pacman.hpp"

Pacman::Pacman()
{

}

Pacman::~Pacman()
{

}

std::stack<AComponent *> Pacman::compute(int keycode)
{
    return std::stack<AComponent *>(std::deque<AComponent *>());
}

void Pacman::restart()
{

}
