//
// Created by veyrie_f on 3/15/16.
//

#include "PacmanGame.hpp"
#include "../Commons/include/ArcadeSystem.hpp"
#include "../Commons/include/UIComponent.hpp"

PacmanGame::PacmanGame()
{
    // Spawns 4 ghosts
    m_ghosts.push_back(Ghost());
    m_ghosts.push_back(Ghost());
    m_ghosts.push_back(Ghost());
    m_ghosts.push_back(Ghost());

    // Sets keycodes
    keycodes[ArcadeSystem::ArrowDown] = &PacmanCharacter::goDown;
    keycodes[ArcadeSystem::ArrowLeft] = &PacmanCharacter::goLeft;
    keycodes[ArcadeSystem::ArrowRight] = &PacmanCharacter::goRight;
    keycodes[ArcadeSystem::ArrowUp] = &PacmanCharacter::goUp;

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
        (m_pacman.*it->second)();
    }

    MoveEntities();

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
    for (std::vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); ++it)
    {
        it->ResetPosition();
    }
    m_pacman.ResetPosition();
}

extern "C" IGame *loadGame()
{
    return (new PacmanGame());
}

void PacmanGame::MoveEntities()
{
    Vector2<int> newPacPos = m_pacman.Move(m_map);

    for (auto var : m_ghosts)
    {
        if (var.Move(m_map) == newPacPos)
        {
            Die();
        }
    }
}

void PacmanGame::Die()
{
    InitGame();
}
