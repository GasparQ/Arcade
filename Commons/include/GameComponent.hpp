//
// GameComponent.hpp for GameComponent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:29:17 2016 Victor Gouet
// Last update Fri Mar 11 17:23:06 2016 Victor Gouet
//

#ifndef GAMECOMPONENT_HPP_
# define GAMECOMPONENT_HPP_

# include <iostream>
# include "AComponent.hpp"

class GameComponent : public AComponent
{
public:
    enum Shapes
    {
        CUBE_LARGE,
        CUBE_MEDIUM,
        CUBE_SMALL,
        SPHERE_LARGE,
        SPHERE_MEDIUM,
        SPHERE_SMALL
    };

private:
    Shapes sprite3D;
    std::string spriteText;
    std::string fileSprite2D;

public:
    GameComponent(Vector2<double> const &pos, AComponent::ComponentColor color,
                  Shapes sprite3D, std::string const &spriteText,
                  std::string const &sprite2D);

    virtual ~GameComponent();

public:
    std::string const &getSpriteText() const;

    std::string const &getSprite2D() const;

    Shapes getSprite3D() const;
};

#endif
