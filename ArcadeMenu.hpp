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
#include "Arcade.hpp"

class ArcadeMenu
{
public:
    enum ComponentsPos
    {
        GRAPHIC,
        GAME,
        PLAY
    };
    ArcadeMenu(arcade::Arcade &);
    ~ArcadeMenu();

public:
    void setFrames(std::string const &, std::string const &, int );
    void setMode(std::string const &);
    std::string getNextFrame() const;
    std::stack<AComponent *>    updateMenu(int key);

private:
    typedef void (ArcadeMenu::*events)();
    void nextAction();
    void prevAction();
    void goDown();
    void goUp();
    void onEnter();
    void updateTexts();

private:
    arcade::Arcade                                              &arcade1;
    std::map<std::string, std::vector<std::string>>             frames;
    mutable size_t                                              frameIdx;
    std::map<std::string, std::vector<std::string>>::iterator   mode;
    std::vector<ActionComponent<arcade::eventSystem > >                                menuComponents;
    std::vector<ActionComponent<arcade::eventSystem > >::iterator                      currComponent;

private:
    std::map<int, events >                                      sysEvents;
};

#endif //C_ARCADEMENU_HPP