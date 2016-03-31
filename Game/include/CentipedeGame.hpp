//
// CentipedeGame.hpp for GAME in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:17:37 2016 Victor Gouet
// Last update Thu Mar 31 12:12:21 2016 Victor Gouet
//

#ifndef CENTIPEDEGAME_HPP
# define CENTIPEDEGAME_HPP

#include "AGame.hpp"
#include "USSEnterprise.hpp"
#include "Centipede.hpp"
#include <vector>

class	CentipedeGame	: public AGame
{
private:
  const char		block = ' ' + 5;

public:
  CentipedeGame();
  virtual ~CentipedeGame();
  virtual std::stack<AComponent *> compute(int keycode);
  virtual void restart();

private:
  void		        initMap();
  void			displayMap(std::stack<AComponent *> &output) const;
  void		        onShoot(std::stack<AComponent *> &output);
  bool		        isEmptyCentipede() const;

private:
  USSEnterprise				spaceShip;
  char					map[31][51];
  std::vector<Centipede>		centipede;
  int					_score;

};

#endif
