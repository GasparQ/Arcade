//
// Created by veyrie_f on 3/15/16.
//

#include <algorithm>
#include <unistd.h>
#include "../include/PacmanGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/UIComponent.hpp"
#include "../../Commons/include/HighScoreComponent.hpp"
#include "../../Commons/include/Chrono.hpp"
#include "../include/Protocol.hpp"

//TODO:
// Ghost can kill pacman if they went back to spawn
PacmanGame::PacmanGame() :
        AGame("Pacman")
{
    // Spawns 4 ghosts
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_GREEN, "sprites/yellow_ghost.bmp"));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_CYAN, "sprites/cyan_ghost.bmp"));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_RED, "sprites/red_ghost.bmp"));
    m_ghosts.push_back(Ghost(AComponent::ComponentColor::COLOR_MAGENTA, "sprites/pink_ghost.bmp"));

    // Sets keycodes
    keycodes[ArcadeSystem::ArrowDown] = &PacmanCharacter::goDown;
    keycodes[ArcadeSystem::ArrowLeft] = &PacmanCharacter::goLeft;
    keycodes[ArcadeSystem::ArrowRight] = &PacmanCharacter::goRight;
    keycodes[ArcadeSystem::ArrowUp] = &PacmanCharacter::goUp;

    InitGame();
    //Chrono<Pacman, void (Pacman::*)()> *c = new Chrono<Pacman, void (Pacman::*)()>(10, m_pacman, &Pacman::ResetPosition);
    //c->SetEvent(m_pacman, &Pacman::ResetPosition);
    //c->SetEvent(this, void (PacmanGame::*InitGame)());
    //m_chronos.push_back(std::unique_ptr<IChrono>(c));
    //m_chronos.emplace_back(new Chrono<Pacman, void (Pacman::*)()>(10, m_pacman, &Pacman::ResetPosition));
    //m_chronos.emplace_back(new Chrono<PacmanGame, void (PacmanGame::*)()>(10, *this, &PacmanGame::FreeGhosts, "Start"));
}

PacmanGame::~PacmanGame()
{

}

std::stack<AComponent *> PacmanGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::map<int, keyfunc>::iterator it;
    HighScoreComponent *highScoreComponent;

    if (state == AGame::ALIVE)
    {
        output.push(new UIComponent(Vector2<double>((static_cast<int>(ArcadeSystem::winWidth - std::string(
                                            "score : " + std::to_string(m_score)).size()) / 2), 1),
                                    AComponent::COLOR_WHITE,
                                    Vector2<double>(5, 1), "score : " + std::to_string(m_score)));
        output.push(new UIComponent(Vector2<double>(1, 1),
                                    AComponent::COLOR_WHITE,
                                    Vector2<double>(5, 1), "lives : " + std::to_string(m_lives)));

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
                    output.push(new GameComponent(Vector2<double>(x, y), AComponent::ComponentColor::COLOR_BLUE,
                                                  GameComponent::Shapes::CUBE_LARGE, " ", "sprites/pacwall.bmp"));
                }
            }
        }
        // Gums
        for (auto var : m_gums)
        {
            if (!var.bIsSpecial())
            {
                output.push(new GameComponent(var.getPos(), AComponent::ComponentColor::COLOR_WHITE,
                                              GameComponent::Shapes::SPHERE_SMALL, "*", "sprites/pac_gum.bmp"));
            }
            else
            {
                output.push(new GameComponent(var.getPos(), AComponent::ComponentColor::COLOR_WHITE,
                                              GameComponent::Shapes::SPHERE_MEDIUM, "o", "sprites/pac_bonus.bmp"));
            }
        }
        // Update chrono
        UpdateChrono();
    }
    else if (state == AGame::DEAD)
    {
        highScoreComponent = new HighScoreComponent("Pacman", m_score);
        highScoreComponent->UpdatePseudo(keycode);
        if (keycode == ArcadeSystem::Enter && highScoreComponent->submit())
        {
            state = AGame::GameState::ALIVE;
            delete (highScoreComponent);
            InitGame();
        }
        else
        {
            output.push(highScoreComponent);
        }
    }

    return output;
}

