//
// NCursesException.hpp for NCurses in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/Exception
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat Mar 12 18:49:06 2016 Victor Gouet
// Last update Sat Mar 12 18:59:41 2016 Victor Gouet
//

#ifndef NCURSESEXCEPTION_HPP_
# define NCURSESEXCEPTION_HPP_

# include "GraphException.hpp"

class	ResizeFailed : public graph::GraphException
{
public:
  ResizeFailed() : graph::GraphException("the terminal is too small")
  {}

  virtual ~ResizeFailed() throw() {}
};

class   NCursesSystemFailed : public graph::GraphException
{
public:
  NCursesSystemFailed() : graph::GraphException("ncurses has failed")
  {}

  virtual ~NCursesSystemFailed() throw() {}
};

#endif
