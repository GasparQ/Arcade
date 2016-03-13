//
// NCursesGraph.cpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 15:05:21 2016 Victor Gouet
// Last update Sun Mar 13 12:30:53 2016 Victor Gouet
//

#include "../include/NCursesGraph.hpp"
#include "../../../Arcade.hpp"

NCursesGraph::NCursesGraph()
{
  _board = NULL;
  gameWin = NULL;
  UIWin = NULL;
  if (NCurses::init() == NULL)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::noEchoMode() == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::hide_cursor() == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::delayOnGetOutput() == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  
  if (!isResizeGood())
    NCurses::destroy(), throw ResizeFailed();

  _board = new ncr::Window(arcade::winHeight + 2, arcade::winWidth + 2, 0, 0);
  gameWin = new ncr::Window(arcade::winHeight, arcade::winWidth, 1, 1, *_board);
  UIWin = new ncr::Window(3, arcade::winWidth - 1, 2, arcade::winHeight + 3);

  if (NCurses::initPair(1, COLOR_RED, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::initPair(2, COLOR_GREEN, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::initPair(3, COLOR_YELLOW, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::initPair(4, COLOR_BLUE, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::initPair(5, COLOR_MAGENTA, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::initPair(6, COLOR_CYAN, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();
  if (NCurses::initPair(7, COLOR_WHITE, COLOR_BLACK) == ERR)
    NCurses::destroy(), throw NCursesSystemFailed();

  _board->attrON(A_REVERSE | COLOR_PAIR(4));
  _board->makeBorder(' ', ' ', ' ');
  _board->attrOFF(A_REVERSE);

  UIWin->attrON(A_REVERSE | COLOR_PAIR(4));
  UIWin->makeBorder(' ', ' ', ' ');
  UIWin->attrOFF(A_REVERSE);

  // TODO init les keycode de keycodeMap avec la SDL
}

NCursesGraph::~NCursesGraph()
{
  if (gameWin)
    delete gameWin;
  if (UIWin)
    delete UIWin;
  if (_board)
    delete _board;
  NCurses::destroy();
}

bool			NCursesGraph::isResizeGood() const
{
  int	x;
  int	y;

  if (NCurses::getMaxXY(x, y) == ERR)
    return (false);
  if (static_cast<unsigned int>(x) < arcade::winWidth + 2)
    return (false);
  if (static_cast<unsigned int>(y) < arcade::winHeight + 2)
    return (false);
  return (true);
}

int	NCursesGraph::eventManagment()
{
  int	keycode;
  std::map<int, int>::iterator	it;

  keycode = NCurses::getCarac();
  if (keycode == KEY_RESIZE && !isResizeGood())
    throw ResizeFailed();
  // TODO Recuperer les keycode de la SDL pour se caler avec
  // if ((it = keycodeMap.find(keycode)) != keycodeMap.end())
  //   return (it->second);
  return (keycode);
}

void	        NCursesGraph::_displayComponent(GameComponent *gameComponent) const
{
  Vector2	pos = gameComponent->getPos();

  gameWin->attrON(A_REVERSE | COLOR_PAIR(gameComponent->getColor()));
  gameWin->print(pos.x, pos.y, "%s", gameComponent->getSpriteText().c_str());
  gameWin->attrOFF(A_REVERSE);
}

void	        NCursesGraph::_displayComponent(UIComponent *uiComponent) const
{
  Vector2	pos = uiComponent->getPos();

  UIWin->attrON(COLOR_PAIR(uiComponent->getColor()) | A_BOLD);
  UIWin->print(pos.x, pos.y, "%s", uiComponent->getText().c_str());
}

void		NCursesGraph::_cacheClear()
{
  if (_cacheGame.empty())
    gameWin->clear();
  while (!_cacheGame.empty())
    {
      std::string space(_cacheGame.top().str);
      _cacheGame.top().win->print(_cacheGame.top().vector.x,
				  _cacheGame.top().vector.y,
				  space.replace(space.begin(),
						space.end(),
						space.size(),
						' ').c_str());
      _cacheGame.pop();
    }
}

void	NCursesGraph::display(std::stack<AComponent *>	obj)
{
  GameComponent	*gameComponent;
  UIComponent	*uiComponent;

  _cacheClear();
  while (!obj.empty())
    {
      if ((gameComponent = dynamic_cast<GameComponent *>(obj.top())) != NULL)
      	{
      	  _displayComponent(gameComponent);
      	  _cacheGame.push(s_cache(gameComponent->getPos(),
      				  gameComponent->getSpriteText(), gameWin));
      	}
      else if ((uiComponent = dynamic_cast<UIComponent *>(obj.top())) != NULL)
      	{
  	  _displayComponent(uiComponent);
  	  _cacheGame.push(s_cache(uiComponent->getPos(), uiComponent->getText(), UIWin));
  	}
      delete obj.top();
      obj.pop();
    }
  gameWin->refresh();
  UIWin->refresh();
}

extern "C" IGraph *loadLib()
{
    return new NCursesGraph();
}
