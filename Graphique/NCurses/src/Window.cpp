//
// Window.cpp for Window in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 22:40:02 2016 Victor Gouet
// Last update Wed Mar  9 23:49:41 2016 Victor Gouet
//

#include "../include/Window.hpp"

ncr::Window::Window(int height, int width, int x, int y, WINDOW *from)
  : height(height), width(width), x(x), y(y)
{
  win = subwin(from, height, width, y, x);
}

ncr::Window::~Window()
{
  if (win)
    delwin(win);
}

/*
** USES METHODS
*/
int		ncr::Window::clear()
{
  return (wclear(win));
}

int		ncr::Window::moveCursor(int x, int y)
{
  return (wmove(win, y, x));
}

int		ncr::Window::print(const char *format, ...)
{
  int		value;
  va_list	args;

  va_start(args, format);
  value = vwprintw(win, format, args);
  va_end(args);
  return (value);
}

int		ncr::Window::print(int x, int y, const char *format, ...)
{
  int		value;
  va_list	args;

  if (moveCursor(x, y) == ERR)
    return (ERR);
  va_start(args, format);
  value = vwprintw(win, format, args);
  va_end(args);
  return (value);
}

int		ncr::Window::attrON(int at)
{
  return (wattron(win, at));
}

int		ncr::Window::attrOFF(int at)
{
  return (wattroff(win, at));
}

int		ncr::Window::refresh()
{
  return (wrefresh(win));
}

int		ncr::Window::makeBorder(chtype corner, chtype hSide, chtype vSide)
{
  return (wborder(win, hSide, hSide, vSide, vSide, corner, corner, corner, corner));
}

int		ncr::Window::setColorPair(chtype colorPair)
{
  return (wbkgd(win, colorPair));
}

/*
** GETTER
*/
WINDOW      *ncr::Window::getWin() const
{
  return (this->win);
}

int		ncr::Window::getHeight() const
{
  return (this->height);
}

int		ncr::Window::getWidth() const
{
  return (this->width);
}

int		ncr::Window::getX() const
{
  return (this->x);
}

int		ncr::Window::gerY() const
{
  return (this->y);
}
