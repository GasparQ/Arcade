//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Sun Apr  3 15:27:03 2016 Victor Gouet
//

#include <unistd.h>
#include "../include/CentipedeGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Protocol.hpp"

/*
 * \brief Create the centipede game, initialise UIComponent and lauch the game
 */
CentipedeGame::CentipedeGame() :
        AGame("Centipede"),
        centipede(Vector2<double>(10, 0))
{
    highScoreComponent = NULL;
    // initMap();

    waveCom = new UIComponent(Vector2<double>(0, 0),
                              AComponent::COLOR_WHITE,
                              Vector2<double>(5, 1), "");

    _wave = 1;
    waveCom->setText("wave : " + std::to_string(_wave));
    waveCom->setPos(Vector2<double>(1, 1));

    _oldStack.push(waveCom);

    scoreCom = new UIComponent(Vector2<double>(0, 0),
                               AComponent::COLOR_WHITE,
                               Vector2<double>(5, 1), "");

    _oldStack.push(scoreCom);

    missilCom = new GameComponent(Vector2<double>(0, 0),
                                  AComponent::ComponentColor::COLOR_GREEN,
                                  GameComponent::Shapes::SPHERE_SMALL, " ", "./sprites/missile.bmp");

    centipedeMusic = new AudioComponent("Sound/CentipedeIntro.wav", false, false, false);

    centipedeExplosion = new AudioComponent("Sound/CentipedeExplosion.wav", false, true, false);

    spaceShipShoot = new AudioComponent("Sound/CentipedeShot.wav", false, true, false);

    restart();
}

CentipedeGame::~CentipedeGame()
{
    if (scoreCom)
    {
        delete scoreCom;
    }
    if (waveCom)
    {
        delete waveCom;
    }
    if (missilCom)
    {
        delete missilCom;
    }
    if (centipedeMusic)
      {
	delete centipedeMusic;
      }
    if (centipedeExplosion)
      {
	delete centipedeExplosion;
      }
    if (spaceShipShoot)
      {
	delete spaceShipShoot;
      }
}

/*
 * \brief determine what the missile is touching / wall / centipede / nothing
 */
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

        if (*vecShoot >= Vector2<double>(0, 0) && *vecShoot < Vector2<double>(50, 30) &&
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] != ' ')
        {
	  // HIT A WALL

            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)]
                    = static_cast<char>(map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] - 1);
            spaceShip.stopShot();

            return;
        }

        itNewVec = centipede.getPos();
        std::list<Vector2<double> >::iterator itNc = itNewVec.begin();

        while (itNc != itNewVec.end())
        {
            if (static_cast<int>(itNc->x) == static_cast<int>(vecShoot->x) &&
                static_cast<int>(itNc->y) == static_cast<int>(vecShoot->y) &&
                *vecShoot >= Vector2<double>(0, 0) && *vecShoot < Vector2<double>(50, 30))
            {

                // HIT THE CENTIPEDE

                _score += 10;
                centipede.splitCentipede(*itNc);
                map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] = block;
                spaceShip.stopShot();
		output.push(centipedeExplosion);
                return;
            }
            ++itNc;
        }

        if (vecShoot->y < 0)
        {

	  // HIT NOTHING AND TOO FAR

            spaceShip.stopShot();
        }
        else
        {
            if ((vecShoot = spaceShip.getShoot()) != NULL)
            {
                missilCom->setPos(*vecShoot);
                output.push(missilCom);
            }
        }
    }
}

/*
 * \brief if there is no centipede
 */
bool                    CentipedeGame::isEmptyCentipede() const
{
    return (centipede.getPos().empty());
}

/*
 * \brief compute the game / will make an action with the keycode
 */
