//
// Centipede.cpp for centiped in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 14:13:12 2016 Victor Gouet
// Last update Wed Mar 30 17:13:51 2016 Victor Gouet
//

#include "../include/USSEnterprise.hpp"
#include "../../Commons/include/ArcadeSystem.hpp"

USSEnterprise::USSEnterprise()
  : _pos(Vector2<double>(10, 10)), _carac(" "), _file_texture(""),
    _shapes(GameComponent::Shapes::SPHERE_LARGE), _color(AComponent::COLOR_MAGENTA), _shoot(NULL)
{
}

USSEnterprise::~USSEnterprise()
{
}

void	USSEnterprise::goUp(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(0, -1);

  if (newPos.y < 0 || map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    return ;
  _pos = newPos;
}

void	USSEnterprise::goDown(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(0, 1);

  if (newPos.y > 29 || map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    return ;
  _pos = newPos;
}

void	USSEnterprise::goLeft(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(-1, 0);

  if (newPos.x < 0 || map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    return ;
  _pos = newPos;
}

void	USSEnterprise::goRight(char map[31][51])
{
  Vector2<double>	newPos = _pos + Vector2<double>(1, 0);

   if (newPos.x > 50 || map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 'X')
    return ;
  _pos = newPos;
}

Vector2<double>		*USSEnterprise::shoot()
{
  if (!_shoot)
    {
      _shoot = new Vector2<double>(_pos.x, _pos.y);
    }
  return (_shoot);
}

void	USSEnterprise::move(int keycode, char map[31][51])
{
  switch (keycode)
    {
    case ArcadeSystem::ArrowDown:
      goDown(map);
      break;
    case ArcadeSystem::ArrowLeft:
      goLeft(map);
      break;
    case ArcadeSystem::ArrowRight:
      goRight(map);
      break;
    case ArcadeSystem::ArrowUp:
      goUp(map);
      break;
    default:
      break;
    }
}

void				USSEnterprise::stopShot()
{
  if (_shoot)
    delete _shoot;
  _shoot = NULL;
}

Vector2<double>			*USSEnterprise::getShoot() const
{
  return (_shoot);
}

Vector2<double> const			&USSEnterprise::getPos() const
{
  return (_pos);
}

std::string const			&USSEnterprise::getCarac() const
{
  return (_carac);
}

std::string const			&USSEnterprise::getFile2D() const
{
  return (_file_texture);
}

AComponent::ComponentColor		USSEnterprise::getColor() const
{
  return (_color);
}

GameComponent::Shapes			USSEnterprise::getShapes() const
{
  return (_shapes);
}

GameComponent				*USSEnterprise::getGameComponent() const
{
  return (new GameComponent(_pos, _color, _shapes, _carac, _file_texture));
}
