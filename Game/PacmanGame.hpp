//
// Created by veyrie_f on 3/15/16.
//

#ifndef CPP_ARCADE_PACMAN_HPP
#define CPP_ARCADE_PACMAN_HPP

#include <vector>
#include <map>
#include <list>
#include "include/IGame.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"

class PacmanGame : public IGame
{
public:
    PacmanGame();

    virtual ~PacmanGame();

public:
    virtual std::stack<AComponent *> compute(int keycode);

    virtual void restart();

    typedef void (PacmanCharacter::*keyfunc)();

private:
    void InitGame();

    void MoveEntities();

    void Die();

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
    Pacman m_pacman;
    std::vector<Ghost> m_ghosts;
    std::list<Vector2<int> > m_gumPos;
    std::map<int, keyfunc> keycodes;
    int m_score = 0;
};


#endif //CPP_ARCADE_PACMAN_HPP
