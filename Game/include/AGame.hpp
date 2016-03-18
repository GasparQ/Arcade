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
    AGame(std::string const &name) : name(name)
    {
        state = ALIVE;
    }
    virtual ~AGame()
    {
    }
    virtual std::string const &getName() const
    {
        return name;
    }

protected:
    GameState           state;
    const std::string   name;
};

#endif //C_AGAME_HPP
