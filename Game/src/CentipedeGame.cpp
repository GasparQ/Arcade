//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Thu Mar 31 23:42:57 2016 Victor Gouet
//

#include "../include/CentipedeGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include "../../Commons/include/UIComponent.hpp"

CentipedeGame::CentipedeGame() :
        AGame("Centipede"),
        centipede(Vector2<double>(0, 0))
{
  highScoreComponent = NULL;
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

        if (vecShoot->y < 0 ||
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] != ' ')
        {
            spaceShip.stopShot();
        }
        else
        {
	  if ((vecShoot = spaceShip.getShoot()) != NULL)
            output.push(new GameComponent(*vecShoot,
                                          AComponent::ComponentColor::COLOR_GREEN,
                                          GameComponent::Shapes::SPHERE_SMALL, " ", "FILE"));
        }
    }
}

bool                    CentipedeGame::isEmptyCentipede() const
{
  return (centipede.getPos().empty());
}

std::stack<AComponent *> CentipedeGame::compute(int keycode)
{
    std::stack<AComponent *> output;
    std::vector<AComponent *> vec;

    if (state == ALIVE)
      {
	onShoot(output);
	if (centipede.isTouching(spaceShip.getPos()))
	  {
	    state = DEAD;
	    return (output);
	  }
	if (keycode == ArcadeSystem::Space)
	  {
	    spaceShip.shoot();
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
	UIComponent		*scoreCom = new UIComponent(Vector2<double>(0, 0),
							    AComponent::COLOR_WHITE,
							    Vector2<double>(5, 1), "");
	scoreCom->setText("score : " + std::to_string(_score));
	scoreCom->setPos(Vector2<double>(static_cast<int>(ArcadeSystem::winWidth - scoreCom->getText().length()) / 2, 1));
	output.push(scoreCom);
	
	UIComponent		*waweCom = new UIComponent(Vector2<double>(0, 0),
							   AComponent::COLOR_WHITE,
							   Vector2<double>(5, 1), "");
	waweCom->setText("wave : " + std::to_string(_wave));
	waweCom->setPos(Vector2<double>(1, 1));
	output.push(waweCom);
      }
    else
      {
	// DEAD
	if (highScoreComponent)
	  delete(highScoreComponent);
        highScoreComponent = new HighScoreComponent(this->getName(),
						    _score);
        highScoreComponent->UpdatePseudo(keycode);
        if (keycode == ArcadeSystem::Enter && highScoreComponent->submit())
        {
            state = AGame::GameState::ALIVE;
            delete(highScoreComponent);
            highScoreComponent = NULL;
            restart();
        }
        else
            output.push(highScoreComponent);
      }

    return (output);
}

void		CentipedeGame::initVariable()
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

void CentipedeGame::restart()
{
  spaceShip.reinitPos();
  _wave = 1;
  _score = 0;
  initVariable();
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
	  if (y != 20 && x != 20)
            map[y][x] = (rand() % 30 == 0 ? block : ' ');
	  else
	    map[y][x] = ' ';
            ++x;
        }
        ++y;
    }
}

extern "C" IGame *loadGame()
{
    return (new CentipedeGame());
}
