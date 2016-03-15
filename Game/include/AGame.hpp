//
// Created by gaspar_q on 3/15/16.
//

#ifndef C_AGAME_HPP
#define C_AGAME_HPP

#include "IGame.hpp"

class AGame : public IGame
{
public:
    typedef enum
    {
        ALIVE,
        DEAD
    } GameState;
    AGame()
    {
        state = ALIVE;
    }
    virtual ~AGame()
    {
    }

protected:
    GameState           state;
};

#endif //C_AGAME_HPP
