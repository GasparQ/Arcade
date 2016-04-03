//
// NCursesGraph.cpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 15:05:21 2016 Victor Gouet
// Last update Sun Apr  3 11:50:11 2016 Victor Gouet
//

#include "../include/NCursesGraph.hpp"
#include "../../../Commons/include/ArcadeSystem.hpp"
#include "../../../Commons/AudioComponent.hpp"


/**
 * \brief Contructor in which ncurses, color, keycodes will be initialised
 */
NCursesGraph::NCursesGraph()
{
  _board = NULL;
  gameWin = NULL;
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

  first_rains = true;

  int y;
  int x;

  getmaxyx(stdscr, y, x);
  _stdscr = new ncr::Window(y, x, 0, 0);
}

/**
 * \brief Will destroy the window and the ncurse
 */
NCursesGraph::~NCursesGraph()
{
  _cacheClear();
  if (gameWin)
    delete gameWin;
  if (_board)
    delete _board;
  if (_stdscr)
    delete _stdscr;
  NCurses::destroy();
}

/**
 * \brief tell you if the resize is enough to display
 */
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

/**
 * \brief tell you if you can display or not
 */
bool			NCursesGraph::canDisplay(int posX, int posY) const
{
  int			x;
  int			y;

  getmaxyx(stdscr, y, x);
  if (x < posX || y < posY)
    {
      return (false);
    }
  return (true);
}

/**
 * \brief return the keycode
 */
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

/**
 * \brief Create the Board which will display the game
 */
ncr::Window		*NCursesGraph::onCreateBoard()
{
  if (_board == NULL)
    {
      _board = new ncr::Window(ArcadeSystem::winHeight + 2, ArcadeSystem::winWidth + 2, 1, 2);
      gameWin = new ncr::Window(ArcadeSystem::winHeight, ArcadeSystem::winWidth, 1, 2, *_board);
    }
  return (gameWin);
}

/**
 * \brief Display GameComponent from the game
 */
void	        NCursesGraph::_displayComponent(GameComponent const *gameComponent,
						ncr::Window *win)
{
  Vector2<double>	pos = gameComponent->getPos();

  onCreateBoard();
  if (!win)
    return ;
  if (!canDisplay(pos.x, pos.y))
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

/**
 * \brief Display UIComponent from the game
 */
void	        NCursesGraph::_displayComponent(UIComponent const *uiComponent, ncr::Window *win)
{
  Vector2<double>	pos = uiComponent->getPos();
  DualTextComponent const   *dualTextComponent =
    dynamic_cast<DualTextComponent const *>(uiComponent);

  if (!win)
    return ;
  if (!canDisplay(pos.x, pos.y))
    return ;
  win->attrON(COLOR_PAIR(uiComponent->getColor()) | A_BOLD);
  win->print(pos.x, pos.y, "%s", uiComponent->getText().c_str());
  _cacheGame.push(s_cache(uiComponent->getPos(), uiComponent->getText(), win));
  if (dualTextComponent)
    {
      Vector2<double>	newPos = dualTextComponent->getSubPos();
      if (!canDisplay(pos.x, newPos.y))
	return ;
      win->attrON(COLOR_PAIR(dualTextComponent->getColor()) | A_BOLD);
      win->print(pos.x, newPos.y, "%s", dualTextComponent->getSubTitle().c_str());
      _cacheGame.push(s_cache(Vector2<double>(pos.x, newPos.y),
			      dualTextComponent->getSubTitle(), win));
    }
}

/**
 * \brief Display HightScoreComponent from the game
 */
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

/**
 * \brief Display AnimationComponent from the game
 */
void		NCursesGraph::_displayComponent(AnimationComponent const *,
						ncr::Window *win)
{
  size_t	i;

  i = 0;
  if (first_rains == true)
    {
      while (i < rains_capacity)
	{
	  rains[i].init();
	  ++i;
	}
    }
  else
    {
      while (i < rains_capacity)
      	{
	  rains[i].move();
	  ++i;
      	}
    }
  i = 0;
  while (i < rains_capacity)
    {
       if (!canDisplay(rains[i].x, rains[i].y))
       	{
       	  ++i;
       	  continue;
       	}
      win->attrON(A_REVERSE | COLOR_PAIR(rains[i].color));
      win->print(rains[i].x, rains[i].y, " ");
      _cacheGame.push(s_cache(Vector2<double>(rains[i].x, rains[i].y), " ", win));
      win->attrOFF(A_REVERSE);
      ++i;
    }
  first_rains = false;
}

/**
 * \brief Clear the cache from the library
 */
void		NCursesGraph::_cacheClear()
{
  if (_cacheGame.empty())
    {
      if (gameWin)
	gameWin->clear();
    }
  while (!_cacheGame.empty())
    {
      std::string space(_cacheGame.top().str);
      if (!canDisplay(static_cast<int>(_cacheGame.top().vector.x),
		      static_cast<int>(_cacheGame.top().vector.y)))
	{
	  _cacheGame.pop();
	  continue;
	}
      _cacheGame.top().win->print(_cacheGame.top().vector.x,
				  _cacheGame.top().vector.y,
				  space.replace(space.begin(),
						space.end(),
						space.size(),
						' ').c_str());
      _cacheGame.pop();
    }
}

/**
 * \brief Display all the component from the stack
 */
void	NCursesGraph::display(std::stack<AComponent *>	obj)
{
  GameComponent		*gameComponent;
  UIComponent		*uiComponent;
  HighScoreComponent	*highScore;
  AnimationComponent	*animation;
  AudioComponent *audioComponent;

  _cacheClear();
  while (!obj.empty())
    {
      if ((gameComponent = dynamic_cast<GameComponent *>(obj.top())) != NULL)
      	{
      	  _displayComponent(gameComponent, gameWin);
      	}
      else if ((uiComponent = dynamic_cast<UIComponent *>(obj.top())) != NULL)
      	{
  	  _displayComponent(uiComponent, _stdscr);
  	}
      else if ((highScore = dynamic_cast<HighScoreComponent *>(obj.top())) != NULL)
	{
	  _displayComponent(highScore, _stdscr);
	}
      else if ((animation = dynamic_cast<AnimationComponent *>(obj.top())) != NULL)
      	{
      	  _displayComponent(animation, _stdscr);
      	}
      else if ((audioComponent = dynamic_cast<AudioComponent*>(obj.top())))
      {
        m_sound.PlaySound(audioComponent->getSoundPath(), audioComponent->getLoop(),
                          audioComponent->getOverlap(), audioComponent->getStop());
      }
      obj.pop();
    }
  if (gameWin)
    gameWin->refresh();
  if (_stdscr)
    _stdscr->refresh();
}

/**
 * \brief Set the title of the terminal
 *
 * \param title The title of the window
 */
void NCursesGraph::setTitle(const std::string &)
{
//    sys.stdout.write("\x1b]2;%s\x07" % title);
}

extern "C" IGraph *loadLib()
{
    return new NCursesGraph();
}
