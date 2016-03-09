//
// Window.hpp for Window in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 22:40:12 2016 Victor Gouet
// Last update Wed Mar  9 23:49:05 2016 Victor Gouet
//

#ifndef WINDOWNCURSE_HPP_
# define WINDOWNCURSE_HPP_

# include <ncurses.h>

namespace ncr
{
  class	Window
  {
  public:
    Window(int height, int width, int x, int y, WINDOW *from = stdscr);
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
    int		setColorPair(chtype colorPair);

    /*
    ** GETTER
    */
  public:
    WINDOW	*getWin() const;
    int		getHeight() const;
    int		getWidth() const;
    int		getX() const;
    int		gerY() const;

    /*
    ** ATTRIBUTS
    */
  private:
    WINDOW	*win;
    int		height;
    int		width;
    int		x;
    int		y;
  };
};

#endif
