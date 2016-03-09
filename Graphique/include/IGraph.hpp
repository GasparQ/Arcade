//
// IGraph.hpp for IGraph in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Graphique/include
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 11:05:46 2016 Victor Gouet
// Last update Wed Mar  9 11:07:23 2016 Victor Gouet
//

#ifndef IGRAPH_HPP_
# define IGRAPH_HPP_

# include <stack>
# include "Object.hpp"

class	IGraph
{
public:
  virtual void eventManagment() = 0;
  virtual void display(std::stack<Object *> &) = 0;
  virtual size_t getKey() const = 0;
};

#endif
