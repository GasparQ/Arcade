//
// Created by veyrie_f on 3/15/16.
//

#include <algorithm>
#include "../include/PacmanGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/UIComponent.hpp"

// TODO: lives
// Ghost spawn after 10 seconds
// score reset on level change ?
PacmanGame::PacmanGame() :
        AGame("Pacman")
{
    // Spawns 4 ghosts
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_GREEN));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_CYAN));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_RED));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_MAGENTA));

    // Sets keycodes
    keycodes[ArcadeSystem::ArrowDown] = &PacmanCharacter::goDown;
    keycodes[ArcadeSystem::ArrowLeft] = &PacmanCharacter::goLeft;
    keycodes[ArcadeSystem::ArrowRight] = &PacmanCharacter::goRight;
    keycodes[ArcadeSystem::ArrowUp] = &PacmanCharacter::goUp;

    // Store all the gums
    StorePacgums();
}

PacmanGame::~PacmanGame()
{

}

std::stack<AComponent *> PacmanGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::map<int, keyfunc>::iterator it;

    output.push(new UIComponent(Vector2<int>((static_cast<int>(ArcadeSystem::winWidth - std::string(
                                        "score : " + std::to_string(m_score)).size()) / 2), 1),
                                AComponent::COLOR_WHITE,
                                Vector2<int>(5, 1), "score : " + std::to_string(m_score)));

    if ((it = keycodes.find(keycode)) != keycodes.end())
    {
        (m_pacman.*it->second)(this->m_map);
    }

    MoveEntities();

    // Pacman
    output.push(new GameComponent(m_pacman.getPosition(), m_pacman.getColor(), m_pacman.getShape3D(),
                                  m_pacman.getShapeCurses(), m_pacman.getShape2D()));
    // Ghosts
    for (auto var : m_ghosts)
    {
        output.push(new GameComponent(var.getPosition(), var.getColor(), var.getShape3D(), var.getShapeCurses(),
                                      var.getShape2D()));
    }
    // Terrain
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 50; ++x)
        {
            if (m_map[y][x] == 'X')
            {
                output.push(new GameComponent(Vector2<int>(x, y), AComponent::ComponentColor::COLOR_BLUE,
                                              GameComponent::Shapes::CUBE, " ", ""));
            }
        }
    }
    // Gums
    for (auto var : m_gums)
    {
        if (!var.bIsSpecial())
        {
            output.push(new GameComponent(var.getPos(), AComponent::ComponentColor::COLOR_WHITE,
                                          GameComponent::Shapes::SPHERE_SMALL, "*", ""));
        }
        else
        {
            output.push(new GameComponent(var.getPos(), AComponent::ComponentColor::COLOR_WHITE,
                                          GameComponent::Shapes::SPHERE_MEDIUM, "o", ""));
        }
    }
    return output;
}

void PacmanGame::restart()
{
    InitGame();
}

void PacmanGame::InitGame()
{
    m_score = 0;
    for (std::vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); ++it)
    {
        it->ResetPosition();
    }
    m_pacman.ResetPosition();
    m_gums.clear();
    StorePacgums();
}

extern "C" IGame *loadGame()
{
    return (new PacmanGame());
}

void    PacmanGame::onReplaceGhostByWall(char newMap[31][51], Ghost::GhostState state) const
{
    int y;
    int x;

    y = 0;
    while (y < 31)
    {
        x = 0;
        while (x < 51)
        {
            newMap[y][x] = m_map[y][x];
            ++x;
        }
        ++y;
    }
    // If the ghost is alive other ghosts are obstacles
    if (state != Ghost::DEAD)
    {
        std::vector<Ghost>::const_iterator itGhost = m_ghosts.begin();
        while (itGhost != m_ghosts.end())
        {
            if ((*itGhost).GetState() != Ghost::DEAD)
            {
                newMap[(*itGhost).getPosition().y][(*itGhost).getPosition().x] = 'X';
            }
            ++itGhost;
        }
    }
}

// Updates the positions of pacman and all the ghosts
void PacmanGame::MoveEntities()
{
    Vector2<int> newPacPos = m_pacman.Move(m_map);
    std::vector<Ghost>::iterator itGhost = m_ghosts.begin();

    while (itGhost != m_ghosts.end())
    {
        char newMap[31][51];

        onReplaceGhostByWall(newMap, (*itGhost).GetState());
        // If pacman is immortal, it kills the ghost, otherwise it dies
        if ((*itGhost).Move(newMap, newPacPos) == newPacPos)
        {
            if (m_pacman.GetState() == Pacman::MORTAL)
            {
                Die();
            }
            else if (m_pacman.GetState() == Pacman::IMMORTAL)
            {
                (*itGhost).SetState(Ghost::DEAD);
                m_score += 100;
            }
        }
        ++itGhost;
    }
    // Looks if pacman is eating a gum
    auto it = std::find_if(std::begin(m_gums), std::end(m_gums), [&](const Gums v)
    { return newPacPos == v.getPos(); });
    if (it != std::end(m_gums))
    {
        // If it's a special pacgum
        if ((*it).bIsSpecial())
        {
            // Pacman becomes immortal
            m_pacman.SetState(Pacman::PacmanState::IMMORTAL);
            // And all the ghosts are scared
            itGhost = m_ghosts.begin();
            while (itGhost != m_ghosts.end())
            {
                (*itGhost).SetState(Ghost::SCARED);
                ++itGhost;
            }
        }
        m_score += 10;
        m_gums.remove(*it);
    }
    // If we ate the gums we restart the level
    if (m_gums.empty())
    {
        InitGame();
    }
}

void PacmanGame::Die()
{
    InitGame();
}

void PacmanGame::StorePacgums()
{
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 50; ++x)
        {
            if (m_map[y][x] == '.')
            {
                m_gums.push_back(Gums(Vector2<int>(x, y), false));
            }
            else if (m_map[y][x] == 'o')
            {
                m_gums.push_back(Gums(Vector2<int>(x, y), true));
            }
        }
    }
}
