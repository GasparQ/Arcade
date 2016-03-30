//
// Centipede.hpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:56:28 2016 Victor Gouet
// Last update Tue Mar 29 16:43:33 2016 Victor Gouet
//

#ifndef CENTIPEDE_HPP_
# define CENTIPEDE_HPP_

# include "../../Commons/include/Vector2.hpp"
# include <map>

class	Centipede
{
public:
  Centipede(Vector2<double> const &);
  ~Centipede();

  typedef int (Centipede::*mptr)(char map[31][51]);

public:
  enum	Direction
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

private:
  int				goUp(char map[31][51]);
  int				goDown(char map[31][51]);
  int				goLeft(char map[31][51]);
  int				goRight(char map[31][51]);

private:
  Direction			_dir;
  Direction			_dir_prev;
  Vector2<double>		_pos;
  std::map<Direction, mptr>	_map;

public:
  void				move(char map[31][51]);

public:
  Vector2<double>	  const &getPos() const;
};

#endif
