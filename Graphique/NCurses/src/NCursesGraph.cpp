//
// NCursesGraph.cpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 15:05:21 2016 Victor Gouet
// Last update Thu Mar 10 15:39:22 2016 Victor Gouet
//

#include "../include/NCursesGraph.hpp"

NCursesGraph::NCursesGraph()
{
  NCurses::init();
  NCurses::noEchoMode();
  NCurses::hide_cursor();
  NCurses::delayOnGetOutput(3);
  _board = new ncr::Window(31, 51, 0, 0);
  gameWin = new ncr::Window(30, 50, 1, 1, _board->getWin());
  _board->attrON(A_REVERSE);
  _board->makeBorder(' ', ' ', ' ');
  _board->attrOFF(A_REVERSE);
}

NCursesGraph::~NCursesGraph()
{
  if (gameWin)
    delete gameWin;
  NCurses::destroy();
}
#include <unistd.h>
int	NCursesGraph::eventManagment()
{
    std::cout << "COUCOU" << std::endl;
    usleep(500000);
  return (NCurses::getCarac());
}

void	        NCursesGraph::_gameComponent(GameComponent *gameComponent) const
{
  Vector2	pos = gameComponent->getPos();

  gameWin->print(pos.x, pos.y, "%s", gameComponent->getSpriteText().c_str());
}

void	NCursesGraph::display(std::stack<AComponent *>	obj)
{
  GameComponent	*gameComponent;

  gameWin->clear();
  while (!obj.empty())
    {
      if ((gameComponent = dynamic_cast<GameComponent *>(obj.top())) != NULL)
	{
	  _gameComponent(gameComponent);
	}
      obj.pop();
    }
}

extern "C" IGraph *loadLib()
{
    IGraph  *toto;
    toto = new NCursesGraph();
    std::cout << "toto: " << toto << std::endl;
    toto->eventManagment();
    std::cout << "COUCOU" << std::endl;
    usleep(500000);
    return toto;
}
