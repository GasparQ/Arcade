//
// Centipede.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:56:16 2016 Victor Gouet
// Last update Tue Mar 29 17:30:24 2016 Victor Gouet
//

#include "../include/Centipede.hpp"

Centipede::Centipede(Vector2<double> const &pos) : _dir(Centipede::Direction::LEFT),
						   _dir_prev(Centipede::Direction::RIGHT),
						   _pos(pos)
{
  _map[UP] = &Centipede::goUp;
  _map[DOWN] = &Centipede::goDown;
  _map[LEFT] = &Centipede::goLeft;
  _map[RIGHT] = &Centipede::goRight;
}

Centipede::~Centipede()
{

}

int    Centipede::goUp(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(0, -0.3);

  if (newPos.y < 0)
    {
      return (1);
    }
  if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    {
      _dir = _dir_prev;
    }
  _pos = newPos;
  return (0);
}

int    Centipede::goDown(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(0, 0.3);

  if (newPos.y > 50)
    {
      _dir = _dir_prev;
      return (1);
    }
  if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    {
      _dir = _dir_prev;
    }
  _pos = newPos;
  return (0);
}

int    Centipede::goLeft(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(-0.3, 0);

  if (newPos.x < 0)
    {
      _dir_prev = RIGHT;
      _dir = DOWN;
      return (1);
    }
  if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    {
      _dir_prev = RIGHT;
      _dir = DOWN;
    }
  _pos = newPos;
  return (0);
}

int    Centipede::goRight(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(0.3, 0);

  if (newPos.x > 50)
    {
      _dir = DOWN;
      _dir_prev = LEFT;
      return (1);
    }
  if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    {
      _dir = DOWN;
      _dir_prev = LEFT;
    }
  _pos = newPos;
  return (0);
}

void				Centipede::move(char map[31][51])
{
  (this->*_map[_dir])(map);
}

Vector2<double> const 		&Centipede::getPos() const
{
  return (_pos);
}

