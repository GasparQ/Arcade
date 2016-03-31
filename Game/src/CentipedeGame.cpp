//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Thu Mar 31 18:34:40 2016 Victor Gouet
//

#include "../include/CentipedeGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

CentipedeGame::CentipedeGame() :
        AGame("Centipede"),
        centipede(Vector2<double>(0, 0))
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
        if (*vecShoot >= Vector2<double>(0, 0) &&
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] != ' ')
        {
            // TOUCHE UN BLOCK
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)]
                    = static_cast<char>(map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] - 1);
            if (map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] == ' ')
                spaceShip.stopShot();
        }
//        it = centipede.begin();
//        while (it != centipede.end())
//        {
        itNewVec = centipede.getPos();
        std::list<Vector2<double> >::iterator itNc = itNewVec.begin();
        while (itNc != itNewVec.end())
        {
            if (static_cast<int>(itNc->x) == static_cast<int>(vecShoot->x) &&
                static_cast<int>(itNc->y) == static_cast<int>(vecShoot->y))
            {

                // TOUCHER PAR LE SHOOT

                _score += 10;
                centipede.splitCentipede(*itNc);
                map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] = block;
                spaceShip.stopShot();
                return;
            }
            ++itNc;
        }
//            if (it != centipede.end())
//                ++it;
//        }

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
//    std::vector<Centipede>::const_iterator it;
//
//    it = centipede.begin();
//    while (it != centipede.end())
//    {
//        if (!it->getPos().empty())
//        {
//            return (false);
//        }
//        ++it;
//    }
    return (centipede.getPos().empty());
}

std::stack<AComponent *> CentipedeGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::vector<AComponent *> vec;

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
    _score -= centipede.move(map);
    vec = centipede.getGameComponent();
    for (std::vector<AComponent *>::iterator it1 = vec.begin(); it1 != vec.end(); ++it1)
    {
        output.push(*it1);
    }
    spaceShip.move(keycode, map);
    displayMap(output);
    output.push(spaceShip.getGameComponent());
    return (output);
}

void CentipedeGame::restart()
{
//    Centipede newCentipede(Vector2<double>(0, 0));

    _score = 0;
    centipede.clean();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
//    centipede.push_back(newCentipede);
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
//             map[y][x] = ' ';
            ++x;
        }
        ++y;
    }
}

extern "C" IGame *loadGame()
{
    return (new CentipedeGame());
}
