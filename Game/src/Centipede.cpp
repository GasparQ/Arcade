//
// Centipede.cpp for CENTIPEDE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:56:16 2016 Victor Gouet
// Last update Thu Mar 31 12:13:31 2016 Victor Gouet
//

#include "../include/Centipede.hpp"
#include <iterator>
#include <cmath>

Centipede::Centipede(Vector2<double> const &pos) : _dir(Centipede::Direction::LEFT),
                                                   _dir_prev(Centipede::Direction::RIGHT)
// _pos(pos)
{
    Vector2<double> newPos = pos;

    _map[UP] = &Centipede::goUp;
    _map[DOWN] = &Centipede::goDown;
    _map[LEFT] = &Centipede::goLeft;
    _map[RIGHT] = &Centipede::goRight;
    _dir = RIGHT;
    this->pos = pos;
    // _pos.push_back(newPos);
    // _pos.push_back(newPos + Vector2<double>(-1, 0));

    // _pos.push_back(newPos + Vector2<double>(-2, 0));
    // _pos.push_back(newPos + Vector2<double>(-3, 0));

    // _pos.push_back(newPos + Vector2<double>(-4, 0));
    // _pos.push_back(newPos + Vector2<double>(-5, 0));

    // _pos.push_back(newPos + Vector2<double>(-6, 0));
    // _pos.push_back(newPos + Vector2<double>(-7, 0));

    // _pos.push_back(newPos + Vector2<double>(-8, 0));
    // _pos.push_back(newPos + Vector2<double>(-9, 0));
    // _pos.push_back(newPos + Vector2<double>(-10, 0));
    // _pos.push_back(newPos + Vector2<double>(-11, 0));
    // _pos.push_back(newPos + Vector2<double>(-12, 0));
    // _pos.push_back(newPos + Vector2<double>(-13, 0));
    // _pos.push_back(newPos + Vector2<double>(-14, 0));
}

Centipede::~Centipede()
{

}

void        Centipede::add_node()
{
    if (_pos.empty())
    {
        _pos.push_back(this->pos);
    }
    else
    {
        _pos.push_back(_pos.back() + Vector2<double>(-1, 0));
    }
}

Centipede    Centipede::splitCentipede(Vector2<double> const &pos)
{
    Centipede centiped(pos);
    std::list<Vector2<double> >::iterator it;
    int size;

    it = _pos.begin();
    if (this->_dir == LEFT)
    {
        centiped._dir = RIGHT;
    }
    if (this->_dir == RIGHT)
    {
        centiped._dir = LEFT;
    }
    size = static_cast<int>(_pos.size() / 2);
    while (it != _pos.end())
    {
        Vector2<double> vec = *it;

        it = _pos.erase(it);
        if (size <= 0)
            break;
        --size;
        centiped.add_node();
    }
    return (centiped);
}

int    Centipede::goUp(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(0, -1);

    if (newPos.y < 0)
    {
        return (1);
    }
    if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir = _dir_prev;
    }
    _dir = _dir_prev;
    pos = newPos;
    return (0);
}

int    Centipede::goDown(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(0, 1);

    if (newPos.y > 30)
    {
        _dir = _dir_prev;
        _pos.clear();
        return (1);
    }
    if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir = _dir_prev;
    }
    _dir = _dir_prev;
    pos = newPos;
    return (0);
}

int    Centipede::goLeft(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(-1, 0);

    if (newPos.x < 0)
    {
        _dir_prev = RIGHT;
        _dir = DOWN;
        return (1);
    }
    if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir_prev = RIGHT;
        _dir = DOWN;
    }
    pos = newPos;
    return (0);
}

int    Centipede::goRight(char map[31][51], Vector2<double> &pos)
{
    Vector2<double> newPos = pos + Vector2<double>(1, 0);

    if (newPos.x > 50)
    {
        _dir = DOWN;
        _dir_prev = LEFT;
        return (1);
    }
    if (map[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] != ' ')
    {
        _dir = DOWN;
        _dir_prev = LEFT;
    }
    pos = newPos;
    return (0);
}

void                        Centipede::move(char map[31][51])
{
    std::list<Vector2<double> >::iterator it;

    if (_pos.empty())
        return;
    // it = _pos.begin();
    // while (it != _pos.end())
    //   {
    //     (this->*_map[_dir])(map, *it);
    //     ++it;
    //   }

    // (this->*_map[_dir])(map, _pos.front());
    it = _pos.end();
    while (it != _pos.begin())
    {
        if (it != _pos.end())
        {
            std::list<Vector2<double> >::iterator it2 = std::prev(it);
            // std::cout << *it2 << std::endl;
            it->x = round(it2->x);
            it->y = it2->y;
        }
        --it;
    }

    // if (_pos.empty())
    // return ;

    // Vector2<double>	backPos = _pos.back();
    // _pos.pop_back();

    // if (_pos.empty())
    //   return ;

    // _pos.push_front(Vector2<double>(0, 0));

    // if (_pos.empty())
    //   _pos.push_front(backPos);
    // else
    //   _pos.push_front(_pos.front());

    (this->*_map[_dir])(map, _pos.front());
}

std::vector<AComponent *>    Centipede::getGameComponent() const
{
    std::vector<AComponent *> vec;
    std::list<Vector2<double> >::const_iterator it;

    it = _pos.begin();
    while (it != _pos.end())
    {
        vec.push_back(new GameComponent(*it, AComponent::ComponentColor::COLOR_YELLOW,
                                        GameComponent::Shapes::CUBE_SMALL, " ", "FILE"));
        ++it;
    }
    return (vec);
}

std::list<Vector2<double> > const &Centipede::getPos() const
{
    return (_pos);
}

