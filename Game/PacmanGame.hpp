//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMAN_HPP
#define CPP_ARCADE_PACMAN_HPP

#include <vector>
#include <map>
#include <list>
#include "include/IGame.hpp"

class PacmanGame : public IGame
{
public:
    PacmanGame();

    virtual ~PacmanGame();

public:
    virtual std::stack<AComponent *> compute(int keycode);

    virtual void restart();

    typedef void (PacmanGame::*keyfunc)();

private:
    void InitGame();

    inline void goUp();

    inline void goDown();

    inline void goLeft();

    inline void goRight();

    void MovePacman();

    void MoveGhost();

private:
    // 50x30
    char m_map[31][51] = {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XooooooooooooooooooooooooooooooooooooooooooooooooX",
                          "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"};

private:


    Vector2<int> m_pacPos;
    std::vector<Vector2<int> > m_ghostPos;
    std::list<Vector2<int> > m_gumPos;
    std::map<int, keyfunc> keycodes;
    int m_score = 0;
};


#endif //CPP_ARCADE_PACMAN_HPP
