//
// Window.cpp for Window in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/NCurses
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 22:40:02 2016 Victor Gouet
// Last update Tue Mar 15 15:54:17 2016 Victor Gouet
//

#include "../include/Window.hpp"

ncr::Window::Window(int height, int width, int x, int y, WINDOW *from, int id)
  : height(height), width(width), x(x), y(y), _id(id)
{
  win = subwin(from, height, width, y, x);
}

ncr::Window::Window(int height, int width, int x, int y, ncr::Window const &from, int id)
  : height(height), width(width), x(x), y(y), _id(id)
{
  win = subwin(from.getWin(), height, width, y, x);
}

ncr::Window::~Window()
{
  if (win)
    {
      delwin(win);
    }
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

int		ncr::Window::write(int value, int flags)
{
  return (waddch(this->win, value | flags));
}

int		ncr::Window::write(int x, int y, int value, int flags)
{
  return (mvwaddch(this->win, y, x, value | flags));
}

int		ncr::Window::setAttrON(int at)
{
  return (wattr_on(win, at, NULL));
}

int		ncr::Window::setAttrOFF(int at)
{
  return (wattr_off(win, at, NULL));
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

int		ncr::Window::setColorPair(int id)
{
  return (wbkgd(win, COLOR_PAIR(id)));
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

int		ncr::Window::getY() const
{
  return (this->y);
}

int		ncr::Window::getId() const
{
  return (this->_id);
}
