//
// Menu.hpp for Menu in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Mar 10 10:00:15 2016 Victor Gouet
// Last update Thu Mar 10 18:17:45 2016 Victor Gouet
//

#ifndef MENUNCURSES_HPP_
# define MENUNCURSES_HPP_

# include <list>
# include "Window.hpp"

namespace ncr
{
  class	Menu
  {
  public:
    Menu(int height, int width, int x, int y, WINDOW *win = stdscr);
    ~Menu();

  public:
    ncr::Window	        *addSubWin(int height);
    int			deleteSubWin(int id = -1);
    int			selectWindow(int id = -1);
    int			refresh(int id = -1);

  public:
    Window	*getMainWindow() const;

  private:
    std::list<Window *>	subWin;
    Window		*mainWindow;
    Window		*_prevSelect;
  };
};

#endif
