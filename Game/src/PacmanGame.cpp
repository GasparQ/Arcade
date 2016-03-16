//
// Created by veyrie_f on 3/15/16.
//

#include <algorithm>
#include "../include/PacmanGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/GameComponent.hpp"

PacmanGame::PacmanGame()
{
    // Spawns 4 ghosts
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_GREEN));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_CYAN));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_RED));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_BLUE));

    // Sets keycodes
    keycodes[ArcadeSystem::ArrowDown] = &PacmanCharacter::goDown;
    keycodes[ArcadeSystem::ArrowLeft] = &PacmanCharacter::goLeft;
    keycodes[ArcadeSystem::ArrowRight] = &PacmanCharacter::goRight;
    keycodes[ArcadeSystem::ArrowUp] = &PacmanCharacter::goUp;

    // Store all the gums
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 50; ++x)
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

    output.push(new UIComponent(Vector2<int>((static_cast<int>(ArcadeSystem::winWidth - std::string("score : " + std::to_string(m_score)).size()) / 2), 1),
                                AComponent::COLOR_WHITE,
                                Vector2<int>(5, 1), "score : " + std::to_string(m_score)));

    if ((it = keycodes.find(keycode)) != keycodes.end())
    {
        (m_pacman.*it->second)();
    }

    MoveEntities();

    // Pacman
    output.push(new GameComponent(m_pacman.getPosition(), m_pacman.getColor(), m_pacman.getShape3D(), m_pacman.getShapeCurses(), m_pacman.getShape2D()));
    //Ghosts
    for (auto var : m_ghosts)
    {
        output.push(new GameComponent(var.getPosition(), var.getColor(), var.getShape3D(), var.getShapeCurses(), var.getShape2D()));
    }
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
    for (auto var : m_gumPos)
    {
        output.push(new GameComponent(var, AComponent::ComponentColor::COLOR_WHITE, GameComponent::Shapes::SPHERE, "*", ""));
    }
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

    if (m_gumPos.empty())
    {
        InitGame();
    }
    for (auto var : m_ghosts)
    {
        if (var.Move(m_map) == newPacPos)
        {
            Die();
        }
    }
    auto it = std::find_if(std::begin(m_gumPos), std::end(m_gumPos), [&](const Vector2<int> v){ return newPacPos == v; });
    if (it != std::end(m_gumPos))
    {
        m_score += 10;
        m_gumPos.remove(*it);
    }
}

void PacmanGame::Die()
{
    InitGame();
}