std::stack<AComponent *> CentipedeGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::vector<AComponent *> vec;

    while (!_output.empty())
    {
        if (_output.top())
            delete _output.top();
        _output.pop();
    }
    if (state == ALIVE)
    {
        output = this->_oldStack;
	if (this->_oldStack.size() == 3)
	  {
	    _oldStack.pop();
	  }
        onShoot(output);
        if (centipede.isTouching(spaceShip.getPos()))
        {
            state = DEAD;
            return (output);
        }
        if (keycode == ArcadeSystem::Space)
        {
            spaceShip.shoot();
            output.push(spaceShipShoot);
        }
        if (isEmptyCentipede())
        {
            ++_wave;
            if (_wave > waveNbr)
            {
                state = DEAD;
            }
            // CENTIPEDE DESTROY
            initVariable();
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

        scoreCom->setText("score : " + std::to_string(_score));
        scoreCom->setPos(
                Vector2<double>(static_cast<int>(ArcadeSystem::winWidth - scoreCom->getText().length()) / 2, 1));

        waveCom->setText("wave : " + std::to_string(_wave));
        waveCom->setPos(Vector2<double>(1, 1));
    }
    else
    {
        // DEAD
        if (highScoreComponent)
            delete (highScoreComponent);
        highScoreComponent = new HighScoreComponent(this->getName(),
                                                    _score);
        highScoreComponent->UpdatePseudo(keycode);
        if (keycode == ArcadeSystem::Enter && highScoreComponent->submit())
        {
            state = AGame::GameState::ALIVE;
            delete (highScoreComponent);
            highScoreComponent = NULL;
            restart();
        }
        else
            output.push(highScoreComponent);
    }
    return (output);
}

void        CentipedeGame::initVariable()
{
    centipede.clean();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
    centipede.add_node();
}


/*
 * \brief Restart the game
 */
void CentipedeGame::restart()
{
  _oldStack.push(centipedeMusic);
    initMap();
    spaceShip.reinitPos();
    _wave = 1;
    _score = 0;
    initVariable();
}

/*
 * \brief Will add the map into the output stack
 */
void            CentipedeGame::displayMap(std::stack<AComponent *> &output) const
{
    int y;
    int x;

    y = 0;
    while (y < 30)
    {
        x = 0;
        while (x < 50)
        {
            if (map[y][x] != ' ')
            {
                int ref = map[y][x] - ' ';
                GameComponent *gameCom = new GameComponent(Vector2<double>(x, y),
                                                           AComponent::ComponentColor::COLOR_WHITE,
                                                           GameComponent::Shapes::CUBE_LARGE, " ", "FILE");
                switch (ref)
                {
                    case 1:
                        gameCom->setColor(AComponent::ComponentColor::COLOR_WHITE);
                        gameCom->setSprite2D("./sprites/mushroom.bmp");
                        break;
                    case 2:
                        gameCom->setColor(AComponent::ComponentColor::COLOR_YELLOW);
                        gameCom->setSprite2D("./sprites/mushroom1.bmp");
                        break;
                    case 3:
                        gameCom->setColor(AComponent::ComponentColor::COLOR_GREEN);
                        gameCom->setSprite2D("./sprites/mushroom2.bmp");
                        break;
                    case 4:
                        gameCom->setColor(AComponent::ComponentColor::COLOR_BLUE);
                        gameCom->setSprite2D("./sprites/mushroom3.bmp");
                        break;
                    case 5:
                        gameCom->setColor(AComponent::ComponentColor::COLOR_RED);
                        gameCom->setSprite2D("./sprites/mushroom4.bmp");
                        break;
                    default:
                        break;
                }
                output.push(gameCom);
                _output.push(gameCom);
            }
            ++x;
        }
        ++y;
    }
}

void                CentipedeGame::initMap()
{
    int y = 0;
    int x = 0;

    while (y < 30)
    {
        x = 0;
        while (x < 50)
        {
            if (y != 25 && x != 20)
                map[y][x] = (rand() % 30 == 0 ? block : ' ');
            else
                map[y][x] = ' ';
            ++x;
        }
        map[y][x] = '\0';
        ++y;
    }
}

std::vector<std::string>        CentipedeGame::getMap() const
{
    std::vector<std::string>    converMap;

    for (size_t y = 0; y < 30; ++y)
    {
        converMap.push_back(map[y]);
    }
    return converMap;
}

Centipede const &CentipedeGame::getCentipede() const
{
    return centipede;
}

