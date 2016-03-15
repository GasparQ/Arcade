//
// Created by veyrie_f on 3/15/16.
//

#include "PacmanGame.hpp"
#include "../Commons/include/ArcadeSystem.hpp"
#include "../Commons/include/UIComponent.hpp"

PacmanGame::PacmanGame() :
m_pacPos (25, 29)
{
    // Spawns 4 ghosts
    m_ghostPos.push_back(Vector2<int>(25, 15));
    m_ghostPos.push_back(Vector2<int>(25, 15));
    m_ghostPos.push_back(Vector2<int>(25, 15));
    m_ghostPos.push_back(Vector2<int>(25, 15));

    // Sets keycodes
    keycodes[ArcadeSystem::ArrowDown] = &PacmanGame::goDown;
    keycodes[ArcadeSystem::ArrowLeft] = &PacmanGame::goLeft;
    keycodes[ArcadeSystem::ArrowRight] = &PacmanGame::goRight;
    keycodes[ArcadeSystem::ArrowUp] = &PacmanGame::goUp;

    // Store all the gums
    for (int y = 0; m_map[y]; ++y)
    {
        for (int x = 0; m_map[y][x]; ++x)
        {
            m_gumPos.push_back(Vector2<int>(x, y));
        }
    }
}

PacmanGame::~PacmanGame()
{

}

std::stack<AComponent *> PacmanGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::map<int, keyfunc>::iterator it;

    if ((it = keycodes.find(keycode)) != keycodes.end())
    {
        (this->*it->second)();
    }
    MoveGhost();
    MovePacman();

    output.push(new UIComponent(Vector2<int>((static_cast<int>(ArcadeSystem::winWidth - std::string("score : " + std::to_string(m_score)).size()) / 2), 1),
                                AComponent::COLOR_WHITE,
                                Vector2<int>(5, 1), "score : " + std::to_string(m_score)));
    return output;
}

void PacmanGame::restart()
{
    InitGame();
}

void PacmanGame::InitGame()
{
    for (std::vector<Vector2<int> >::iterator it = m_ghostPos.begin(); it != m_ghostPos.end(); ++it)
    {
        it->x = 25;
        it->y = 15;
    }
}

extern "C" IGame *loadGame()
{
    return (new PacmanGame());
}

inline void PacmanGame::goUp()
{
    m_pacDir = UP;
}

inline void PacmanGame::goDown()
{
    m_pacDir = DOWN;
}

inline void PacmanGame::goLeft()
{
    m_pacDir = LEFT;
}

inline void PacmanGame::goRight()
{
    m_pacDir = RIGHT;
}

void PacmanGame::MovePacman()
{
    Vector2<int> nextPos = m_pacPos;

    switch (m_pacDir)
    {
        case UP:
            if (m_map[m_pacPos.y - 1][m_pacPos.x] != 'X')
            {
                --m_pacPos.y;
            }
            break;
        case DOWN:
            if (m_map[m_pacPos.y + 1][m_pacPos.x] != 'X')
            {
                ++m_pacPos.y;
            }
            break;
        case LEFT:
            if (m_map[m_pacPos.y][m_pacPos.x - 1] != 'X')
            {
                --m_pacPos.x;
            }
            break;
        case RIGHT:
            if (m_map[m_pacPos.y][m_pacPos.x + 1] != 'X')
            {
                ++m_pacPos.x;
            }
            break;
    }
}

void PacmanGame::MoveGhost()
{

}
