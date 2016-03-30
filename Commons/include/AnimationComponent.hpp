//
// AnimationComponent.hpp for AnimationMenu in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Commons
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Mar 18 12:04:59 2016 Victor Gouet
// Last update Fri Mar 18 14:05:22 2016 Victor Gouet
//

#ifndef ANIMATIONCOMPONENT_HPP_
# define ANIMATIONCOMPONENT_HPP_

# include <iostream>
# include "AComponent.hpp"

class AnimationComponent : public AComponent
{
public:
    AnimationComponent(int x, int y, enum ComponentColor color,
                       std::string const &file);

    virtual ~AnimationComponent();

private:
    std::string file;

    /*
    **	GETTER
    */
public:
    std::string const &getFileName() const;

    void setFileName(std::string const &);
};


#endif
