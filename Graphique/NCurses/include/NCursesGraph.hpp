//
// NCursesGraph.hpp for lib in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 14:58:54 2016 Victor Gouet
// Last update Thu Mar 10 22:27:51 2016 Victor Gouet
//

#ifndef NCURSESGRAP_HPP_
# define NCURSESGRAP_HPP_

# include "../../include/IGraph.hpp"
# include "Window.hpp"
# include "NCurses.hpp"
# include "../../../Component/include/GameComponent.hpp"

class	NCursesGraph	: public IGraph
{
public:
  NCursesGraph();
  virtual ~NCursesGraph();

public:
  virtual int eventManagment();
  virtual void display(std::stack<AComponent *>);

private:
  void	        _gameComponent(GameComponent *) const;
  void		_cacheClear();

private:
  ncr::Window			*gameWin;
  ncr::Window			*_board;
  std::stack<Vector2>		_cacheGame;
};

#endif
