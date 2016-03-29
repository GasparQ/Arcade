//
// CentipedeGame.hpp for GAME in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:17:37 2016 Victor Gouet
// Last update Tue Mar 29 14:28:19 2016 Victor Gouet
//

#ifndef CENTIPEDEGAME_HPP
# define CENTIPEDEGAME_HPP

#include "AGame.hpp"

class	CentipedeGame	: public AGame
{
public:
  CentipedeGame();
  virtual ~CentipedeGame();
  virtual std::stack<AComponent *> compute(int keycode);
  virtual void restart();
};

#endif
