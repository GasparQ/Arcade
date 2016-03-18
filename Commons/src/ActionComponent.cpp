//
// Created by gaspar_q on 3/18/16.
//

#include "../include/ActionComponent.hpp"

ActionComponent::ActionComponent(Vector2<int> const &pos, AComponent::ComponentColor color,
                                 Vector2<int> const &dim, const std::string &string) :
    UIComponent(pos, color, dim, string)
{
    selected = false;
}

ActionComponent::ActionComponent(const ActionComponent &component) :
    UIComponent(component.getPos(), component.getColor(), component.getDim(), component.getText())
{
    subTitle = component.subTitle;
    selected = component.selected;
}

ActionComponent::~ActionComponent()
{

}

void ActionComponent::setSubTitle(const std::string &string)
{
    subTitle = string;
}

std::string const &ActionComponent::getSubTitle() const
{
    return subTitle;
}

bool ActionComponent::isSelected() const
{
    return selected;
}

void ActionComponent::select()
{
    selected = true;
}

void ActionComponent::unselect()
{
    selected = false;
}