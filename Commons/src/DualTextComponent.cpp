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
DualTextComponent::DualTextComponent(Vector2<double> const &pos, AComponent::ComponentColor color,
                                     Vector2<double> const &dim, std::string const &string, std::string const &subTitle) :
    UIComponent(pos, color, dim, string)
{
    setSubTitle(subTitle);
}

DualTextComponent::DualTextComponent(const DualTextComponent &component) :
    UIComponent(component.getPos(), component.getColor(), component.getDim(), component.getText())
{
    setSubTitle(component.subTitle);
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
    subDim = Vector2<double>(static_cast<int>(string.length()), getDim().y / 3);
    subPos = Vector2<double>(getDim().x / 2 - subDim.x / 2 + getPos().x, getPos().y + getDim().y);
}

/**
 * @return the subtitle
 */
std::string const &DualTextComponent::getSubTitle() const
{
    return subTitle;
}

Vector2<double> const &DualTextComponent::getSubPos() const
{
    return subPos;
}

Vector2<double> const &DualTextComponent::getSubDim() const
{
    return subDim;
}
