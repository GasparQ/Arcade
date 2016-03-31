//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Thu Mar 31 16:11:26 2016 Victor Gouet
//

#include "../include/CentipedeGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

CentipedeGame::CentipedeGame() : AGame("Centipede")
{
    initMap();
    restart();
}

CentipedeGame::~CentipedeGame()
{

}

void            CentipedeGame::onShoot(std::stack<AComponent *> &output)
{
    std::vector<Centipede>::iterator it;
    std::vector<AComponent *> vec;
    std::vector<AComponent *>::iterator itVec;
    Vector2<double> *vecShoot;
    std::list<Vector2<double> > itNewVec;

    if ((vecShoot = spaceShip.getShoot()) != NULL)
    {
        *vecShoot = *vecShoot + Vector2<double>(0, -1);
        if (*vecShoot >= Vector2<double>(0, 0) && map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] != ' ')
        {
            // TOUCHE UN BLOCK
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)]
                    = static_cast<char>(map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] - 1);
            if (map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] == ' ')
                spaceShip.stopShot();
        }
        it = centipede.begin();
        while (it != centipede.end())
        {
            itNewVec = it->getPos();
            std::list<Vector2<double> >::iterator itNc = itNewVec.begin();
            while (itNc != itNewVec.end())
            {
                if (*itNc == *vecShoot)
                {

                    // TOUCHER PAR LE SHOOT
                    _score += 10;
                    centipede.push_back(it->splitCentipede(*itNc));
                    map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] = block;
                    spaceShip.stopShot();
                    return;
                }
                ++itNc;
            }
            if (it != centipede.end())
                ++it;
        }

        if (vecShoot->y < 0 ||
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] != ' ')
        {
            spaceShip.stopShot();
        }
        else
        {
            output.push(new GameComponent(*vecShoot,
                                          AComponent::ComponentColor::COLOR_GREEN,
                                          GameComponent::Shapes::SPHERE_SMALL, " ", "FILE"));
        }
    }
}

bool                    CentipedeGame::isEmptyCentipede() const
{
    std::vector<Centipede>::const_iterator it;

    it = centipede.begin();
    while (it != centipede.end())
    {
        if (!it->getPos().empty())
        {
            return (false);
        }
        ++it;
    }
    return (true);
}

std::stack<AComponent *> CentipedeGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::vector<Centipede>::iterator it;
    std::vector<AComponent *> vec;
    std::vector<AComponent *>::iterator itVec;
    std::vector<Vector2<double> > itNewVec;

    onShoot(output);
    if (keycode == ArcadeSystem::Space)
    {
        spaceShip.shoot();
    }
    if (isEmptyCentipede())
    {
        restart();
        return (output);
    }
    it = centipede.begin();
    while (it != centipede.end())
    {
        it->move(map);
        vec = it->getGameComponent();
        itVec = vec.begin();
        std::list<Vector2<double> > nc = it->getPos();
        std::list<Vector2<double> >::iterator itNc = nc.begin();

        while (itVec != vec.end())
        {
            if (itNc->y > 29 || itNc->x < 0 || itNc->x >= 51)
            {
                // LE CENTIPEDE TOUCHE LE FOND
                _score -= 30;
                it = centipede.erase(it);
                break;
            }
            output.push(*itVec);
            ++itVec;
        }
        if (it != centipede.end())
            ++it;
    }
    spaceShip.move(keycode, map);
    displayMap(output);
    output.push(spaceShip.getGameComponent());
    return (output);
}

void CentipedeGame::restart()
{
    Centipede newCentipede(Vector2<double>(0, 0));

    _score = 0;
    centipede.clear();
    newCentipede.add_node();
    newCentipede.add_node();
    newCentipede.add_node();
    newCentipede.add_node();
    newCentipede.add_node();
    newCentipede.add_node();
    newCentipede.add_node();
    centipede.push_back(newCentipede);
}

void            CentipedeGame::displayMap(std::stack<AComponent *> &output) const
{
    int y;
    int x;

    y = 0;
    while (y < 31)
    {
        x = 0;
        while (x < 51)
        {
            if (map[y][x] != ' ')
                output.push(new GameComponent(Vector2<double>(x, y),
                                              AComponent::ComponentColor::COLOR_RED,
                                              GameComponent::Shapes::CUBE_LARGE, " ", "FILE"));
            ++x;
        }
        ++y;
    }
}

void                CentipedeGame::initMap()
{
    int y = 0;
    int x = 0;

    while (y < 31)
    {
        x = 0;
        while (x < 51)
        {
            map[y][x] = (rand() % 30 == 0 ? block : ' ');
            // map[y][x] = ' ';
            ++x;
        }
        ++y;
    }
}

extern "C" IGame *loadGame()
{
    return (new CentipedeGame());
}
