//
// NCursesGraph.cpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 15:05:21 2016 Victor Gouet
// Last update Fri Mar 11 12:54:38 2016 Victor Gouet
//

#include "../include/NCursesGraph.hpp"
#include "../../../Arcade.hpp"

NCursesGraph::NCursesGraph()
{
  NCurses::init();
  NCurses::noEchoMode();
  NCurses::hide_cursor();
  NCurses::delayOnGetOutput();
  _board = new ncr::Window(arcade::winHeight + 2, arcade::winWidth + 2, 0, 0);
  gameWin = new ncr::Window(arcade::winHeight, arcade::winWidth, 1, 1, *_board);

  _board->attrON(A_REVERSE);
  _board->makeBorder(' ', ' ', ' ');
  _board->attrOFF(A_REVERSE);

  NCurses::initPair(1, COLOR_CYAN, COLOR_BLACK);
  gameWin->setColorPair(1);
}

NCursesGraph::~NCursesGraph()
{
  if (gameWin)
    delete gameWin;
  NCurses::destroy();
}

int	NCursesGraph::eventManagment()
{
  return (NCurses::getCarac());
}

void	        NCursesGraph::_gameComponent(GameComponent *gameComponent) const
{
  Vector2	pos = gameComponent->getPos();

  gameWin->attrON(A_REVERSE);
  gameWin->print(pos.x, pos.y, "%s", gameComponent->getSpriteText().c_str());
  gameWin->attrOFF(A_REVERSE);
}

void		NCursesGraph::_cacheClear()
{
  if (_cacheGame.empty())
    gameWin->clear();
  while (!_cacheGame.empty())
    {
      gameWin->print(_cacheGame.top().x, _cacheGame.top().y, " ");
      _cacheGame.pop();
    }
}

void	NCursesGraph::display(std::stack<AComponent *>	obj)
{
  GameComponent	*gameComponent;

  _cacheClear();
  while (!obj.empty())
    {
      if ((gameComponent = dynamic_cast<GameComponent *>(obj.top())) != NULL)
  	{
  	  _gameComponent(gameComponent);
  	  _cacheGame.push(gameComponent->getPos());
  	}
      obj.pop();
    }
  gameWin->refresh();
}

extern "C" IGraph *loadLib()
{
    return new NCursesGraph();
}
