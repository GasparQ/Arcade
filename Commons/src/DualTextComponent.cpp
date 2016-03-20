//
// Created by gaspar_q on 3/20/16.
//

#include "../include/DualTextComponent.hpp"

/**
 * @param pos which is the position of your component
 * @param color which is the color of your component
 * @param dim which is the width and height of your component
 * @param string which corresponds to the title of the UIComponent
 * @param subTitle which is the subtitle of this component
 */
DualTextComponent::DualTextComponent(Vector2<int> const &pos, AComponent::ComponentColor color,
                                     Vector2<int> const &dim, std::string const &string, std::string const &subTitle) :
    UIComponent(pos, color, dim, string),
    subTitle(subTitle)
{
}

DualTextComponent::DualTextComponent(const DualTextComponent &component) :
    UIComponent(component.getPos(), component.getColor(), component.getDim(), component.getText()),
    subTitle(component.subTitle)
{
}

DualTextComponent::~DualTextComponent()
{
}

/**
 * @param string corresponds to the new subtitle to give
 */
void DualTextComponent::setSubTitle(std::string const &string)
{
    subTitle = string;
}

/**
 * @return the subtitle
 */
std::string const &DualTextComponent::getSubTitle() const
{
    return subTitle;
}
