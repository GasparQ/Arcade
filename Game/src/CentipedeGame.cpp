//
// CentipedeGame.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:20:01 2016 Victor Gouet
// Last update Wed Mar 30 22:13:48 2016 Victor Gouet
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

        it = centipede.begin();	
	while (it != centipede.end())
	  {
	    itNewVec = it->getPos();
	    std::vector<Vector2<double> >::iterator		itNc = itNewVec.begin();
	    while (itNc != itNewVec.end())
	      {
		// std::cout << *itNc << std::endl;
		// if (itNc->y >= 31 || itNc->x < 0 || itNc->x >= 51)
		//   {
		//     // LE CENTIPEDE TOUCHE LE FOND
		    
		//     it = centipede.erase(it);
		//     break;
		//   }
		if (*itNc == *vecShoot)
		  {

		    // TOUCHER PAR LE SHOOT

		    centipede.push_back(it->splitCentipede(*itNc));
		    map[static_cast<int>(vecShoot->y)][static_cast<int>(vecShoot->x)] = 'X';
		    spaceShip.stopShot();
		    return ;
		  }
		++itNc;
	      }
	    if (it != centipede.end())
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

bool					CentipedeGame::isEmptyCentipede() const
{
  std::vector<Centipede>::const_iterator	it;

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
      std::vector<Vector2<double> >			nc = it->getPos();
      std::vector<Vector2<double> >::iterator		itNc = nc.begin();

      while (itVec != vec.end())
	{
	  if (itNc->y >= 31 || itNc->x < 0 || itNc->x >= 51)
	    {
	      // LE CENTIPEDE TOUCHE LE FOND
	      
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
  Centipede	newCentipede(Vector2<double>(0, 0));

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
