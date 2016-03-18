//
// NCursesGraph.cpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 15:05:21 2016 Victor Gouet
// Last update Fri Mar 18 15:00:11 2016 Victor Gouet
//

#include "../include/NCursesGraph.hpp"
#include "../../../Commons/include/ArcadeSystem.hpp"

NCursesGraph::NCursesGraph()
{
  _board = NULL;
  gameWin = NULL;
  UIWin = NULL;
  _stdscr = NULL;

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

  // _board = new ncr::Window(ArcadeSystem::winHeight + 2, ArcadeSystem::winWidth + 2, 0, 0);
  // gameWin = new ncr::Window(ArcadeSystem::winHeight, ArcadeSystem::winWidth, 1, 1, *_board);
  // UIWin = new ncr::Window(3, ArcadeSystem::winWidth - 1, 2, ArcadeSystem::winHeight + 3);

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

  // _board->attrON(A_REVERSE | COLOR_PAIR(4));
  // _board->makeBorder(' ', ' ', ' ');
  // _board->attrOFF(A_REVERSE);

  // UIWin->attrON(A_REVERSE | COLOR_PAIR(4));
  // UIWin->makeBorder(' ', ' ', ' ');
  // UIWin->attrOFF(A_REVERSE);

  keycodeMap[260] = ArcadeSystem::ArrowLeft;
  keycodeMap[261] = ArcadeSystem::ArrowRight;
  keycodeMap[259] = ArcadeSystem::ArrowUp;
  keycodeMap[258] = ArcadeSystem::ArrowDown;

  keycodeMap[32] = ArcadeSystem::Space;

  keycodeMap[50] = ArcadeSystem::PrevGraph;
  keycodeMap[51] = ArcadeSystem::NextGraph;
  keycodeMap[52] = ArcadeSystem::PrevGame;
  keycodeMap[53] = ArcadeSystem::NextGame;

  keycodeMap[56] = ArcadeSystem::Restart;
  keycodeMap[57] = ArcadeSystem::Home;
  keycodeMap[27] = ArcadeSystem::Exit;
  keycodeMap[112] = ArcadeSystem::Pause;
  keycodeMap[10] = ArcadeSystem::Enter;
  keycodeMap[263] = ArcadeSystem::Backspace;

  _stdscr = new ncr::Window(ArcadeSystem::winHeight + 2, ArcadeSystem::winWidth + 2, 0, 0);
}

NCursesGraph::~NCursesGraph()
{
  if (gameWin)
    delete gameWin;
  if (UIWin)
    delete UIWin;
  if (_board)
    delete _board;
  if (_stdscr)
    delete _stdscr;
  NCurses::destroy();
}

bool			NCursesGraph::isResizeGood() const
{
  int	x;
  int	y;

  if (NCurses::getMaxXY(x, y) == ERR)
    return (false);
  if (static_cast<unsigned int>(x) < ArcadeSystem::winWidth + 2)
    return (false);
  if (static_cast<unsigned int>(y) < ArcadeSystem::winHeight + 2)
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
  if ((it = keycodeMap.find(keycode)) != keycodeMap.end())
    return (it->second);
  return (keycode);
}

ncr::Window		*NCursesGraph::onCreateBoard()
{
  if (_board == NULL)
    {
      _board = new ncr::Window(ArcadeSystem::winHeight + 2, ArcadeSystem::winWidth + 2, 0, 0);
      gameWin = new ncr::Window(ArcadeSystem::winHeight, ArcadeSystem::winWidth, 1, 1, *_board);
      _board->attrON(A_REVERSE | COLOR_PAIR(4));
      _board->makeBorder(' ', ' ', ' ');
      _board->attrOFF(A_REVERSE);
      _board->refresh();
    }
  return (gameWin);
}

ncr::Window		*NCursesGraph::onCreateUI()
{
  if (UIWin == NULL)
    {
      UIWin = new ncr::Window(3, ArcadeSystem::winWidth - 1, 2, ArcadeSystem::winHeight + 3);
      UIWin->attrON(A_REVERSE | COLOR_PAIR(4));
      UIWin->makeBorder(' ', ' ', ' ');
      UIWin->attrOFF(A_REVERSE);
    }
  return (UIWin);
}

