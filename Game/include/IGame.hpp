//
// IGame.hpp for IGame in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game/include
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 11:10:42 2016 Victor Gouet
// Last update Wed Mar  9 15:20:01 2016 Victor Gouet
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <stack>
# include "AComponent.hpp"
# include "IGraph.hpp"

class	IGame
{
public:
  virtual std::stack<AComponent *> compute(IGraph const *) = 0;
};

#endif
