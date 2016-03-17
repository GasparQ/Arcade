//
// Created by veyrie_f .n 3/15/16.
//

#ifndef CPP_ARCADE_PACMAN_HPP
#define CPP_ARCADE_PACMAN_HPP

#include <vector>
#include <map>
#include <list>
#include "IGame.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "../../Commons/include/AComponent.hpp"

class PacmanGame : public IGame
{
public:
    PacmanGame();

    virtual ~PacmanGame();

public:
    virtual std::stack<AComponent *> compute(int keycode);

    virtual void restart();

    typedef void (PacmanCharacter::*keyfunc)(char [31][51]);

private:
    void InitGame();

    void MoveEntities();
  void  onReplaceGhostByWall(char newMap[31][51]) const;


    void Die();

private:
    // 50x30
    char m_map[31][51] = {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                          "Xo.....................XXXX.....................oX",
                          "X.XXXXXXXX.XXXXXXXXXXX.XXXX.XXXXXXXXXXX.XXXXXXXX.X",
                          "X.X      X.X         X.XXXX.X         X.X      X.X",
                          "X.XXXXXXXX.XXXXXXXXXXX.XXXX.XXXXXXXXXXX.XXXXXXXX.X",
                          "X................................................X",
                          "X.XXXXXXXX.XXXX.XXXXXXXXXXXXXXXXXX.XXXX.XXXXXXXX.X",
                          "X.XXXXXXXX.X  X.XXXXXXXX  XXXXXXXX.X  X.XXXXXXXX.X",
                          "X..........X  X........X  X........X  X..........X",
                          "XXXXXXXXXX.X  XXXXXXXX.X  X.XXXXXXXX  X.XXXXXXXXXX",
                          "       XXX.X  XXXXXXXX.XXXX.XXXXXXXX  X.XXX       ",
                          "       XXX.X  X....................X  X.XXX       ",
                          "       XXX.X  X.XXXXX.XXX XXX.XXXX.X  X.XXX       ",
                          "XXXXXXXXXX.XXXX.X   X.X     X.X  X.XXXX.XXXXXXXXXX",
                          "          ......X   X.X     X.X  X......          ",
                          "XXXXXXXXXX.XXXX.X   X.X     X.X  X.XXXX.XXXXXXXXXX",
                          "       XXX.X  X.X   X.X     X.X  X.X  X.XXX       ",
                          "       XXX.X  X.XXXXX.XXXXXXX.XXXX.X  X.XXX       ",
                          "       XXX.X  X....................X  X.XXX       ",
                          "XXXXXXXXXX.XXXX.XXXXXXXXXXXXXXXXXX.XXXX.XXXXXXXXXX",
                          "X......................X  X......................X",
                          "X.XXXXXXXX.XXXXXXXXXXX.X  X.XXXXXXXXXXX.XXXXXXXX.X",
                          "X.XXXX   X.XXXXXXXXXXX.XXXX.XXXXXXXXXXX.X   XXXX.X",
                          "X....X   X..............................X   X....X",
                          "XXXX.X   X.XXXX.XXXXXXXXXXXXXXXXXX.XXXX.X   X.XXXX",
                          "XXXX.XXXXX.X  X.XXXXXXXX  XXXXXXXX.X  X.XXXXX.XXXX",
                          "X..........X  X........X  X........X  X..........X",
                          "X.XXXXXXXXXXXXXXXXXXXX.XXXX.XXXXXXXXXXXXXXXXXXXX.X",
                          "Xo..............................................oX",
                          "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"};

private:
    Pacman m_pacman;
    std::vector<Ghost> m_ghosts;
    std::list<Vector2<int> > m_gumPos;
    std::map<int, keyfunc> keycodes;
    int m_score = 0;
};


#endif //CPP_ARCADE_PACMAN_HPP
