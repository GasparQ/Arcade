//
// USSEnterprise.hpp for USSENTERPRISE in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Game
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Mar 29 15:38:20 2016 Victor Gouet
// Last update Fri Apr  1 15:47:12 2016 Victor Gouet
//
//

#ifndef USSENTERPRISE_HPP_
# define USSENTERPRISE_HPP_

#include "../../Commons/include/Vector2.hpp"
#include "../../Commons/include/GameComponent.hpp"

class USSEnterprise
{

public:
    USSEnterprise();

    ~USSEnterprise();

private:
    Vector2<double> _pos;
    const std::string _carac;
    const std::string _file_texture;
    const GameComponent::Shapes _shapes;
    const AComponent::ComponentColor _color;
    Vector2<double> *_shoot;
    mutable GameComponent *gameComponent;

public:
    void goUp(char map[31][51]);

    void goDown(char map[31][51]);

    void goLeft(char map[31][51]);

    void goRight(char map[31][51]);

public:
    void move(int keycode, char map[31][51]);

    Vector2<double> *shoot();

    void stopShot();

    void reinitPos();

public:
    Vector2<double> const &getPos() const;

    std::string const &getCarac() const;

    std::string const &getFile2D() const;

    AComponent::ComponentColor getColor() const;

    GameComponent::Shapes getShapes() const;

    Vector2<double> *getShoot() const;

public:
    GameComponent *getGameComponent() const;

};

#endif