USSEnterprise const &CentipedeGame::getUssEntreprise() const
{
    return spaceShip;
}

void CentipedeGame::goRight()
{
    spaceShip.goRight(map);
}

void CentipedeGame::goLeft()
{
    spaceShip.goLeft(map);
}

void CentipedeGame::goUp()
{
    spaceShip.goUp(map);
}

void CentipedeGame::goDown()
{
    spaceShip.goDown(map);
}

void CentipedeGame::shoot()
{
    spaceShip.shoot();
}

extern "C" IGame *loadGame()
{
    return (new CentipedeGame());
}

void                            updateMap(struct arcade::GetMap *map, CentipedeGame const &centipedeGame)
{
    std::vector<std::string>    centMap = centipedeGame.getMap();
    std::list<Vector2<double> > centipedePoses = centipedeGame.getCentipede().getPos();
    Vector2<double>             *shoot = centipedeGame.getUssEntreprise().getShoot();

    for (size_t y = 0; y < 30; ++y)
    {
        for (size_t x = 0; x < 50; x++)
        {
            map->tile[y * ArcadeSystem::winWidth + x] = centMap[y][x] != ' ' ? arcade::TileType::OBSTACLE : arcade::TileType::EMPTY;
        }
    }
    for (std::list<Vector2<double> >::iterator it = centipedePoses.begin(), end = centipedePoses.end(); it != end; ++it)
    {
        map->tile[static_cast<size_t >(it->x) + static_cast<size_t >(it->y) * ArcadeSystem::winWidth] = arcade::TileType::EVIL_DUDE;
    }
    if (shoot)
    {
        map->tile[static_cast<size_t >(shoot->x) + static_cast<size_t>(shoot->y) * ArcadeSystem::winWidth] = arcade::TileType::MY_SHOOT;
    }
}

void                        whereAmI(CentipedeGame const &centipedeGame)
{
    struct arcade::WhereAmI *pos;
    size_t                  posSize = sizeof(*pos) + sizeof(arcade::Position);

    if ((pos = (arcade::WhereAmI *)malloc(posSize)) == NULL)
        throw std::bad_alloc();
    pos->type = arcade::CommandType::WHERE_AM_I;
    pos->lenght = static_cast<uint16_t>(1);
    pos->position[0].x = static_cast<uint16_t >(centipedeGame.getUssEntreprise().getPos().x);
    pos->position[0].y = static_cast<uint16_t >(centipedeGame.getUssEntreprise().getPos().y);
    write(1, pos, posSize);
}

extern "C" void Play(void)
{
    arcade::CommandType c;
    CentipedeGame centipedeGame;
    struct arcade::GetMap *map;
    size_t mapSize = sizeof(*map) + ArcadeSystem::winWidth * ArcadeSystem::winHeight * sizeof(uint16_t);

    if ((map = (arcade::GetMap *)malloc(mapSize)) == NULL)
        throw std::bad_alloc();
    map->type = arcade::CommandType::GET_MAP;
    map->width = ArcadeSystem::winWidth;
    map->height = ArcadeSystem::winHeight;
    while (read(0, &c, sizeof(c)))
    {
        switch (static_cast<arcade::CommandType>(c))
        {
            case arcade::CommandType::WHERE_AM_I:
                whereAmI(centipedeGame);
                break;
            case arcade::CommandType::GET_MAP:
                updateMap(map, centipedeGame);
                write(1, map, mapSize);
                break;
            case arcade::CommandType::GO_UP:
                centipedeGame.goUp();
                break;
            case arcade::CommandType::GO_DOWN:
                centipedeGame.goDown();
                break;
            case arcade::CommandType::GO_LEFT:
                centipedeGame.goLeft();
                break;
            case arcade::CommandType::GO_RIGHT:
                centipedeGame.goRight();
                break;
            case arcade::CommandType::SHOOT:
                centipedeGame.shoot();
                break;
            case arcade::CommandType::PLAY:
                centipedeGame.compute(-1);
                break;
            default:
                break;
        }
    }
    free(map);
}
