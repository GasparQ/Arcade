//
// Centipede.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:56:16 2016 Victor Gouet
// Last update Sun Apr  3 16:01:10 2016 Victor Gouet
//

#include "../include/Centipede.hpp"
#include <iterator>
#include <cmath>
#include <algorithm>

//BE CAREFULL WHEN CHANGIN IT
//DON'T FORGET TO CHANGE THE ROUND OF POSITIONS IN "int move(char [][]);"
const double        Centipede::centipedeSpeed = 0.2;

/*
 * \brief Will create the centipede from the given position
 */
Centipede::Centipede(Vector2<double> const &pos) :
        _dir(Centipede::Direction::LEFT),
        _dir_prev(Centipede::Direction::RIGHT),
        _directions({
                            {RIGHT, Vector2<double>(1, 0)},
                            {LEFT, Vector2<double>(-1, 0)},
                            {UP, Vector2<double>(0, -1)},
                            {DOWN, Vector2<double>(0, 1)}
                    })
{
    Vector2<double> newPos = pos;

    /*
     * [UP] => Vector2(0, 1)
     * [DOWN] => Vector2(0, -1)
     * [LEFT] => Vector2(-1, 0)
     * [RIGHT] => Vector2(1, 0)
     */

    _map[UP] = &Centipede::goUp;
    _map[DOWN] = &Centipede::goDown;
    _map[LEFT] = &Centipede::goLeft;
    _map[RIGHT] = &Centipede::goRight;
    _dir = RIGHT;
    this->initPos = pos;
    centipedeMove = new AudioComponent("Sound/CentipedeMove.wav", false, false, false);
}

Centipede::Centipede(const Centipede &centipede) :
        _dir(centipede._dir),
        _dir_prev(centipede._dir_prev),
        _directions(centipede._directions),
        _pos(centipede._pos),
        initPos(centipede.initPos),
        _map(centipede._map)
{
  centipedeMove = new AudioComponent("Sound/CentipedeMove.wav", false, false, false);
}

Centipede &Centipede::operator=(const Centipede &centipede)
{
    _dir = centipede._dir;
    _dir_prev = centipede._dir_prev;
    _pos = centipede._pos;
    initPos = centipede.initPos;
    _map = centipede._map;
    centipedeMove = new AudioComponent("Sound/CentipedeMove.wav", false, false, false);
    return *this;
}

Centipede::~Centipede()
{
  if (centipedeMove)
    {
      delete centipedeMove;
    }
}

/*
 * \brief the centipede is touching the vec paremeter
 */
bool		Centipede::isTouching(Vector2<double> const &vec) const
{
  std::list<centipedeBody>::const_iterator	it;

  it = _pos.begin();
  while (it != _pos.end())
    {
      if (static_cast<int>(vec.x) == static_cast<int>(it->pos.x)
	  && static_cast<int>(vec.y) == static_cast<int>(it->pos.y))
	{
	  return (true);
	}
      ++it;
    }
  return (false);
}

void        Centipede::add_node()
{
    if (_pos.empty())
    {
        _pos.push_back(centipedeBody(this->initPos, RIGHT));
    }
    else
    {
        _pos.push_back(centipedeBody(_pos.back().pos + Vector2<double>(-1, 0), RIGHT));
    }
}

/*
 * \brief when the centipede is split
 */
void    Centipede::splitCentipede(Vector2<double> const &pos)
{
  for (std::list<centipedeBody >::iterator it = _pos.begin(); it != _pos.end(); ++it)
    {
      if (static_cast<int>(it->pos.x) == static_cast<int>(pos.x) &&
            static_cast<int>(it->pos.y) == static_cast<int>(pos.y))
        {
            _pos.erase(it);
            break;
        }
    }
}

/*
 * \brief Centipede goes up
 */
int    Centipede::goUp(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(0, -1);

    if (newPos.y < 0)
    {
        return (1);
    }
    if (newPos >= Vector2<double>(0, 0) && newPos < Vector2<double>(50, 30) &&
        map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir = _dir_prev;
    }
    _dir = _dir_prev;
    pos = newPos;
    return (0);
}

