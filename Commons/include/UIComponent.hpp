//
// UIComponent.hpp for UIComponent in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/Component
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Mar  9 15:38:55 2016 Victor Gouet
// Last update Fri Mar 11 17:25:31 2016 Victor Gouet
//

#ifndef UICOMPONENT_HPP_
# define UICOMPONENT_HPP_

# include <iostream>
# include "AComponent.hpp"

class UIComponent : public AComponent
{
private:
    Vector2<double> dim;
    std::string text;

public:
    UIComponent(Vector2<double> const &pos, enum ComponentColor color,
                Vector2<double> const &dim, std::string const &);

    virtual ~UIComponent();

public:
    Vector2<double> const   &getDim() const;

    std::string const       &getText() const;
    void                    setText(std::string const &);
};

#endif
