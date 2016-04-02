//
// Created by gaspar_q on 3/15/16.
//

#ifndef C_AGAME_HPP
#define C_AGAME_HPP

#include "IGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

class AGame : public IGame
{
public:

    typedef enum
    {
        ALIVE,
        DEAD
    } GameState;

    AGame(std::string const &name) :
            state(ALIVE),
            name(name),
            size(ArcadeSystem::winWidth, ArcadeSystem::winHeight)
    {
    }
    virtual ~AGame()
    {
    }
    virtual std::string const &getName() const
    {
        return name;
    }
    virtual Vector2<double> const &getSize() const
    {
        return size;
    }

protected:
    GameState           state;
    const std::string   name;
    Vector2<double>     size;
};

#endif //C_AGAME_HPP
