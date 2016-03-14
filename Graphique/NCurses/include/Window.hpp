//
// Window.hpp for Window in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 22:40:12 2016 Victor Gouet
// Last update Mon Mar 14 15:02:40 2016 Victor Gouet
//

#ifndef WINDOWNCURSE_HPP_
# define WINDOWNCURSE_HPP_

# include "../lib/include/curses.h"

namespace ncr
{
  class	Window
  {
  public:
    Window(int height, int width, int x, int y, WINDOW *from = stdscr, int id = 0);
    Window(int height, int width, int x, int y, ncr::Window const &from, int id = 0);
    ~Window();

    /*
    ** USES METHODS
    */
  public:
    int		clear();
    int		moveCursor(int x, int y);
    int		print(const char *, ...);
    int		print(int x, int y, const char *, ...);
    int		attrON(int at);
    int		attrOFF(int at);
    int		refresh();
    int		makeBorder(chtype corner, chtype hSide, chtype vSide);
    int		setColorPair(int id);
    int		setAttrON(int at);
    int		setAttrOFF(int at);

    /*
    ** GETTER
    */
  public:
    WINDOW	*getWin() const;
    int		getHeight() const;
    int		getWidth() const;
    int		getX() const;
    int		getY() const;
    int	        getId() const;

    /*
    ** ATTRIBUTS
    */
  private:
    WINDOW	*win;
    int		height;
    int		width;
    int		x;
    int		y;
    const int	_id;
  };
};

#endif
