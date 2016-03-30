//
// Centipede.hpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:56:28 2016 Victor Gouet
// Last update Wed Mar 30 17:01:32 2016 Victor Gouet
//

#ifndef CENTIPEDE_HPP_
# define CENTIPEDE_HPP_

# include "../../Commons/include/Vector2.hpp"
# include "../../Commons/include/GameComponent.hpp"
# include <map>
# include <vector>

class	Centipede
{
public:
  Centipede(Vector2<double> const &);
  ~Centipede();

  typedef int (Centipede::*mptr)(char map[31][51], Vector2<double> &pos);

public:
  enum	Direction
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

private:
  int				goUp(char map[31][51], Vector2<double> &pos);
  int				goDown(char map[31][51], Vector2<double> &pos);
  int				goLeft(char map[31][51], Vector2<double> &pos);
  int				goRight(char map[31][51], Vector2<double> &pos);

private:
  Direction			_dir;
  Direction			_dir_prev;
  std::vector<Vector2<double> >	_pos;
  std::map<Direction, mptr>	_map;

public:
  void				move(char map[31][51]);
  std::vector<AComponent *>	getGameComponent() const;

public:
  std::vector<Vector2<double> >	  const &getPos() const;
};

#endif
