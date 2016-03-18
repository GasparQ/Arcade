//
// Created by gaspar_q on 3/18/16.
//

#ifndef C_ARCADEMENU_HPP
#define C_ARCADEMENU_HPP

#include <stddef.h>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "Commons/include/AComponent.hpp"
#include "Commons/include/ActionComponent.hpp"

class ArcadeMenu
{
public:
    enum ComponentsPos
    {
        GRAPHIC,
        GAME,
        PLAY
    };
    ArcadeMenu();
    ~ArcadeMenu();

public:
    void setFrames(std::string const &, std::string const &, int );
    void setMode(std::string const &);
    std::string getNextFrame() const;
    std::stack<AComponent *>    updateMenu(int key, std::string const &currGame, std::string const &currLib);

private:
    void eventManager(int key, std::string const &currGame, std::string const &currLib);

private:
    std::map<std::string, std::vector<std::string>>             frames;
    mutable size_t                                              frameIdx;
    std::map<std::string, std::vector<std::string>>::iterator   mode;
    std::vector<ActionComponent>                                menuComponents;
    std::vector<ActionComponent>::iterator                      currComponent;
};

#endif //C_ARCADEMENU_HPP
