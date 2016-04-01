//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Fri Apr  1 16:37:32 2016 Victor Gouet
//

#include "../include/CentipedeGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

CentipedeGame::CentipedeGame() :
        AGame("Centipede"),
        centipede(Vector2<double>(0, 0))
{
  highScoreComponent = NULL;
  initMap();
  restart();

  waweCom = new UIComponent(Vector2<double>(0, 0),
			    AComponent::COLOR_WHITE,
			    Vector2<double>(5, 1), "");

  waweCom->setText("wave : " + std::to_string(_wave));
  waweCom->setPos(Vector2<double>(1, 1));

  _oldStack.push(waweCom);

  scoreCom = new UIComponent(Vector2<double>(0, 0),
			     AComponent::COLOR_WHITE,
			     Vector2<double>(5, 1), "");

  _oldStack.push(scoreCom);

  missilCom = new GameComponent(Vector2<double>(0, 0),
				AComponent::ComponentColor::COLOR_GREEN,
				GameComponent::Shapes::SPHERE_SMALL, " ", "FILE");
}

CentipedeGame::~CentipedeGame()
{
  if (scoreCom)
    {
      delete scoreCom;
    }
  if (waweCom)
    {
      delete waweCom;
    }
  if (missilCom)
    {
      delete missilCom;
    }
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

        if (*vecShoot >= Vector2<double>(0, 0) && *vecShoot < Vector2<double>(50, 30) &&
            map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] != ' ')
        {
	  map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)]
                    = static_cast<char>(map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] - 1);
	  spaceShip.stopShot();
	    
	    return ;
        }

        itNewVec = centipede.getPos();
        std::list<Vector2<double> >::iterator itNc = itNewVec.begin();

        while (itNc != itNewVec.end())
        {
            if (static_cast<int>(itNc->x) == static_cast<int>(vecShoot->x) &&
                static_cast<int>(itNc->y) == static_cast<int>(vecShoot->y) &&
		*vecShoot >= Vector2<double>(0, 0) && *vecShoot < Vector2<double>(50, 30))
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

        if (vecShoot->y < 0)
        {
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

bool                    CentipedeGame::isEmptyCentipede() const
{
  return (centipede.getPos().empty());
}

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

	// UIComponent		*scoreCom = new UIComponent(Vector2<double>(0, 0),
	// 						    AComponent::COLOR_WHITE,
	// 						    Vector2<double>(5, 1), "");

	scoreCom->setText("score : " + std::to_string(_score));
	scoreCom->setPos(Vector2<double>(static_cast<int>(ArcadeSystem::winWidth - scoreCom->getText().length()) / 2, 1));

	// output.push(scoreCom);
	
	// UIComponent		*waweCom = new UIComponent(Vector2<double>(0, 0),
	// 						   AComponent::COLOR_WHITE,
	// 						   Vector2<double>(5, 1), "");

	waweCom->setText("wave : " + std::to_string(_wave));
	waweCom->setPos(Vector2<double>(1, 1));

	// output.push(waweCom);
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
    while (y < 30)
    {
        x = 0;
        while (x < 50)
        {
            if (map[y][x] != ' ')
	      {
		int	ref = map[y][x] - ' ';
		GameComponent	*gameCom = new GameComponent(Vector2<double>(x, y),
							     AComponent::ComponentColor::COLOR_WHITE ,
							     GameComponent::Shapes::CUBE_LARGE, " ", "FILE");
	        switch (ref)
		  {
		  case 1:
		    gameCom->setColor(AComponent::ComponentColor::COLOR_WHITE);
	            break;
		  case 2:
		    gameCom->setColor(AComponent::ComponentColor::COLOR_YELLOW);
	            break;
		  case 3:
		    gameCom->setColor(AComponent::ComponentColor::COLOR_GREEN);
	            break;
		  case 4:
		    gameCom->setColor(AComponent::ComponentColor::COLOR_BLUE);
	            break;
		  case 5:
		    gameCom->setColor(AComponent::ComponentColor::COLOR_RED);
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
        ++y;
    }
}

extern "C" IGame *loadGame()
{
    return (new CentipedeGame());
}
