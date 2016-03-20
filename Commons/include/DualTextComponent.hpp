//
// Created by gaspar_q on 3/20/16.
//

#ifndef C_DUALTEXTCOMPONENT_HPP
#define C_DUALTEXTCOMPONENT_HPP

#include "UIComponent.hpp"

/**
 * Class in which you will have a subtitle in addition of a title
 */
class   DualTextComponent : public UIComponent
{
public:
    DualTextComponent(
            Vector2<int> const &pos,
            enum ComponentColor color,
            Vector2<int> const &dim,
            std::string const &title,
            std::string const &subTitle = ""
    );
    DualTextComponent(DualTextComponent const &);
    ~DualTextComponent();

public:
    void                setSubTitle(std::string const &string);
    std::string const   &getSubTitle() const;
    Vector2<int> const  &getSubPos() const;
    Vector2<int> const  &getSubDim() const;

private:
    std::string     subTitle;
    Vector2<int>    subPos;
    Vector2<int>    subDim;
};

#endif //C_DUALTEXTCOMPONENT_HPP