/*
 * \brief Centipede goes down
 */
int    Centipede::goDown(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(0, 1);

    if (newPos.y > 30)
    {
        _dir = _dir_prev;
        _pos.clear();
        return (1);
    }
    if (newPos >= Vector2<double>(0, 0) && newPos < Vector2<double>(50, 30) &&
        map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir = _dir_prev;
    }
    _dir = _dir_prev;
    pos = newPos;
    return (0);
}

/*
 * \brief Centipede goes left
 */
int    Centipede::goLeft(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(-0.3, 0);

    if (newPos.x < 0)
    {
        _dir_prev = RIGHT;
        _dir = DOWN;
        return (1);
    }
    if (newPos >= Vector2<double>(0, 0) && newPos < Vector2<double>(50, 30) &&
        map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir_prev = RIGHT;
        _dir = DOWN;
    }
    pos = newPos;
    return (0);
}

/*
 * \brief Centipede goes right
 */
int    Centipede::goRight(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(0.3, 0);

    if (newPos.x > 50)
    {
        _dir = DOWN;
        _dir_prev = LEFT;
        return (1);
    }
    if (newPos >= Vector2<double>(0, 0) && newPos < Vector2<double>(50, 30) &&
        map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir = DOWN;
        _dir_prev = LEFT;
    }
    pos = newPos;
    return (0);
}

/**
 * \brief Move the centipede bodies on the map
 *
 * \param map The map of the game
 * \return The score to remove when centipede arrive to the area limits
 */
int                        Centipede::move(char map[31][51])
{
    std::list<centipedeBody >::iterator it;
    int scoreToRemove = 0;

    if (_pos.empty())
        return 0;
    for (it = _pos.begin(); it != _pos.end(); ++it)
    {
        Vector2<double> newPos = it->pos + _directions[it->direction] * Centipede::centipedeSpeed;

        if ((newPos.x < 0 && it->pos.x >= 0) ||
            (newPos.x >= 50 && it->pos.x < 50) ||
            (newPos >= Vector2<double>(0, 0) && newPos < Vector2<double>(50, 30) &&
	     map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' '))
        {
            newPos = it->pos + _directions[DOWN];
            it->direction = (it->direction == LEFT ? RIGHT : LEFT);
        }
        it->pos = newPos;
        it->pos.x = round(it->pos.x * 10.0) / 10.0;
        it->pos.y = round(it->pos.y * 10.0) / 10.0;
        if (it->pos.y > 30)
        {
            centipedeBody save = *it;

            scoreToRemove += 30;
            _pos.erase(it);
            it = std::find<std::list<centipedeBody>::iterator, centipedeBody>(_pos.begin(),
									      _pos.end(), save);
        }
    }
    return scoreToRemove;
}

/**
 * \brief Method that will convert the Centipede into gameComponents
 *
 * \return Returns a std::vector of game components used in the display
 */
std::vector<AComponent *>    Centipede::getGameComponent() const
{
    std::vector<AComponent *> vec;
    std::list<centipedeBody>::const_iterator it;

    it = _pos.begin();
    while (it != _pos.end())
    {
      it->actualiseGameComponent();
      vec.push_back(it->gameComponent);
      ++it;
    }
    vec.push_back(centipedeMove);
    return (vec);
}

/**
 * \brief Getter for Centipede positions
 *
 * \return All of the positions of the centipede bodies
 */
std::list<Vector2<double> > Centipede::getPos() const
{
    std::list<Vector2<double> > newList;

    for (std::list<centipedeBody>::const_iterator it = _pos.begin(), end = _pos.end(); it != end; ++it)
    {
        newList.push_back(it->pos);
    }
    return (newList);
}

/**
 * \brief Suppress all bodies of the centipede
 */
void Centipede::clean()
{
    _pos.clear();
}
