//
// NCursesGraph.hpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 14:58:54 2016 Victor Gouet
// Last update Thu Mar 31 13:27:57 2016 Victor Gouet
//

#ifndef NCURSESGRAP_HPP_
# define NCURSESGRAP_HPP_

# include <string>
# include <map>
# include <fstream>

# include "../../include/IGraph.hpp"
# include "Window.hpp"
# include "NCurses.hpp"
# include "../../../Commons/include/GameComponent.hpp"
# include "../../../Commons/include/UIComponent.hpp"
# include "../../../Commons/include/HighScoreComponent.hpp"
# include "../../../Commons/include/AnimationComponent.hpp"
# include "../../Exception/NCursesException.hpp"
# include "../../../Commons/include/ActionComponent.hpp"

typedef struct	s_cache
{
public:
  Vector2<double>	const	vector;
  std::string   const	str;
  ncr::Window		*win;

public:
  s_cache(Vector2<double> const vector, std::string const str, ncr::Window *win)
    : vector(vector), str(str), win(win)
  {}
}		t_cache;

typedef struct	s_rains
{
public:
  int		color;
  int		x;
  int		y;

private:
  bool		bounce;

public:

  void		init()
  {
    color = 3;
    bounce = false;
    x = rand() % 1500;
    y = rand() % 1500;
  }

  void		move()
  {
    int newX;
    int newY;

    getmaxyx(stdscr, newY, newX);

    if (!bounce)
      {
	x--;
	y++;
      }
    else
      {
	--x;
	--y;
      }
    if (y <= 10)
      {
    	color = 2;
      }
    else if (y <= 20)
      {
    	color = 3;
      }
    else if (y <= 30)
      {
    	color = 6;
      }
    else if (y <= 40)
      {
    	color = 7;
      }

    if (x <= 0)
      {
	bounce = (bounce == true ? false : true);
	// init();
      }
    if (y > newY)
      {
	bounce = (bounce == true ? false : true);
      }

    if (x < 0 || y < 0)
      {
	init();
      }
  }
}		t_rains;

class	NCursesGraph	: public IGraph
{
private:
  static const	int rains_capacity = 10000;

public:
  NCursesGraph();
  virtual ~NCursesGraph();

public:
  virtual int eventManagment();
  virtual void display(std::stack<AComponent *>);

private:
  ncr::Window			*gameWin;
  ncr::Window			*_board;
  std::stack<t_cache>		_cacheGame;
  ncr::Window			*UIWin;
  std::map<int, int>		keycodeMap;
  ncr::Window			*_stdscr;
  std::map<std::string, std::string>	_fileCache;
  t_rains			rains[rains_capacity];
  bool				first_rains;

private:
  void			_displayComponent(GameComponent const *, ncr::Window *win);
  void			_displayComponent(HighScoreComponent const *, ncr::Window *win);
  void			_displayComponent(UIComponent const *, ncr::Window *win);
  void			_displayComponent(AnimationComponent const *, ncr::Window *win);
  void			_cacheClear();
  bool			isResizeGood() const;
  ncr::Window		*onCreateBoard();
  ncr::Window		*onCreateUI();
  void			_displayFile(int x, int y, std::string const &contenu, ncr::Window *);
};

#endif
