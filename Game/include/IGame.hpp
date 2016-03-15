//
// IGame.hpp for IGame in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game/include
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 11:10:42 2016 Victor Gouet
// Last update Fri Mar 11 16:02:27 2016 Victor Gouet
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <stack>
# include "../../Commons/include/AComponent.hpp"

class	IGame
{
public:
    virtual ~IGame() {};
    virtual std::stack<AComponent *> compute(int keycode) = 0;
  virtual void restart() = 0;
};

#endif
