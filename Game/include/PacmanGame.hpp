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
#include "AGame.hpp"

class PacmanGame : public AGame
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

    void onReplaceGhostByWall(char newMap[31][51], Ghost::GhostState state) const;

    void StorePacgums();

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
    class Gums
    {
    public:
        Gums(Vector2<int> pos, bool bIsSpecialGum) : m_pos(pos), m_bIsSpecialGum(bIsSpecialGum)
        { }

        ~Gums()
        { }

        Vector2<int> getPos() const
        { return m_pos; }

        bool bIsSpecial() const
        { return m_bIsSpecialGum; }

    public:
        bool operator==(Gums const &other) const
        { return m_pos == other.m_pos; }

    private:
        Vector2<int> m_pos;
        bool m_bIsSpecialGum;
    };

private:
    Pacman m_pacman;
    std::vector<Ghost> m_ghosts;
    std::list<Gums> m_gums;
    std::map<int, keyfunc> keycodes;
    int m_score = 0;
};


#endif //CPP_ARCADE_PACMAN_HPP