void	        NCursesGraph::_displayComponent(GameComponent const *gameComponent,
						ncr::Window *win)
{
  Vector2<int>	pos = gameComponent->getPos();

  onCreateBoard();
  if (!win)
    return ;
  if (gameComponent->getSpriteText() != " ")
    win->attrON(COLOR_PAIR(gameComponent->getColor()));
  else
    win->attrON(A_REVERSE | COLOR_PAIR(gameComponent->getColor()));
  win->print(pos.x, pos.y, "%s", gameComponent->getSpriteText().c_str());
  win->attrOFF(A_REVERSE);
  _cacheGame.push(s_cache(gameComponent->getPos(),
			  gameComponent->getSpriteText(), gameWin));
}

void	        NCursesGraph::_displayComponent(UIComponent const *uiComponent, ncr::Window *win)
{
  Vector2<int>	pos = uiComponent->getPos();

  onCreateUI();
  if (!win)
    return ;
  win->attrON(COLOR_PAIR(uiComponent->getColor()) | A_BOLD);
  win->print(pos.x, pos.y, "%s", uiComponent->getText().c_str());
  _cacheGame.push(s_cache(uiComponent->getPos(), uiComponent->getText(), win));
}

void		NCursesGraph::_displayComponent(HighScoreComponent const *hightScoreComponent,
						ncr::Window *win)
{
  int			i = 0;
  const UIComponent *const *arrayComponent = hightScoreComponent->getComponentsToDisplay();
  
  while (arrayComponent[i] != NULL)
    {
      _displayComponent(arrayComponent[i], win);
      ++i;
    }
}

void		NCursesGraph::_displayFile(int x, int y, std::string const &contenu,
					   ncr::Window *win) const
{
  unsigned int	i;
  int		newX;
  int		newY;

  i = 0;
  newX = x;
  newY = y;
  while (i < contenu.size())
    {
      if (contenu[i] == '$')
	{
	  win->write(newX, newY, ' ', A_REVERSE | COLOR_PAIR(3));
	}
      else if (contenu[i] == '\n')
	{
	  ++newY;
	  newX = 0;
	}
      else
	{
	  win->write(newX, newY, contenu[i], A_REVERSE | COLOR_PAIR(3));
	}
      ++newX;
      ++i;
    }
}

void		NCursesGraph::_displayComponent(AnimationComponent const *animation,
						ncr::Window *win)
{
  std::ofstream					fd;
  std::stringstream				buffer;
  // std::map<std::string, std::string>::iterator	it;

  // if ((it = _fileCache.find(animation->getFileName())) != _fileCache.end())
  //   {
  //     _displayFile(animation->getPos().x, animation->getPos().y, (*it).second, win);
  //     return ;
  //   }
  fd.open(animation->getFileName().c_str());
  if (fd.is_open())
    {
      buffer << fd.rdbuf();
      _displayFile(animation->getPos().x, animation->getPos().y, buffer.str(), win);
      fd.close();
    }
}

void		NCursesGraph::_cacheClear()
{
  if (gameWin == NULL)
    return ;
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
  GameComponent		*gameComponent;
  UIComponent		*uiComponent;
  HighScoreComponent	*highScore;
  AnimationComponent	*animation;

  _cacheClear();
  while (!obj.empty())
    {
      if ((gameComponent = dynamic_cast<GameComponent *>(obj.top())) != NULL)
      	{
      	  _displayComponent(gameComponent, gameWin);
      	}
      else if ((uiComponent = dynamic_cast<UIComponent *>(obj.top())) != NULL)
      	{
  	  _displayComponent(uiComponent, UIWin);
  	}
      else if ((highScore = dynamic_cast<HighScoreComponent *>(obj.top())) != NULL)
	{
	  _displayComponent(highScore, gameWin);
	}
      else if ((animation = dynamic_cast<AnimationComponent *>(obj.top())) != NULL)
	{
	  _displayComponent(animation, _stdscr);
	}
      delete obj.top();
      obj.pop();
    }
  if (gameWin)
    gameWin->refresh();
  if (UIWin)
    UIWin->refresh();
}

extern "C" IGraph *loadLib()
{
    return new NCursesGraph();
}
