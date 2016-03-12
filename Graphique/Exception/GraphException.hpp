//
// GraphException.hpp for throw exeption in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/Exception
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat Mar 12 18:34:09 2016 Victor Gouet
// Last update Sat Mar 12 18:52:45 2016 Victor Gouet
//

#ifndef GRAPHEXCEPTION_HPP_
# define GRAPHEXCEPTION_HPP_

# include <stdexcept>

namespace graph
{
  class		GraphException : public std::runtime_error
  {
  public:
    GraphException(std::string const &error)
      : std::runtime_error("graph::graphException: " + error)
    {}

    virtual ~GraphException() throw() {}

  };
};

#endif
