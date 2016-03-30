//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Wed Mar 30 17:14:58 2016 Victor Gouet
//

#include "../include/CentipedeGame.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"
#include <algorithm>

CentipedeGame::CentipedeGame() : AGame("Centipede")
{
  // initMap();
  restart();
}

CentipedeGame::~CentipedeGame()
{

}

void			CentipedeGame::onShoot(std::stack<AComponent *> &output)
{
  std::vector<Centipede>::iterator	it;
  std::vector<AComponent *>		vec;
  std::vector<AComponent *>::iterator	itVec;
  Vector2<double>			*vecShoot;
  std::vector<Vector2<double> >		itNewVec;
  
  if ((vecShoot = spaceShip.getShoot()) != NULL)
    {
      *vecShoot = *vecShoot + Vector2<double>(0, -1);

      // TOUCH
      // SHOOT
        it = centipede.begin();	
	while (it != centipede.end())
	  {
	    itNewVec = it->getPos();
	    std::vector<Vector2<double> >::iterator		itNc = itNewVec.begin();
	    while (itNc != itNewVec.end())
	      {
		if (*itNc == *vecShoot)
		  {
		    centipede.push_back(Centipede(*itNc));
		    map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] = 'X';
		    spaceShip.stopShot();
		    return ;
		  }
		++itNc;
	      }
	    ++it;
	  }

      if (vecShoot->y < 0 ||
	  map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] == 'X')
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

std::stack<AComponent *> CentipedeGame::compute(int keycode)
{
  std::stack<AComponent *>		output;
  std::vector<Centipede>::iterator	it;
  std::vector<AComponent *>		vec;
  std::vector<AComponent *>::iterator	itVec;
  std::vector<Vector2<double> >		itNewVec;

  onShoot(output);
  if (keycode == ArcadeSystem::Space)
    {
      spaceShip.shoot();
    }
  it = centipede.begin();
  while (it != centipede.end())
    {
      it->move(map);
      vec = it->getGameComponent();
      itVec = vec.begin();
      while (itVec != vec.end())
	{
	  output.push(*itVec);
	  ++itVec;
	}
      ++it;
    }
  spaceShip.move(keycode, map);
  displayMap(output);
  output.push(spaceShip.getGameComponent());
  return (output);
}

void CentipedeGame::restart()
{
  initMap();
  centipede.push_back(Centipede(Vector2<double>(0, 0)));
}

void			CentipedeGame::displayMap(std::stack<AComponent *> &output) const
{
  int			y;
  int			x;

  y = 0;
  while (y < 31)
    {
      x = 0;
      while (x < 51)
	{
	  if (map[y][x] == block)
	    output.push(new GameComponent(Vector2<double>(x, y),
					  AComponent::ComponentColor::COLOR_RED,
					  GameComponent::Shapes::CUBE_LARGE, " ", "FILE"));
	  ++x;
	}
      ++y;
    }
}

void		        CentipedeGame::initMap()
{
  int			y = 0;
  int			x = 0;

  while (y < 31)
    {
      x = 0;
      while (x < 51)
	{
	  map[y][x] = (rand() % 30 == 0 ? 'X' : ' ');
	  ++x;
	}
      ++y;
    }
}

extern "C" IGame *loadGame()
{
  return (new CentipedeGame());
}
