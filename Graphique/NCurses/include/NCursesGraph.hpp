//
// NCursesGraph.hpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 14:58:54 2016 Victor Gouet
// Last update Sat Mar 12 17:42:00 2016 Victor Gouet
//

#ifndef NCURSESGRAP_HPP_
# define NCURSESGRAP_HPP_

# include <string>
# include "../../include/IGraph.hpp"
# include "Window.hpp"
# include "NCurses.hpp"
# include "../../../Component/include/GameComponent.hpp"
# include "../../../Component/include/UIComponent.hpp"

typedef struct	s_cache
{
public:
  Vector2	const	vector;
  std::string   const	str;
  ncr::Window		*win;

public:
  s_cache(Vector2 const vector, std::string const str, ncr::Window *win)
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
  void			_displayComponent(GameComponent *) const;
  void			_displayComponent(UIComponent *) const;
  void			_cacheClear();

private:
  ncr::Window			*gameWin;
  ncr::Window			*_board;
  std::stack<t_cache>		_cacheGame;
  ncr::Window			*UIWin;

};

#endif