void PacmanGame::restart()
{
    InitGame();
}

///
/// @param : is it a restart or a level change ?
///
void PacmanGame::InitGame(bool bIsRestart, bool bIsNextLevel)
{
    for (std::vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); ++it)
    {
        it->ResetPosition();
    }
    m_pacman.ResetPosition();
    m_pacman.SetState(Pacman::MORTAL);
    m_chronos.clear();
    m_chronos.emplace_back(new Chrono<PacmanGame, void (PacmanGame::*)()>(10, *this, &PacmanGame::FreeGhosts, "Start"));
    if (bIsRestart)
    {
        if (!bIsNextLevel)
        {
            m_score = 0;
            m_lives = 3;
        }
        m_gums.clear();
        StorePacgums();
    }
}

extern "C" IGame *loadGame()
{
    return (new PacmanGame());
}

void                                    updateMap(struct arcade::GetMap *map, PacmanGame const &pacman)
{
    std::vector<std::string>            pacMap = pacman.getMap();

    //Reinit la map
    for (size_t i = 0, len = ArcadeSystem::winHeight * ArcadeSystem::winWidth; i < len; ++i)
    {
        map->tile[i] = arcade::TileType::EMPTY;
    }
    //Write map
    for (size_t i = 0, len = ArcadeSystem::winWidth * ArcadeSystem::winHeight; i < len; ++i)
    {
        switch (pacMap[i / ArcadeSystem::winWidth][i % ArcadeSystem::winWidth])
        {
            case 'X':
                map->tile[i] = arcade::TileType::BLOCK;
                break;
            case 'o':
                map->tile[i] = arcade::TileType::POWERUP;
                break;
            case '.':
                map->tile[i] = arcade::TileType::POWERUP;
                break;
            default:
                break;
        }
    }
}

void    whereAmI(PacmanGame const &pacman)
{
    struct arcade::WhereAmI *pos;
    Vector2<double>         pacpos = pacman.getPacman().getPosition();
    size_t                  posSize = sizeof(*pos) + sizeof(arcade::Position);

    if ((pos = (struct arcade::WhereAmI *)(malloc(posSize))) == NULL)
        throw std::bad_alloc();
    pos->type = arcade::CommandType::WHERE_AM_I;
    pos->lenght = 1;
    pos->position[0].x = static_cast<uint16_t >(pacpos.x);
    pos->position[0].y = static_cast<uint16_t >(pacpos.y);
    write(1, pos, posSize);
    free(pos);
}

extern "C" void Play(void)
{
    char                        c;
    PacmanGame                  pacman;
    struct arcade::GetMap       *map;
    size_t                      mapSize = sizeof(*map) + (ArcadeSystem::winWidth * ArcadeSystem::winHeight * sizeof(uint16_t));
    std::stack<AComponent *>    components;

    if ((map = (struct arcade::GetMap *)(malloc(mapSize))) == NULL)
        throw std::bad_alloc();
    map->type = arcade::CommandType::GET_MAP;
    map->width = ArcadeSystem::winWidth;
    map->height = ArcadeSystem::winHeight;
    while (std::cin.read(&c, 1))
    {
        switch (static_cast<arcade::CommandType>(c))
        {
            case arcade::CommandType::WHERE_AM_I:
                whereAmI(pacman);
                break;
            case arcade::CommandType::GET_MAP:
                updateMap(map, pacman);
                write(1, map, mapSize);
                break;
            case arcade::CommandType::GO_UP:
                const_cast<Pacman *>(&pacman.getPacman())->goUp(NULL);
                break;
            case arcade::CommandType::GO_DOWN:
                const_cast<Pacman *>(&pacman.getPacman())->goDown(NULL);
                break;
            case arcade::CommandType::GO_LEFT:
                const_cast<Pacman *>(&pacman.getPacman())->goLeft(NULL);
                break;
            case arcade::CommandType::GO_RIGHT:
                const_cast<Pacman *>(&pacman.getPacman())->goRight(NULL);
                break;
            case arcade::CommandType::PLAY:
                components = pacman.compute(-1);
                while (!components.empty())
                {
                    delete (components.top());
                    components.pop();
                }
                break;
            default:
                break;
        }
    }
    free(map);
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
    if (state == Ghost::HUNTING)
    {
        std::vector<Ghost>::const_iterator itGhost = m_ghosts.begin();
        while (itGhost != m_ghosts.end())
        {
            if ((*itGhost).GetState() == Ghost::HUNTING)
            {
                newMap[(int)(*itGhost).getPosition().y][(int)(*itGhost).getPosition().x] = 'X';
            }
            ++itGhost;
        }
    }
}

