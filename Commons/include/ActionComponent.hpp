//
// Created by gaspar_q on 3/18/16.
//

#ifndef C_ACTIONCOMPONENT_HPP
#define C_ACTIONCOMPONENT_HPP

#include "UIComponent.hpp"
#include "DualTextComponent.hpp"

/**
 * Class used to associate an element to 2 actions
 */
template <typename linkedElemType, typename action1Type = void *, typename action2Type = action1Type>
class   ActionComponent
{
public:
    ActionComponent(linkedElemType linkedElem, action1Type f_action = (action1Type)0, action2Type s_action = (action2Type)0) :
            linkedElem(linkedElem),
            selected(false),
            action1(f_action),
            action2(s_action)
    {
    }
    ~ActionComponent()
    {

    }
    ActionComponent(ActionComponent const &component) :
            linkedElem(component.linkedElem),
            selected(component.selected),
            action1(component.action1),
            action2(component.action2)
    {
    }

public:
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
    const action1Type   &getAction1() const
    {
        return action1;
    }
    const action2Type   &getAction2() const
    {
        return action2;
    }

public:
    linkedElemType  *operator->()
    {
        return &linkedElem;
    }
    linkedElemType  &operator*()
    {
        return linkedElem;
    }

private:
    linkedElemType  linkedElem;
    bool            selected;
    action1Type     action1;
    action2Type     action2;

};

#endif //C_ACTIONCOMPONENT_HPP
