//
// NCurses.hpp for Ncurses in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 23:53:22 2016 Victor Gouet
// Last update Sat Mar 12 18:02:33 2016 Victor Gouet
//

#ifndef ARCADENCURSES_HPP_
# define ARCADENCURSES_HPP_

# include <ncurses.h>

class	NCurses
{
public:
  static WINDOW *init();
  static int	destroy();
  static int	initPair(short id, short text, short background);
  static int	hide_cursor();
  static int	show_cursor();
  static int	getCarac();
  static int	getString(char *);
  static int    echoMode();
  static int	noEchoMode();
  static int	delayOnGetOutput();
  static int	getMaxXY(int &x, int &y);
};

#endif
