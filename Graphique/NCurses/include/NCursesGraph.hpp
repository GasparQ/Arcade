//
// NCursesGraph.hpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 14:58:54 2016 Victor Gouet
// Last update Fri Mar 18 14:47:31 2016 Victor Gouet
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

typedef struct	s_cache
{
public:
  Vector2<int>	const	vector;
  std::string   const	str;
  ncr::Window		*win;

public:
  s_cache(Vector2<int> const vector, std::string const str, ncr::Window *win)
    : vector(vector), str(str), win(win)
  {}
}		t_cache;

class	NCursesGraph	: public IGraph
{
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

private:
  void			_displayComponent(GameComponent const *, ncr::Window *win);
  void			_displayComponent(HighScoreComponent const *, ncr::Window *win);
  void			_displayComponent(UIComponent const *, ncr::Window *win);
  void			_displayComponent(AnimationComponent const *, ncr::Window *win);
  void			_cacheClear();
  bool			isResizeGood() const;
  ncr::Window		*onCreateBoard();
  ncr::Window		*onCreateUI();
  void			_displayFile(int x, int y, std::string const &contenu, ncr::Window *) const;
};

#endif
