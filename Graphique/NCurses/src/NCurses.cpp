//
// NCurses.cpp for ncurses in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 23:55:45 2016 Victor Gouet
// Last update Tue Mar 15 16:23:55 2016 Victor Gouet
//

# include "../include/NCurses.hpp"

WINDOW *NCurses::init()
{
  WINDOW *win = initscr();

  if (win)
    {
      raw();
      start_color();
      keypad(stdscr, true);
      set_escdelay(0);
    }
  return (win);
}

int	NCurses::destroy()
{
  return (endwin());
}

int	NCurses::initPair(short id, short text, short background)
{
  return (init_pair(id, text, background));
}

int	NCurses::hide_cursor()
{
  return (curs_set(0));
}

int	NCurses::show_cursor()
{
  return (curs_set(1));
}

#include <unistd.h>
#include <iostream>

int	NCurses::getCarac()
{
  return (getch());
}

int	NCurses::getString(char *str)
{
  int	value;

  // keypad(stdscr, false);
  value = getstr(str);
  // keypad(stdscr, true);
  return (value);
}

int    NCurses::echoMode()
{
  return (echo());
}

int    NCurses::noEchoMode()
{
  return (noecho());
}

int	NCurses::delayOnGetOutput()
{
  return (nodelay(stdscr, true));
}

int	NCurses::getMaxXY(int &x, int &y)
{
  return (getmaxyx(stdscr, y, x));
}
