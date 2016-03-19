//
// Created by gaspar_q on 3/18/16.
//

#ifndef C_ACTIONCOMPONENT_HPP
#define C_ACTIONCOMPONENT_HPP

#include "UIComponent.hpp"

template <typename action1Type = void *, typename action2Type = action1Type>
class   ActionComponent : public UIComponent
{
public:
    ActionComponent(Vector2<int> const &pos, enum ComponentColor color,
                    Vector2<int> const &dim, std::string const &string,
                    action1Type f_action = (action1Type)0, action2Type s_action = (action2Type)0) :
            UIComponent(pos, color, dim, string),
            subTitle(""),
            selected(false),
            action1(f_action),
            action2(s_action)
    {
    }
    ~ActionComponent()
    {

    }
    ActionComponent(ActionComponent const &component) :
            UIComponent(component.getPos(), component.getColor(), component.getDim(), component.getText()),
            subTitle(component.subTitle),
            selected(component.selected),
            action1(component.action1),
            action2(component.action2)
    {
    }

public:
    void                setSubTitle(std::string const &string)
    {
        subTitle = string;
    }
    std::string const   &getSubTitle() const
    {
        return subTitle;
    }
    bool                isSelected() const
    {
        return selected;
    }
    void                select()
    {
        selected = true;
    }
    void                unselect()
    {
        selected = false;
    }
    const action1Type   getAction1() const
    {
        return action1;
    }
    const action2Type   getAction2() const
    {
        return action2;
    }

private:
    std::string     subTitle;
    bool            selected;
    action1Type     action1;
    action2Type     action2;

};

#endif //C_ACTIONCOMPONENT_HPP
