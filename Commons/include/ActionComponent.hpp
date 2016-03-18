//
// Created by gaspar_q on 3/18/16.
//

#ifndef C_ACTIONCOMPONENT_HPP
#define C_ACTIONCOMPONENT_HPP

#include "UIComponent.hpp"

class   ActionComponent : public UIComponent
{
public:
    ActionComponent(Vector2<int> const &pos, enum ComponentColor color,
                    Vector2<int> const &dim, std::string const &);
    ~ActionComponent();
    ActionComponent(ActionComponent const &);

public:
    void                setSubTitle(std::string const &);
    std::string const   &getSubTitle() const;
    bool                isSelected() const;
    void                select();
    void                unselect();

private:
    std::string     subTitle;
    bool            selected;
};

#endif //C_ACTIONCOMPONENT_HPP