// Updates the positions of pacman and all the ghosts
void PacmanGame::MoveEntities()
{
    Vector2<double> newPacPos = m_pacman.Move(m_map);
    std::vector<Ghost>::iterator itGhost = m_ghosts.begin();

    while (itGhost != m_ghosts.end())
    {
        char newMap[31][51];

        onReplaceGhostByWall(newMap, (*itGhost).GetState());
        // If pacman is immortal, it kills the ghost, otherwise it dies
        if ((*itGhost).Move(newMap, newPacPos).isEqual(newPacPos, 0.5))
        {
            if (m_pacman.GetState() == Pacman::MORTAL)
            {
                Die();
                return;
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
                if ((*itGhost).GetState() == Ghost::HUNTING)
                {
                    (*itGhost).SetState(Ghost::SCARED);
                }
                ++itGhost;
            }

            auto chronoDup = std::find_if(std::begin(m_chronos), std::end(m_chronos),
                                   [&](std::unique_ptr<IChrono>& c)
                                   { return *c.get() == std::string("Pacgum"); });

            // If the powerup is already active, we reset it
            if (chronoDup != m_chronos.end())
            {
                (*chronoDup).get()->ResetChrono();
            }
            else
            {
                m_chronos.emplace_back(
                        new Chrono<PacmanGame, void (PacmanGame::*)()>(10, *this, &PacmanGame::PacmanPowerUpEnd,
                                                                       "Pacgum"));
            }
        }
        m_score += 10;
        m_gums.remove(*it);
    }
    // If we ate the gums we restart the level
    if (m_gums.empty())
    {
        InitGame(true, true);
    }
}

void PacmanGame::Die()
{
    --m_lives;
    if (m_lives <= 0)
    {
        // Set game state to game over
        state = AGame::DEAD;
    }
    else
    {
        InitGame(false);
    }
}

void PacmanGame::StorePacgums()
{
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 50; ++x)
        {
            if (m_map[y][x] == '.')
            {
                m_gums.push_back(Gums(Vector2<double>(x, y), false));
            }
            else if (m_map[y][x] == 'o')
            {
                m_gums.push_back(Gums(Vector2<double>(x, y), true));
            }
        }
    }
}

// Update all the timers currently active
void PacmanGame::UpdateChrono()
{
    //Chrono <Pacman, Pacman::PacmanState (Pacman::*)()> c(60);

    std::vector<std::unique_ptr<IChrono>>::iterator it = m_chronos.begin();

    while (it != m_chronos.end())
    {
        (*it).get()->Update();
        if ((*it).get()->GetRemainingTime() <= 0)
        {
            (*it).get()->TriggerEvent();
            m_chronos.erase(it);
            it = m_chronos.begin();
        }
        else
        {
            ++it;
        }
    }
}

// Free the ghosts !!
void PacmanGame::FreeGhosts()
{
    for (std::vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); ++it)
    {
        if ((*it).GetState() == Ghost::FREEZE || (*it).GetState() == Ghost::SCARED)
        {
            (*it).SetState(Ghost::HUNTING);
        }
    }
}

void PacmanGame::PacmanPowerUpEnd()
{
    m_pacman.SetState(Pacman::MORTAL);
    FreeGhosts();
}

std::vector<std::string>    PacmanGame::getMap(void) const
{
    std::vector<std::string>    map;

    for (size_t i = 0, len = ArcadeSystem::winHeight; i < len; ++i)
    {
        map.push_back(m_map[i]);
    }
    return map;
}

const Pacman &PacmanGame::getPacman(void) const
{
    return m_pacman;
}
